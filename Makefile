# Makefile for EduCC

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

# Extract test file from command-line arguments (for the run target)
TEST_FILE := $(firstword $(filter-out run,$(MAKECMDGOALS)))
# If a test file is provided on the command line, remove it from MAKECMDGOALS.
ifneq ($(strip $(TEST_FILE)),)
  $(eval .DEFAULT_GOAL := run)
endif

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
	rm -f $(TARGET) output.ll output.s output

# Copy source files to clipboard (if needed)
copy:
	@make clean
	@find $(INC_DIR) $(SRC_DIR) tests -type f -exec cat {} + | pbcopy

# Run the compiler on a specified test file.
# Usage: make run [test_file]
.PHONY: run
run: all $(BUILD_DIR)/$(TARGET)
	@echo "Copying binary from $(BUILD_DIR)/$(TARGET) to current directory..."
	@cp $(BUILD_DIR)/$(TARGET) .
	@if [ -z "$(TEST_FILE)" ]; then \
		echo "No test file provided. Usage: make run <test_file>"; \
		exit 1; \
	fi
	@echo "Running the compiler on $(TEST_FILE)..."
	@./$(TARGET) $(TEST_FILE)
	@echo "Compiling the generated LLVM IR to assembly..."
	@llc output.ll -o output.s
	@echo "Compiling the assembly to an executable..."
	@clang output.s -o output
	@echo "Running the produced executable..."
	@./output

# Test command: run all test cases in tests/*.c.
# Each test file must have an expected output file with the same name plus a .expected suffix.
.PHONY: test
test: $(BUILD_DIR)/$(TARGET)
	@echo "Running test cases..."
	@for test in $(wildcard tests/*.c); do \
		echo "Running test $$test..."; \
		./$(BUILD_DIR)/$(TARGET) $$test; \
		llc output.ll -o output.s; \
		clang output.s -o output; \
		./output > tmp.out; \
		if diff -q tmp.out $$test.expected > /dev/null; then \
			echo "$$test passed."; \
		else \
			echo "$$test failed:"; \
			diff -u tmp.out $$test.expected; \
			rm -f tmp.out; \
			exit 1; \
		fi; \
	done; \
	rm -f tmp.out; \
	echo "All tests passed."

.PHONY: all clean run copy test
