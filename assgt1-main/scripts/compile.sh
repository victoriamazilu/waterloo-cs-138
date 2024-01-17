#!/bin/bash
# This script compiles the program

# check that we are in the scripts directory
if [ ! -f helper/colors.sh ] 
then
    echo "please cd to the scripts directory"
    echo "this script is intended to be run from the scripts directory"
    exit 1
fi
# in the scripts directory: proceed


source helper/colors.sh

if [ "$#" -lt 1 ]; then
    echo -e "${RED}Run the script as follows:"
    echo -e "\t./compile.sh <QUESTION_NUMBER>${NC}"
    echo -e "${RED}If you want to compile the program to be used by valgrind or gcov, run it as follows:"
    echo -e "\t./compile.sh <QUESTION_NUMBER> <gcov|valgrind>${NC}"
    exit 1
fi

source helper/variables.sh $1
compilation_type=$2

helper/make_build.sh $QUESTION_DIR $OUTPUT
cd ${QUESTION_DIR}/$OUTPUT

if [ "$compilation_type" = "$VALGRIND" ]; then
    echo "Running g++: valgrind compatible"
    g++ a1q${QUESTION}.cc
elif [ "$compilation_type" = "$GCOV" ]; then
    echo "Running g++: gcov compatible"
    g++ --coverage a1q${QUESTION}.cc
else
    echo "Running g++: normal compilation"
    g++ a1q${QUESTION}.cc
fi
