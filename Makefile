###############################################################################
# Makefile for EduCC Compiler
###############################################################################

# =============================================================================
# Configuration
# =============================================================================

# Compiler and Tools
CXX          := /usr/bin/clang++
AR           := ar
LLVM_CONFIG  := llvm-config

# Compiler Flags
CXXFLAGS_BASE := -std=c++17 -Wall -Wextra -Wno-unused-parameter -g
LLVM_CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LIBS     := $(shell $(LLVM_CONFIG) --libs)
LLVM_LIBDIR   := $(shell $(LLVM_CONFIG) --libdir)
CXXFLAGS      := $(CXXFLAGS_BASE) $(LLVM_CXXFLAGS) -DLLVM_ENABLE_OPAQUE_POINTERS=0 -fexceptions

# =============================================================================
# Directory Structure
# =============================================================================

# Source Directories
COMMON_DIR       := common
PREPROCESSOR_DIR := preprocessor
COMPILER_DIR     := compiler
TEST_DIR         := tests

# Build Directories
BUILD_DIR        := build
COMMON_BUILD     := $(BUILD_DIR)/common
PREPROC_BUILD    := $(BUILD_DIR)/preprocessor
COMPILER_BUILD   := $(BUILD_DIR)/compiler
TEST_OUTPUT_DIR  := test_output

# =============================================================================
# Source Files
# =============================================================================

# Common Library
COMMON_SRC     := $(shell find $(COMMON_DIR)/src -type f -name "*.cpp")
COMMON_OBJ     := $(patsubst $(COMMON_DIR)/src/%, $(COMMON_BUILD)/%.o, $(COMMON_SRC))
COMMON_INCLUDE := -I$(COMMON_DIR)/include
COMMON_TARGET  := $(COMMON_BUILD)/libcommon.a

# Preprocessor Library
PREPROC_SRC     := $(shell find $(PREPROCESSOR_DIR)/src -type f -name "*.cpp")
PREPROC_HEADERS := $(shell find $(PREPROCESSOR_DIR)/include -type f -name "*.h")
PREPROC_FILES   := $(PREPROC_SRC) $(PREPROC_HEADERS)
PREPROC_OBJ     := $(patsubst $(PREPROCESSOR_DIR)/src/%, $(PREPROC_BUILD)/%.o, $(PREPROC_SRC))
PREPROC_INCLUDE := -I$(PREPROCESSOR_DIR)/include
PREPROC_TARGET  := $(PREPROC_BUILD)/libpreprocessor.a

# Compiler Library
COMPILER_SRC     := $(shell find $(COMPILER_DIR)/src -type f -name "*.cpp")
COMPILER_HEADERS := $(shell find $(COMPILER_DIR)/include -type f -name "*.h")
COMPILER_FILES   := $(COMPILER_SRC) $(COMPILER_HEADERS)
COMPILER_OBJ     := $(patsubst $(COMPILER_DIR)/src/%, $(COMPILER_BUILD)/%.o, $(COMPILER_SRC))
COMPILER_INCLUDE := -I$(COMPILER_DIR)/include
COMPILER_TARGET  := $(COMPILER_BUILD)/libcompiler.a

# Main Executable
MAIN_SRC    := main.cpp
MAIN_TARGET := $(BUILD_DIR)/educc

# =============================================================================
# Test Configuration
# =============================================================================

# Test Files
LLFILE     := output.ll
OBJFILE    := output.o
OUR_EXE    := our_executable
NATIVE_CC  := gcc
GCC_EXE    := gcc_executable
OUR_OUTPUT := our_output.txt
GCC_OUTPUT := gcc_output.txt

# Test Directory Filter
FILTER := $(filter-out test test-log,$(MAKECMDGOALS))
TEST_SUBDIR := $(if $(FILTER),$(TEST_DIR)/$(firstword $(FILTER)),$(TEST_DIR))

# =============================================================================
# Phony Targets
# =============================================================================

.PHONY: all clean test test-log run lint help

# =============================================================================
# Main Targets
# =============================================================================

all: $(MAIN_TARGET)

# =============================================================================
# Build Rules
# =============================================================================

# Create build directories
$(BUILD_DIR) $(COMMON_BUILD) $(PREPROC_BUILD) $(COMPILER_BUILD):
	@mkdir -p $@

# Common Library
$(COMMON_BUILD)/%.o: $(COMMON_DIR)/src/%
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(COMMON_INCLUDE) -c $< -o $@

$(COMMON_TARGET): $(COMMON_OBJ) | $(COMMON_BUILD)
	@echo "Building $@"
	$(AR) rcs $@ $^

# Preprocessor Library
$(PREPROC_BUILD)/%.o: $(PREPROCESSOR_DIR)/src/%
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(PREPROC_INCLUDE) $(COMMON_INCLUDE) -c $< -o $@

$(PREPROC_TARGET): $(PREPROC_OBJ) | $(PREPROC_BUILD)
	@echo "Building $@"
	$(AR) rcs $@ $^

