# CS138 W24 Assignment 6 README

This assignment has three different parts, as described in the PDF.

1. Part 1 involves creating a hash table abstract base class.
2. Part 2 involves creating a concrete hash table with a better hash function.
3. Part 3 involves using STL algorithm functions with the hash table class.

Each part has two submissions to Marmoset:

-   Tests
-   Code

For a total of 6 Marmoset submissions:

1. Tests for Part 1 - a6p1t
2. Tests for Part 2 - a6p2t
3. Tests for Part 3 - a6p3t
4. Code for Part 1 - a6p1c
5. Code for Part 2 - a6p2c
6. Code for Part 3 - a6p3c

To submit parts to Marmoset individually, you can use the
`submit_project.sh` script. This will look like:

-   `./submit_project.sh 1t`
-   `./submit_project.sh 2t`
-   `./submit_project.sh 3t`
-   `./submit_project.sh 1c`
-   `./submit_project.sh 2c`
-   `./submit_project.sh 3c`

## Test case coverage is measured on staff code

Just like in previous assignments, the test cases you create for this assignment
will be assessed by measuring their coverage _of the staff code_. The provided test
files contain exact copies of all the Marmoset public tests for the corresponding
part. The coverage threshold for each part is written at the top of the test files.

## Provided Scripts:

Replace <part_num> with 1, 2, or 3 depending on which part of the assignment you
are working on.

`run_gtest.sh <part_num>`

This script compiles your a6pX.cc file, then tests it against the Google Test suites.

`run_gcov.sh <part_num>`

This script compiles your a6pX.cc, then tests it against the Google Test suites, then reports
your gcov coverage.

`run_valgrind.sh <part_num>`

This script compiles your a6pX.cc file, then tests it against the Google Test suites with
Valgrind. Note that Valgrind errors can be caused by issues in both a6pX.cc and a6pXTest.cc.
