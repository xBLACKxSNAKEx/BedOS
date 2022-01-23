OUTPUT_FORMAT(elf32-i386)

STARTUP_PHYSICAL_ADDRESS = 0x00008000;
KERNEL_PHYSICAL_ADDRESS  = 0x00009000;

SECTIONS
{
	. = STARTUP_PHYSICAL_ADDRESS;

	. = KERNEL_PHYSICAL_ADDRESS;
	
	.boot :
	{
		obj/asm/init/startup.o
	}

	.text ALIGN(4K) : AT(ADDR(.text))
	{
		*(.text)
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata))
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data))
	{
		*(.data)
	}
}