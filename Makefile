# Makefile for C99Compiler

# Compiler and Flags
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/opt/homebrew/Cellar/llvm/19.1.7/include -I/opt/homebrew/opt/llvm/include -g

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target Executable
TARGET := C99Compiler

# Default Target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJS) `llvm-config --cxxflags --ldflags --system-libs --libs all`

# Compile Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR)

# Copy Output to Clipboard
copy:
	@make clean
	@find $(INC_DIR) $(SRC_DIR) tests -type f -exec cat {} + | pbcopy

# Run the Executable
# Run target: copy the binary, compile a test file, and execute the produced program
run: $(BUILD_DIR)/$(TARGET)
	@echo "Copying binary from $(BUILD_DIR)/$(TARGET) to current directory..."
	@cp $(BUILD_DIR)/$(TARGET) .
	@echo "Running the compiler on tests/test1.c..."
	@./$(TARGET) tests/test1.c
	@echo "Compiling the generated LLVM IR to assembly..."
	@llc output.ll -o output.s
	@echo "Compiling the assembly to an executable..."
	@clang output.s -o output
	@echo "Running the produced executable..."
	@./output


# Phony Targets
.PHONY: all clean run copy
