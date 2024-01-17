#!/bin/bash

# check that we are in the scripts directory
if [ ! -f helper/colors.sh ] 
then
    echo "please cd to the scripts directory"
    echo "this script is intended to be run from the scripts directory"
    exit 1
fi
# in the scripts directory: proceed


source helper/colors.sh

# This if condition checks whether the question number is provided.
if [ "$#" -lt 1 ]; then
    echo -e "${RED}Run the script as follows:"
    echo -e "\t./run_tests.sh <QUESTION_NUMBER>${NC}"
    echo -e "${RED}If you want to test the program and have the valgrind or gcov report, run it as follows:"
    echo -e "\t./run_tests.sh <QUESTION_NUMBER> <gcov|valgrind>${NC}"
    exit 1
fi



# student files might have Windows/Mac line endings
# student outputs might have noeol on last line etc.
# $1 --- name of the input file
# returns name of sanitized tmp file via stdout
sanitize () {
    touch "$1"
    if [ -s "$1" ] ; then
        # file has contents, so sanitize them
        sanitized=`mktemp`
        touch "$sanitized"
        dos2unix --newfile "$1" "$sanitized" &> /dev/null
        # https://unix.stackexchange.com/questions/31947/how-to-add-a-newline-to-the-end-of-a-file
        sed -i -e '$a\' "$sanitized"
        # return the name of the new tmp file
        echo "$sanitized"
    else
        # file is empty, so do nothing
        # return the original file name
        echo "$1"
    fi
}


# This function runs a single test case
run_testcase () {
    total_counter=$(( total_counter + 1 ));

    if [ ! -f "$input" ] ; then
        echo -e "${RED}Input doesn't exist: $input"
        return 1
    fi
    if [ ! -f "$expected.out" ] ; then
        echo -e "${RED}Expected output doesn't exist: $expected.out"
        return 1
    fi
    if [ ! -f "$expected.err" ] ; then
        echo -e "${RED}Expected error output doesn't exist: $expected.err"
        return 1
    fi

    if [ "$compilation_type" = "$VALGRIND" ]; then
        echo -e "${CYAN}Running valgrind (no output is good) ...${NC}"
        valgrind --leak-check=yes --quiet --num-callers=2 ${EXECUTABLE_FILE} < "$input" &> /dev/null

    elif [ "$compilation_type" = "$GCOV" ]; then
        ${EXECUTABLE_FILE} < "$input" > "$actual.out" 2> "$actual.err"
    else
        ${EXECUTABLE_FILE} < "$input" > "$actual.out" 2> "$actual.err"

        # check stderr
        actualerr=`sanitize "$PWD/$actual.err"`
        expectederr=`sanitize "$PWD/$expected.err"`
        diff --strip-trailing-cr "$expectederr" "$actualerr"
        if [ $? -ne 0 ]; then 
            echo -e "${RED}Failed: err stream differed${NC}"
            return 2
        fi
        
        # check stdout
        actualout=`sanitize "$PWD/$actual.out"`
        expectedout=`sanitize "$PWD/$expected.out"`
        D=`diff --strip-trailing-cr "$expectedout" "$actualout"`
        Dlen="${#D}"
        if [ "$Dlen" -gt 0 ]; then
            # print out the diff, converting spaces to underscores
            echo "$D" | cat -A | sed -e 's/ /_/g' -e 's/\$$//' -e 's/^\(.\)_/\1 /'
            echo -e "${RED}Failed: out stream differed${NC}"
            return 1
        else
            echo -e "${GREEN}Passed!${NC}"
            passed_counter=$(( passed_counter + 1 ));
            return 0
        fi
        
    fi
}

# This function prints the final result of running test cases
print_result() {
    if [ -z "$compilation_type" ]; then
        echo -e "\n${CYAN}########\t${passed_counter} / ${total_counter} TEST CASES PASSED!\t########${NC}"
    elif [ "$compilation_type" = "$GCOV" ]; then
        echo -e "${CYAN}Running gcov ...${NC}"
        echo " "
        # the switches don't really change the output through the filter
        # but the switches are good to have here for reference
        # running gcov on the gcno files (instead of cc) also works on 11.2.0
        gcov --demangled-names --function-summaries *a1q${QUESTION}.gcno | grep -A 1 "File .a1q${QUESTION}.cc"
    fi
}

##############
# Here the script actually starts

source helper/variables.sh $1
compilation_type=$2

# Compilation
./compile.sh ${QUESTION} ${compilation_type}

cd $QUESTION_DIR/$OUTPUT

# make and clean output directories
mkdir -p ${OUTPUTS_ACTUAL}/
rm -f ${OUTPUTS_ACTUAL}/*.out
rm -f ${OUTPUTS_ACTUAL}/*.err

total_counter=0
passed_counter=0

# run all of the tests
echo -e "${CYAN}Running tests ...${NC}"
inputs=`find ${INPUTS}/ -name '*.in' | sort`
for input in $inputs
do
    # two truncated forms of the input name
    in=`basename $input`
    n=${in/.in/}
    echo -e "${CYAN}$n${NC}"

    # add .out or .err to get an actual file
    actual="${OUTPUTS_ACTUAL}/$n"
    expected="${OUTPUTS_EXPECTED}/$n"
    run_testcase
done

print_result
