#!/bin/bash
# This script compiles and runs the program normally

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
    echo -e "\t./run_main.sh <QUESTION_NUMBER>${NC}"
    exit 1
fi

source helper/variables.sh $1

./compile.sh ${QUESTION}

cd $QUESTION_DIR/$OUTPUT

echo -e "${CYAN}Running the program in interactive mode...${NC}"
echo -e "${CYAN}Type input to the program with the keyboard.${NC}"
echo -e "${CYAN}Type ctrl-d to send EOF to the program.${NC}"
echo " "
./a.out
