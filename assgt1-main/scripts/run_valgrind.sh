#!/bin/bash
# This script compiles and runs the program to generate the valgrind report

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
    echo -e "\t./run_valgrind.sh <QUESTION_NUMBER>${NC}"
    exit 1
fi

source helper/variables.sh $1

./compile.sh ${QUESTION} valgrind

cd $QUESTION_DIR/$OUTPUT

echo -e "${CYAN}Running valgrind ...${NC}"
echo " "
valgrind --leak-check=yes --quiet --num-callers=2 ./a.out
