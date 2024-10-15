#!/bin/bash

make rebuild
rm -rf cat_prog
rm -rf cat_com_treminal

echo "Input directory or file name. Ex: file.txt - *.txt - ../cat/*"
read dir

echo "Input flags"
read flags

# сам тест
if [ "$flags" != -E ] && [ "$flags" != -T ]; then
    cat $flags $dir >> cat_com_treminal
    ./s21_cat $flags $dir >> cat_prog
else
    if [ "$flags" == -E ]; then
        cat "-e" $dir >> cat_com_treminal
        ./s21_cat $flags $dir >> cat_prog
    fi
    if [ "$flags" == -T ]; then
        cat "-t"  $dir >> cat_com_treminal
        ./s21_cat $flags $dir >> cat_prog
    fi

fi

echo "******** Result of check 'cat $flags $dir' ********"
diff cat_com_treminal cat_prog


