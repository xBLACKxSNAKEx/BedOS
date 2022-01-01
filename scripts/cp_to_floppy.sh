#!/bin/bash

./scripts/mount.sh
cp build/bootloader/stage2.bin L:/
cd build/kernel
cp -r . L:/
cd ../..
./scripts/mount.sh -u