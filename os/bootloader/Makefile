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
	${ASM} ${SRC_DIR}/bootloader/bootloader.asm -f bin -o ${BUILD_DIR}/bootloader/bootloader.bin
	${ASM} ${SRC_DIR}/bootloader/boot.asm -f bin -o ${BUILD_DIR}/bootloader/boot.bin


clean:
	rm -rf ${BUILD_DIR}/bootloader/*