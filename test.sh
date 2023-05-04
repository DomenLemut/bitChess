#!/bin/bash

function cleanup {
    rm chess
    exit 1
}

trap cleanup SIGINT

./install.sh && ./chess

rm chess