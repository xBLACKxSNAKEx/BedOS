#!/bin/bash

./scripts/mount.sh
cp build/bootloader/boot.bin L:/
cp build/kernel/kernel.bin L:/
rm -rf L:/L
./scripts/mount.sh -u