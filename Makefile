ASM := ./tools/nasm

BUILD_DIR = build
TOOLS_DIR = tools
SRC_DIR = os

CC = i686-elf-gcc

.PHONY: all floppy_image build kernel bootloader mount unmount clean always

all: floppy_image

build: bootloader kernel

mount:
	./scripts/mount.sh

unmount:
	./scripts/mount.sh -u

#
# FLOPPY IMAGE
#
floppy_image: build
	dd if=/dev/zero of=${BUILD_DIR}/floppy.img bs=512 count=2880
	mkfs.fat.exe -F 12 -n "FILE" ${BUILD_DIR}/floppy.img
	dd if=${BUILD_DIR}/bootloader/bootloader.bin of=${BUILD_DIR}/floppy.img conv=notrunc
	./scripts/cp_to_floppy.sh
#
# BOOTLOADER
#
bootloader: always
	${MAKE} -C ${SRC_DIR}/bootloader

#
# KERNEL
#
kernel: always
	${MAKE} -C ${SRC_DIR}/kernel

#
# ALWAYS
#
always:
	mkdir -p ${BUILD_DIR}/bootloader
	mkdir -p ${BUILD_DIR}/kernel

clean:
	rm -rf $(SRC_DIR)/*/obj/*
	rm -rf ${BUILD_DIR}