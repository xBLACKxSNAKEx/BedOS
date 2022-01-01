ASM := ./tools/nasm

BUILD_DIR = build
SRC_DIR = os

.PHONY: all floppy_image kernel bootloader clean always

all: floppy_image

#
# FLOPPY IMAGE
#
floppy_image: ${BUILD_DIR}/floppy.img kernel bootloader

${BUILD_DIR}/floppy.img: bootloader kernel
	dd if=/dev/zero of=${BUILD_DIR}/floppy.img bs=512 count=2880
	mkfs.fat.exe -F 12 -n "FILE" ${BUILD_DIR}/floppy.img
	dd if=${BUILD_DIR}/bootloader/bootloader.bin of=${BUILD_DIR}/floppy.img conv=notrunc

#
# BOOTLOADER
#
bootloader: always
	${ASM} ${SRC_DIR}/bootloader/bootloader.asm -f bin -o ${BUILD_DIR}/bootloader/bootloader.bin

#
# ALWAYS
#
always:
	mkdir -p ${BUILD_DIR}/bootloader
	mkdir -p ${BUILD_DIR}/kernel

clean:
	rm -rf ${BUILD_DIR}