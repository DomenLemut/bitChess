#!/bin/bash

MAIN_PROGRAM="./src/main.c"


cd src

INCLUDE_FILE="./includes.h"

headers=$(find -name "*.h" ! -name "includes.h")

echo "// Automatically generated includes.h file" > $INCLUDE_FILE

for header in $headers
do
    echo "#include \"$header\"" >> $INCLUDE_FILE
done

cd ..

gcc -o chess $MAIN_PROGRAM
