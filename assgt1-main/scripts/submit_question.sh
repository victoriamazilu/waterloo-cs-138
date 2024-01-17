#!/bin/sh
# This script submits an acceptable tar file of your project into Marmoset.

# check that we are in the scripts directory
if [ ! -f helper/colors.sh ] 
then
    echo "please cd to the scripts directory"
    echo "this script is intended to be run from the scripts directory"
    exit 1
fi
# in the scripts directory: proceed

if [ "$#" -lt 1 ]; then
    echo -e "Run the script as follows:"
    echo -e "\t./submit_question.sh <QUESTION_NUMBER>"
    exit 1
fi

ASSIGNMENT=a1
QUESTION=$1
DIR_NAME=${ASSIGNMENT}q${QUESTION}
FNAME=${DIR_NAME}.tar.gz

./package.sh ${QUESTION}
cd ../${DIR_NAME}

echo
echo Submitting to Marmoset!
echo
/u/cs_build/bin/marmoset_submit cs138 ${DIR_NAME} ${FNAME}

echo
echo Good luck!
echo