# Compiler Library
$(COMPILER_BUILD)/%.o: $(COMPILER_DIR)/src/%
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(COMPILER_INCLUDE) $(COMMON_INCLUDE) -c $< -o $@

$(COMPILER_TARGET): $(COMPILER_OBJ) | $(COMPILER_BUILD)
	@echo "Building $@"
	$(AR) rcs $@ $^

# Main Executable
$(MAIN_TARGET): $(MAIN_SRC) $(PREPROC_TARGET) $(COMPILER_TARGET) $(COMMON_TARGET) | $(BUILD_DIR)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) -I$(COMPILER_DIR)/include -I$(PREPROCESSOR_DIR)/include $(COMMON_INCLUDE) -o $@ $^ -L$(LLVM_LIBDIR) $(LLVM_LIBS) -lc++

# =============================================================================
# Testing
# =============================================================================

# Test target with terminal output
test: clean all
	@echo "Running tests in $(TEST_SUBDIR)..."
	@find $(TEST_SUBDIR) -type f -name "*.c" | while read -r testfile; do \
		echo "Testing $$testfile..."; \
		$(MAIN_TARGET) $$testfile $(LLFILE) > /dev/null 2>&1; \
		if [ ! -f $(LLFILE) ]; then \
			echo "[FAILED] $$testfile - LLVM file not generated" >&2; \
			continue; \
		fi; \
		llc $(LLFILE) -filetype=obj -o $(OBJFILE); \
		clang $(OBJFILE) -o $(OUR_EXE); \
		our_output=$$(./$(OUR_EXE) 2>/dev/null); \
		our_ret=$$?; \
		$(NATIVE_CC) $$testfile -o $(GCC_EXE); \
		gcc_output=$$(./$(GCC_EXE) 2>/dev/null); \
		gcc_ret=$$?; \
		if [ $$our_ret -ne $$gcc_ret ]; then \
			echo "[FAILED] $$testfile - Return code mismatch (Ours: $$our_ret, GCC: $$gcc_ret)" >&2; \
		else \
			echo "[PASSED] $$testfile"; \
		fi; \
	done
	@echo "Test execution completed."

# Test target with log files
test-log: clean all
	@mkdir -p $(TEST_OUTPUT_DIR)
	@find $(TEST_SUBDIR) -type d | sed "s|^$(TEST_DIR)|$(TEST_OUTPUT_DIR)|" | xargs mkdir -p
	@echo "Running tests in $(TEST_SUBDIR) with log files..."
	@find $(TEST_SUBDIR) -type f -name "*.c" | while read -r testfile; do \
		rel_path=$$(echo $$testfile | sed "s|^$(TEST_DIR)/||"); \
		output_file="$(TEST_OUTPUT_DIR)/$$(dirname $$rel_path)/$$(basename $$rel_path .c).txt"; \
		echo "Testing $$testfile..." | tee $$output_file; \
		$(MAIN_TARGET) $$testfile $(LLFILE) > /dev/null 2>&1; \
		if [ ! -f $(LLFILE) ]; then \
			echo "[FAILED] $$testfile - LLVM file not generated" | tee -a $$output_file; \
			continue; \
		fi; \
		llc $(LLFILE) -filetype=obj -o $(OBJFILE); \
		clang $(OBJFILE) -o $(OUR_EXE); \
		./$(OUR_EXE) > $(OUR_OUTPUT) 2>/dev/null; \
		our_ret=$$?; \
		$(NATIVE_CC) $$testfile -o $(GCC_EXE); \
		./$(GCC_EXE) > $(GCC_OUTPUT) 2>/dev/null; \
		gcc_ret=$$?; \
		echo "Return codes - Ours: $$our_ret, GCC: $$gcc_ret" | tee -a $$output_file; \
		if [ $$our_ret -ne $$gcc_ret ]; then \
			echo "[FAILED] $$testfile - Return code mismatch" | tee -a $$output_file; \
		else \
			echo "[PASSED] $$testfile" | tee -a $$output_file; \
		fi; \
	done
	@echo "Test execution completed. Check $(TEST_OUTPUT_DIR) for results."

# =============================================================================
# Utility Targets
# =============================================================================

# Run compiler on a single file
run: all
	@ARGS=$(filter-out run,$(MAKECMDGOALS)); \
	if [ -z "$$ARGS" ]; then \
		echo "Usage: make run <path/to/file.c>"; \
		exit 1; \
	else \
		echo "Running $(MAIN_TARGET) on $$ARGS..."; \
		$(MAIN_TARGET) $$ARGS; \
	fi

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(TEST_OUTPUT_DIR)
	rm -f $(LLFILE) $(OBJFILE) $(OUR_EXE) $(GCC_EXE) $(OUR_OUTPUT) $(GCC_OUTPUT)
	@echo "Clean completed."

# Format code with clang-format
lint:
	@echo "Formatting code with clang-format..."
	@find . \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
	@echo "Code formatting completed."

# =============================================================================
# Catch-all Rule
# =============================================================================

# Prevent make from treating extra arguments as targets
%:
	@:
