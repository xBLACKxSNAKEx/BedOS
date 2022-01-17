#!/bin/bash

./scripts/mount.sh
cp build/bootloader/boot.bin L:/
cd build/kernel
cp -r . L:/
cd ../..
rm -rf L:/L
./scripts/mount.sh -u