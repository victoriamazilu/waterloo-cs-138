#!/bin/sh
# This script submits all the acceptable tar files of your project into Marmoset.

# check that we are in the scripts directory
if [ ! -f helper/colors.sh ] 
then
    echo "please cd to the scripts directory"
    echo "this script is intended to be run from the scripts directory"
    exit 1
fi
# in the scripts directory: proceed

for question in $(seq 1 5)
do
    ./submit_question.sh ${question}
done