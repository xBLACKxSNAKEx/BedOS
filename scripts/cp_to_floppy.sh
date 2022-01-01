#!/bin/bash

./scripts/mount.sh
cd build/kernel
cp -r . L:/
cd ../..
./scripts/mount.sh -u