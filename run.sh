#!/bin/bash

if [ -e chess ]; then
    ./chess
else
    echo -e "\033[31m[!] No such file: \033[0m chess has not yet been compiled"
    echo "run ./compile.sh"
fi

