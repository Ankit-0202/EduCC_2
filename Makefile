###############################################################################
# Makefile for EduCC
###############################################################################

# Compiler and Flags
CXX      := clang++
LLVM_CXXFLAGS := $(shell llvm-config --cxxflags)
LLVM_LIBS     := $(shell llvm-config --libs)
LLVM_LIBDIR   := $(shell llvm-config --libdir)
CXXFLAGS := -std=c++17 -Wall -Wextra -Wno-unused-parameter -g $(LLVM_CXXFLAGS)

# Archiver
AR       := ar

# Directories
ROOT_DIR           := $(shell pwd)
PREPROCESSOR_DIR   := preprocessor
COMPILER_DIR       := compiler
TEST_DIR           := tests
BUILD_DIR          := build
PREPROC_BUILD      := $(BUILD_DIR)/preprocessor
COMPILER_BUILD     := $(BUILD_DIR)/compiler
TEST_OUTPUT_DIR    := test_output

# Preprocessor Sources & Headers
PREPROC_SRC     := $(wildcard $(PREPROCESSOR_DIR)/src/*.cpp)
PREPROC_HEADERS := $(wildcard $(PREPROCESSOR_DIR)/include/*.h)
PREPROC_FILES   := $(PREPROC_SRC) $(PREPROC_HEADERS)
PREPROC_OBJ     := $(patsubst $(PREPROCESSOR_DIR)/src/%.cpp, $(PREPROC_BUILD)/%.o, $(PREPROC_SRC))
PREPROC_INCLUDE := -I$(PREPROCESSOR_DIR)/include
PREPROC_TARGET  := $(PREPROC_BUILD)/libpreprocessor.a

# Compiler Sources & Headers
COMPILER_SRC     := $(wildcard $(COMPILER_DIR)/src/*.cpp)
COMPILER_HEADERS := $(wildcard $(COMPILER_DIR)/include/*.h)
COMPILER_FILES   := $(COMPILER_SRC) $(COMPILER_HEADERS)
COMPILER_OBJ     := $(patsubst $(COMPILER_DIR)/src/%.cpp, $(COMPILER_BUILD)/%.o, $(COMPILER_SRC))
COMPILER_INCLUDE := -I$(COMPILER_DIR)/include
COMPILER_TARGET  := $(COMPILER_BUILD)/libcompiler.a

# Main executable (links main.cpp with preprocessor and compiler)
MAIN_SRC    := main.cpp
MAIN_TARGET := $(BUILD_DIR)/educc

# LLVM & GCC Settings for tests
LLFILE     := output.ll
OBJFILE    := output.o
OUR_EXE    := our_executable
NATIVE_CC  := gcc
GCC_EXE    := gcc_executable
OUR_OUTPUT := our_output.txt
GCC_OUTPUT := gcc_output.txt

.PHONY: all clean test test-verbose run create_test_output_dir copy

###############################################################################
# Build Everything
###############################################################################

all: $(MAIN_TARGET)  ## 'all' builds the final executable (educc)

###############################################################################
# Build Preprocessor Library
###############################################################################

$(PREPROC_BUILD):
	mkdir -p $(PREPROC_BUILD)

$(PREPROC_BUILD)/%.o: $(PREPROCESSOR_DIR)/src/%.cpp | $(PREPROC_BUILD)
	$(CXX) $(CXXFLAGS) $(PREPROC_INCLUDE) -c $< -o $@

$(PREPROC_TARGET): $(PREPROC_OBJ)
	$(AR) rcs $@ $^

###############################################################################
# Build Compiler Library
###############################################################################

$(COMPILER_BUILD):
	mkdir -p $(COMPILER_BUILD)

$(COMPILER_BUILD)/%.o: $(COMPILER_DIR)/src/%.cpp | $(COMPILER_BUILD)
	$(CXX) $(CXXFLAGS) $(COMPILER_INCLUDE) -c $< -o $@

$(COMPILER_TARGET): $(COMPILER_OBJ)
	$(AR) rcs $@ $^

###############################################################################
# Build Main Executable
###############################################################################

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MAIN_TARGET): $(MAIN_SRC) $(PREPROC_TARGET) $(COMPILER_TARGET) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -Icompiler/include -Ipreprocessor/include -o $@ $^ -L$(LLVM_LIBDIR) $(LLVM_LIBS)

###############################################################################
# Testing Setup & Execution
###############################################################################

create_test_output_dir:
	@mkdir -p $(TEST_OUTPUT_DIR)
	@find $(TEST_DIR) -type d | sed "s|^$(TEST_DIR)|$(TEST_OUTPUT_DIR)|" | xargs mkdir -p

# Standard Test Mode: Runs all .c tests (compares our output against gcc)
test: all create_test_output_dir
	@clear
	@echo "Running tests..."
	@find $(TEST_DIR) -type f -name "*.c" | while read -r testfile; do \
	    rel_path=$$(echo $$testfile | sed "s|^$(TEST_DIR)/||"); \
	    output_file="$(TEST_OUTPUT_DIR)/$$(dirname $$rel_path)/$$(basename $$rel_path .c).txt"; \
	    echo "-----------------------------------------------------" >> $$output_file; \
	    echo "Testing $$testfile" >> $$output_file; \
	    $(MAIN_TARGET) $$testfile > /dev/null 2>&1; \
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
	        echo "[FAILED] $$testfile - Return code mismatch" >&2 ------ Ours: $$our_ret, GCC: $$gcc_ret; \
	        continue; \
	    fi; \
	    if ! diff -u our_output.txt gcc_output.txt > /dev/null; then \
	        echo "Output mismatch for $$testfile" | tee -a $$output_file; \
	    else \
	        echo "Test $$testfile passed." >> $$output_file; \
	    fi; \
	done
	@echo "-----------------------------------------------------"; \
	echo "All tests executed. Check $(TEST_OUTPUT_DIR) for results."

# Verbose Test Mode: Prints output to stdout as well as saving test logs
test-verbose: all create_test_output_dir
	@clear
	@echo "Running tests in verbose mode..."
	@find $(TEST_DIR) -type f -name "*.c" | while read -r testfile; do \
	    rel_path=$$(echo $$testfile | sed "s|^$(TEST_DIR)/||"); \
	    output_file="$(TEST_OUTPUT_DIR)/$$(dirname $$rel_path)/$$(basename $$rel_path .c).txt"; \
	    echo "-----------------------------------------------------"; \
	    echo "Testing $$testfile"; \
	    echo "-----------------------------------------------------" >> $$output_file; \
	    echo "Testing $$testfile" >> $$output_file; \
	    $(MAIN_TARGET) $$testfile; \
	    if [ ! -f $(LLFILE) ]; then \
	        echo "Error: $(LLFILE) was not produced for $$testfile" | tee -a $$output_file; \
	        echo "[FAILED] $$testfile - LLVM file not generated" >&2; \
	        continue; \
	    fi; \
	    llc $(LLFILE) -filetype=obj -o $(OBJFILE); \
	    clang $(OBJFILE) -o $(OUR_EXE); \
	    echo "Running compiled executable..."; \
	    ./$(OUR_EXE) | tee $(OUR_OUTPUT); \
	    our_ret=$$?; \
	    $(NATIVE_CC) $$testfile -o $(GCC_EXE); \
	    echo "Running GCC-compiled executable..."; \
	    ./$(GCC_EXE) | tee $(GCC_OUTPUT); \
	    gcc_ret=$$?; \
	    echo "Our return code: $$our_ret, gcc return code: $$gcc_ret" | tee -a $$output_file; \
	    if [ $$our_ret -ne $$gcc_ret ]; then \
	        echo "Return code mismatch for $$testfile" | tee -a $$output_file; \
			echo "[FAILED] $$testfile - Return code mismatch" >&2 ------ Ours: $$our_ret, GCC: $$gcc_ret; \
	        continue; \
	    fi; \
	    if ! diff -u our_output.txt gcc_output.txt; then \
	        echo "Output mismatch for $$testfile" | tee -a $$output_file; \
	        echo "[FAILED] $$testfile - Output mismatch" >&2; \
	    else \
	        echo "Test $$testfile passed." | tee -a $$output_file; \
	    fi; \
	done
	@echo "-----------------------------------------------------"; \
	echo "All tests executed in verbose mode. Check test_output/ for results."

###############################################################################
# Run Compiler on a Single File
###############################################################################

run: all
	@clear
	@ARGS=$(filter-out run,$(MAKECMDGOALS)); \
	if [ -z "$$ARGS" ]; then \
	  echo "Usage: make run <path/to/file.c>"; exit 1; \
	else \
	  echo "Running $(MAIN_TARGET) on $$ARGS..." && $(MAIN_TARGET) $$ARGS; \
	fi

###############################################################################
# Copy Source Code to Clipboard (macOS: pbcopy)
#
# For each file copied, its relative path from the project root is printed
# above its contents.
###############################################################################

copy:
	@echo "Copying source files to clipboard..."
	@( \
		echo "### Main Program ###"; \
		echo "$(MAIN_SRC)"; \
		cat $(MAIN_SRC); \
		echo ""; \
		echo "### Preprocessor ###"; \
		for file in $(PREPROC_FILES); do \
			echo "$$file"; \
			cat "$$file"; \
			echo ""; \
		done; \
		echo "### Compiler ###"; \
		for file in $(COMPILER_FILES); do \
			echo "$$file"; \
			cat "$$file"; \
			echo ""; \
		done; \
	) | pbcopy
	@echo "✅ All source files copied to clipboard!"

###############################################################################
# Clean Build Artifacts & Temporary Files
###############################################################################

clean:
	rm -rf $(BUILD_DIR) $(TEST_OUTPUT_DIR)
	rm -f $(LLFILE) $(OBJFILE) $(OUR_EXE) $(GCC_EXE) $(OUR_OUTPUT) $(GCC_OUTPUT)
