#!/bin/bash

make rebuild
rm -rf grep_prog
rm -rf grep_com_treminal

echo "input test"
read comman

grep $comman >> grep_com_treminal
./s21_grep $comman >> grep_prog

echo "******** Result of check 'grep $comman' ********"
diff grep_com_treminal grep_prog

