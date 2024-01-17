#!/bin/sh
# This script generates the acceptable tar file of your assignment.

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
    echo -e "\t./package.sh <QUESTION_NUMBER>"
    exit 1
fi

ASSIGNMENT=a1
QUESTION=$1
DIR_NAME=${ASSIGNMENT}q${QUESTION}
FNAME=${DIR_NAME}.tar.gz

cd ../${DIR_NAME}

# Finding source and input files and making a tar file
find . -regextype posix-extended -regex '.*\.(cc|in|out|err)$'\
        -print0 | tar --exclude="build"\
        -czf $FNAME --null --files-from -

echo Your tarball file name is: $FNAME
echo 
echo It contains the following files:
echo 
tar -tf $FNAME
