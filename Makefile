# Makefile for EduCC

# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/opt/homebrew/Cellar/llvm/19.1.7/include -I/opt/homebrew/opt/llvm/include -g

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TEST_DIR := tests
TEST_OUTPUT_DIR := test_output

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target Executable
TARGET := C99Compiler
TARGET_PATH := $(BUILD_DIR)/$(TARGET)

# Test settings
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

.PHONY: all copy clean test run create_test_output_dir

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

# Ensure test_output directory exists and matches the structure of tests/
create_test_output_dir:
	@mkdir -p $(TEST_OUTPUT_DIR)
	@find $(TEST_DIR) -type d | sed "s|^$(TEST_DIR)|$(TEST_OUTPUT_DIR)|" | xargs mkdir -p

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TEST_OUTPUT_DIR)
	rm -f $(LLFILE) $(OBJFILE) $(OUR_EXE) $(GCC_EXE) our_output.txt gcc_output.txt

# Recursive Test target: Runs tests in all subdirectories, storing results in test_output/
test: $(TARGET_PATH) create_test_output_dir
	clear
	@echo "Running tests recursively..."
	@find $(TEST_DIR) -type f -name "*.c" | while read -r testfile; do \
	    rel_path=$$(echo $$testfile | sed "s|^$(TEST_DIR)/||"); \
	    output_file="$(TEST_OUTPUT_DIR)/$$(dirname $$rel_path)/$$(basename $$rel_path .c).txt"; \
	    echo "-----------------------------------------------------" >> $$output_file; \
	    echo "Testing $$testfile" >> $$output_file; \
	    $(TARGET_PATH) $$testfile > /dev/null 2>&1; \
	    if [ ! -f $(LLFILE) ]; then \
	        echo "Error: $(LLFILE) was not produced for $$testfile" | tee -a $$output_file; \
	        echo "[FAILED] $$testfile - LLVM file not generated" >&2; \
	        continue; \
	    fi; \
	    llc $(LLFILE) -filetype=obj -o $(OBJFILE); \
	    clang $(OBJFILE) -o $(OUR_EXE); \
	    ./$(OUR_EXE) > our_output.txt; \
	    our_ret=$$?; \
	    $(NATIVE_CC) $$testfile -o $(GCC_EXE); \
	    ./$(GCC_EXE) > gcc_output.txt; \
	    gcc_ret=$$?; \
	    echo "Our return code: $$our_ret, gcc return code: $$gcc_ret" >> $$output_file; \
	    if [ $$our_ret -ne $$gcc_ret ]; then \
	        echo "Return code mismatch for $$testfile" | tee -a $$output_file; \
	        echo "[FAILED] $$testfile - Return code mismatch" >&2; \
	        continue; \
	    fi; \
	    if ! diff -u our_output.txt gcc_output.txt > /dev/null; then \
	        echo "Output mismatch for $$testfile" | tee -a $$output_file; \
	        echo "[FAILED] $$testfile - Output mismatch" >&2; \
	    else \
	        echo "Test $$testfile passed." >> $$output_file; \
	    fi; \
	done

	# Aggregate results from subdirectories to parent directories
	@find $(TEST_OUTPUT_DIR) -type d | while read -r dir; do \
	    cat $$dir/*.txt > $$dir/tests_summary.txt 2>/dev/null || true; \
	done

	@echo "-----------------------------------------------------"; \
	echo "All tests executed. Check test_output/ for results."

# Run target: Run compiler on a single test file provided on the command line.
run: $(TARGET_PATH)
	@echo "Running $(TARGET_PATH) on $(TEST_FILE)..."
	@$(TARGET_PATH) $(TEST_FILE)

# Copy source files to clipboard
copy:
	@make clean
	@find $(INC_DIR) $(SRC_DIR) $(TEST_DIR) -type f -exec cat {} + | pbcopy
