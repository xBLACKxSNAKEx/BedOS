# Directories
BUILD_DIR?=../../build
TOOLS_DIR?=../../tools
SRC_DIR?=../../os

# Compilation tools
ASM?=${TOOLS_DIR}/nasm.exe

# Files


.PHONY: all build clean

all: build

build:
	${ASM} ${SRC_DIR}/bootloader/bootloader.asm -f bin -o ${BUILD_DIR}/bootloader/bootloader.bin
	${ASM} ${SRC_DIR}/bootloader/bootloader_loaded.asm -f bin -o ${BUILD_DIR}/bootloader/bootloaderL.bin


clean:
	rm -rf ${BUILD_DIR}/bootloader/*