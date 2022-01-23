# Directories
BUILD_DIR := ../../build
TOOLS_DIR := ../../tools
SRC_DIR   := src
OBJ_DIR   := obj
BIN_DIR   := $(BUILD_DIR)/kernel

# Compilation tools
ASM     := ${TOOLS_DIR}/nasm.exe
CC     := /opt/cross/i686-elf/bin/i686-elf-gcc
OBJCOPY := /opt/cross/i686-elf/i686-elf/bin/objcopy

# Files
C_SOURCES := $(shell find $(SRC_DIR) -name *.c)
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/c/%.o,$(C_SOURCES))

ASM_SOUCES := $(shell find $(SRC_DIR) -name "*.asm")
ASM_OBJECTS := $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/asm/%.o,$(ASM_SOUCES))

GCC_COMPILE_FLAGS := -I $(SRC_DIR) -ffreestanding -ggdb3 -O0 -Wall -Wextra -Wno-unused-parameter -Wno-packed-bitfield-compat -fshort-enums
GCC_LINK_FLAGS := -T ../linker.ld -nolibc -lgcc -nostdlib

DEPS := $(C_OBJECTS:.o=.d)

.PHONY: all build clean

all: build

build: dir $(ASM_OBJECTS) $(C_OBJECTS)
	$(CC) $(C_OBJECTS) $(ASM_OBJECTS) -o $(BIN_DIR)/kernel.elf $(GCC_LINK_FLAGS)
	$(OBJCOPY) -O binary $(BIN_DIR)/kernel.elf $(BIN_DIR)/kernel.bin

$(OBJ_DIR)/c/%.o: $(SRC_DIR)/%.c
	mkdir -p '$(@D)'
	$(CC) -c $< -o $@ -MMD -MF $(@:.o=.d) $(GCC_COMPILE_FLAGS)

$(OBJ_DIR)/asm/%.o: $(SRC_DIR)/%.asm
	mkdir -p '$(@D)'
	${ASM} $< -f elf32 -o $@

-include $(DEPS)

dir:
	mkdir -p obj/asm obj/c

clean:
	rm -rf ${BUILD_DIR}/kernel