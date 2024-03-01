#!/bin/bash

cd src

MAIN_PROGRAM="./main.c"

programs=$(find -name "*.c" ! -name "main.c")

echo $programs

gcc -o chess $programs $MAIN_PROGRAM
