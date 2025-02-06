# Makefile for EduCC

# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/opt/homebrew/Cellar/llvm/19.1.7/include -I/opt/homebrew/opt/llvm/include -g

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TEST_DIR := tests

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target Executable
TARGET := C99Compiler
TARGET_PATH := $(BUILD_DIR)/$(TARGET)

# Test settings
TESTS := $(wildcard $(TEST_DIR)/*.c)
LLFILE := output.ll
OBJFILE := output.o
OUR_EXE := our_executable
NATIVE_CC := gcc
GCC_EXE := gcc_executable

# Allow a test file to be passed as a parameter to the run target:
TEST_FILE := $(firstword $(filter-out run,$(MAKECMDGOALS)))
ifneq ($(strip $(TEST_FILE)),)
  $(eval .DEFAULT_GOAL := run)
endif

.PHONY: all copy clean test run

# Default target: build the compiler
all: $(TARGET_PATH)

# Create build directory if needed
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create the compiler executable
$(TARGET_PATH): $(BUILD_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_PATH) $(OBJS) `llvm-config --cxxflags --ldflags --system-libs --libs all`

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(LLFILE) $(OBJFILE) $(OUR_EXE) $(GCC_EXE) our_output.txt gcc_output.txt

# Test target: For every .c file in tests/, compile with both our compiler and gcc,
# run the executables, and compare output and return codes.
test: $(TARGET_PATH)
	@for testfile in $(TESTS); do \
	    echo "-----------------------------------------------------"; \
	    echo "Testing $$testfile"; \
	    $(TARGET_PATH) $$testfile > /dev/null 2>&1; \
	    if [ ! -f $(LLFILE) ]; then \
	        echo "Error: $(LLFILE) was not produced for $$testfile"; \
	        exit 1; \
	    fi; \
	    llc $(LLFILE) -filetype=obj -o $(OBJFILE); \
	    clang $(OBJFILE) -o $(OUR_EXE); \
	    ./$(OUR_EXE) > our_output.txt; \
	    our_ret=$$?; \
	    $(NATIVE_CC) $$testfile -o $(GCC_EXE); \
	    ./$(GCC_EXE) > gcc_output.txt; \
	    gcc_ret=$$?; \
	    echo "Our return code: $$our_ret, gcc return code: $$gcc_ret"; \
	    if [ $$our_ret -ne $$gcc_ret ]; then \
	        echo "Return code mismatch for $$testfile"; \
	        exit 1; \
	    fi; \
	    if ! diff -u our_output.txt gcc_output.txt > /dev/null; then \
	        echo "Output mismatch for $$testfile"; \
	        exit 1; \
	    else \
	        echo "Test $$testfile passed."; \
	    fi; \
	done; \
	echo "-----------------------------------------------------"; \
	echo "All tests passed successfully."

# Run target: Run compiler on a single test file provided on the command line.
run: $(TARGET_PATH)
	@echo "Running $(TARGET_PATH) on $(TEST_FILE)..."
	@$(TARGET_PATH) $(TEST_FILE)

# Copy source files to clipboard
copy:
	@make clean
	@find $(INC_DIR) $(SRC_DIR) $(TEST_DIR) -type f -exec cat {} + | pbcopy


# make all
# ./build/C99Compiler tests/test2.c
# llc output.ll -o output.s
# clang output.s -o output
# ./output