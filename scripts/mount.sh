#!/bin/bash

if [ "$#" -eq 0 ]; then
    imdisk -a -f ../build/floppy.img -m L:
elif [ "$#" -eq 1 ] && [ $1 == "-u" ]
then
    imdisk -D -m L:
    rm -rf "L"
else
    echo "Illegal number of parameters"
fi