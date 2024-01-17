#!/bin/bash

QUESTION_DIR=$1
OUTPUT=$2

cd $QUESTION_DIR

# Making a bulid directory
mkdir -p $OUTPUT
rm -rf $OUTPUT/*
cp *.cc $OUTPUT
cd $OUTPUT
