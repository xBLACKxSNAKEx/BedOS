# Directories
BUILD_DIR?=../../build
TOOLS_DIR?=../../tools
SRC_DIR?=../../os

# Compilation tools
ASM?=${TOOLS_DIR}/nasm.exe
CC?=
LD?= 

# Files

.PHONY: all build clean

all: build

build:
	${ASM} ${SRC_DIR}/kernel/kernel.asm -f bin -o ${BUILD_DIR}/kernel/kernel.bin


clean:
	rm -rf ${BUILD_DIR}/kernel/*