#!/bin/bash

./scripts/mount.sh
cp build/bin/kernel/kernel.bin L:/
rm -rf L:/L
./scripts/mount.sh -u