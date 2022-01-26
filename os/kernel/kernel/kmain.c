#include "stdio/stdio.h"

typedef struct
{
	uint64_t BaseAddr;
	uint64_t Length;
	uint32_t Type;
	uint32_t extended_attributes;
} _packed memory_map_descriptor;

void kmain()
{
	printf("BedOS! v.%s", KERNEL_VERSION);
	VGA_newline();
	memory_map_descriptor *mmd = (memory_map_descriptor *)(0x501);
	for (uint8_t i = 0; i < *(uint8_t *)(0x500); i++)
	{
		printf("B: %llx, L: %llx, E: %llx, T: %ld\n", mmd->BaseAddr, mmd->Length, mmd->BaseAddr + mmd->Length - 1, mmd->Type);
		mmd++;
	}
	printf("End\n");
}