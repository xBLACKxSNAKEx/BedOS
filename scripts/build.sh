#!/bin/bash

cd ..

if [ "$#" -eq 1 ]
then
    if [ "$1" == "clean" ]
    then
        make clean
    fi
elif [ "$#" -eq 0 ]
then
    make
fi