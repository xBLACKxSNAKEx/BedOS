#include "stdio/stdio.h"

void kmain()
{
	printf("BedOS!\n");
	printf("BedOS! %d %x %lx %llx\n", 12, 0xaf, 0xbeef, 0xbeefbeebfababaca);
	printf("BedOS! %c %s", 'A', "Test");
}