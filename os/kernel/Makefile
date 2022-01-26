# Directories
BUILD_DIR := ../../build
TOOLS_DIR := ../../tools
SRC_DIR   := .
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := $(BUILD_DIR)/bin/kernel

# Compilation tools
ASM     := ${TOOLS_DIR}/nasm.exe
CC     := /opt/cross/i686-elf/bin/i686-elf-gcc
OBJCOPY := /opt/cross/i686-elf/i686-elf/bin/objcopy

# Files
C_SOURCES := $(patsubst $(SRC_DIR)/%/crtn.c,,$(patsubst $(SRC_DIR)/%/crti.c,,$(shell find $(SRC_DIR) -name *.c)))
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/c/%.o,$(C_SOURCES))

ASM_SOUCES := $(shell find $(SRC_DIR) -name "*.asm")
ASM_OBJECTS := $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/asm/%.o,$(ASM_SOUCES))

CRTI_C:=$(shell find $(SRC_DIR) -name "crtn.c")
CRTN_C:=$(shell find $(SRC_DIR) -name "crti.c")

CRTI_OBJ:=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/c/%.o,$(CRTI_C))
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/c/%.o,$(CRTN_C))

GCC_COMPILE_FLAGS := -I kernel -I libc -I klib -I headers -include headers/typedef.h -ffreestanding -ggdb3 -O0 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-packed-bitfield-compat -fshort-enums -Wno-implicit-function-declaration
GCC_LINK_FLAGS := -T ../linker.ld -L libc -L klib -nolibc -lgcc -nostdlib

GCC_LINK_FLAGS += -Wl,-Map=output.map

DEPS := $(C_OBJECTS:.o=.d)

.PHONY: all build clean

all: build

build: $(BIN_DIR)/kernel.bin

$(BIN_DIR)/kernel.elf: $(CRTI_OBJ) $(C_OBJECTS) $(ASM_OBJECTS) $(CRTN_OBJ)
	$(CC) $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(C_OBJECTS) $(ASM_OBJECTS) $(CRTEND_OBJ) $(CRTN_OBJ) -o $(abspath $(BIN_DIR)/kernel.elf) $(GCC_LINK_FLAGS)

$(BIN_DIR)/kernel.bin: $(BIN_DIR)/kernel.elf
	$(OBJCOPY) -O binary $(BIN_DIR)/kernel.elf $(BIN_DIR)/kernel.bin

$(OBJ_DIR)/asm/%.o: $(SRC_DIR)/%.asm
	mkdir -p '$(@D)'
	${ASM} $(abspath $<) -f elf32 -o $(abspath $@)

$(OBJ_DIR)/c/%.o: $(SRC_DIR)/%.c
	mkdir -p '$(@D)'
	$(CC) -c $(abspath $<) -o $(abspath $@) -MMD -MF $(@:.o=.d) $(GCC_COMPILE_FLAGS)

-include $(DEPS)

clean:
	rm -rf ${BUILD_DIR}/kernel