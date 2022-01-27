#include "stdio/stdio.h"
#include "cpu/gdt.h"

static void kmain();

void kernel_early_main()
{
	GDT_init();
	// initialize paging
	VGA_init(VGA_MODE_03H);
	// Logger.init(VGA);
	// _init();
	VGA_set_cursor_pos(0,0);
	printf("BedOS! v.%s", KERNEL_VERSION);
	VGA_newline();
	kmain(); 					// give control to real kmain
	// restart(); 				// if we somehow get here restart PC
}

typedef struct
{
	uint64_t BaseAddr;
	uint64_t Length;
	uint32_t Type;
	uint32_t extended_attributes;
} _packed memory_map_descriptor;

void kmain()
{
	memory_map_descriptor* mmd = (memory_map_descriptor*)(0x501);
	for (uint8_t i = 0; i <= *(uint8_t *)(0x500); i++)
	{
		printf("B: %llx, E: %llx, L: %llx, T: %ld\n", mmd[i].BaseAddr, mmd[i].BaseAddr + mmd[i].Length - 1, mmd[i].Length, mmd[i].Type);
	}
	printf("End\n");
}