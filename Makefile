# Makefile for C99Compiler

# Compiler and Flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -g

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

# Phony Targets
.PHONY: all clean
