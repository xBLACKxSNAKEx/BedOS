#!/bin/bash

./scripts/mount.sh
cp build/bootloader/boot.bin L:/
cp build/bootloader/boot.bin L:/boot/
cd build/kernel
cp -r . L:/
cd ../..
./scripts/mount.sh -u