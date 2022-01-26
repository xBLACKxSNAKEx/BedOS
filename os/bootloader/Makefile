# Directories
BUILD_DIR?=$(abspath ../../build)
TOOLS_DIR?=$(abspath ../../tools)
SRC_DIR?=$(abspath ../../os)

# Compilation tools
ASM?=${TOOLS_DIR}/nasm.exe
CC?=
LD?= 

# Files

.PHONY: all build clean

all: build

build:
	${ASM} ${SRC_DIR}/bootloader/bootloader.asm -f bin -o ${BUILD_DIR}/bin/bootloader/bootloader.bin

clean:
	rm -rf ${BUILD_DIR}/bin/bootloader/*