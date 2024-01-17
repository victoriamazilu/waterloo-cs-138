#!/bin/bash

# question-related
QUESTION=$1
QUESTION_DIR="../a1q${QUESTION}"

# build directory
OUTPUT=build
# these paths are relative to the build directory
# so some are back a level and some are not
INPUTS="../inputs"
OUTPUTS_ACTUAL="outputs-actual"
OUTPUTS_EXPECTED="../outputs-expected"
EXECUTABLE_FILE="./a.out"

# types of compilation
GCOV=gcov
VALGRIND=valgrind
