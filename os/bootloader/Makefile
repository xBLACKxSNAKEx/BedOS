# Directories
BUILD_DIR ?= ..\\..\\build
TOOLS_DIR ?= ..\\..\\tools
SRC_DIR ?= ..\\..\\os

# Compilation tools
ASM ?= ${TOOLS_DIR}\\nasm.exe
CC16 = ${TOOLS_DIR}\\wcc\\wcc.exe
LD16 = ${TOOLS_DIR}\\wcc\\wlink.exe

# Compilation flags
ASMFLAGS?= -f obj
C16FLAGS?= -3 -d3 -s -wx -ms -zl -zq 

# Files
STAGE2_SRC_C=$(wildcard stage2/*.c)
STAGE2_SRC_ASM=$(wildcard stage2/*.asm)
STAGE2_OBJS_C=$(patsubst stage2/%.c, ${BUILD_DIR}\\bootloader\\obj\\c\\\\%.obj, ${STAGE2_SRC_C})
STAGE2_OBJS_ASM=$(patsubst stage2/%.asm, ${BUILD_DIR}\\bootloader\\obj\\asm\\\\%.obj, ${STAGE2_SRC_ASM})

.PHONY: all build stage1 stage2 clean

all: build

build: stage1 stage2

stage1: always
	${ASM} ${SRC_DIR}\\bootloader\\stage1\\bootloader_stage1.asm -f bin -o ${BUILD_DIR}\\bootloader\\bootloader.bin

stage2: $(STAGE2_OBJS_ASM) $(STAGE2_OBJS_C) always
	${LD16} NAME ${BUILD_DIR}\\bootloader\\stage2.bin FILE { ${STAGE2_OBJS_ASM} ${STAGE2_OBJS_C} } OPTION MAP=${BUILD_DIR}\\stage2.map @linker.lnk

${BUILD_DIR}\\bootloader\\obj\\asm\\\\%.obj: ${SRC_DIR}\\bootloader\\stage2\\%.asm
	${ASM} ${ASMFLAGS} -o $@ $<

${BUILD_DIR}\\bootloader\\obj\\c\\\\%.obj: ${SRC_DIR}\\bootloader\\stage2\\%.c
	${CC16} ${C16FLAGS} -fo=$@ $<

always:
	mkdir -p ${BUILD_DIR}\\bootloader\\obj\\c
	mkdir -p ${BUILD_DIR}\\bootloader\\obj\\asm

clean:
	rm -rf ${BUILD_DIR}\\bootloader\\*