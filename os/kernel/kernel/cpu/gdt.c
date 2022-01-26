#include "gdt.h"

gdt_entry gdt[GDT_SIZE];
gdt_info info;

void GDT_init()
{
    GDT_fill_NULL_entry();
    GDT_fill_entry(1, true, 0);
    GDT_fill_entry(2, false, 0);
    GDT_fill_entry(3, true, 3);
    GDT_fill_entry(4, false, 3);

    info.size = sizeof(gdt_entry) * GDT_SIZE - 1;
    info.offset = (uint32_t)&gdt;

    __asm__("lgdt %0" ::"m"(info));
}

void GDT_fill_NULL_entry()
{
    gdt[0].limit_0_15       = 0x0000;
    gdt[0].base_0_15        = 0x0000;
    gdt[0].base_16_23       =   0x00;

    gdt[0].accessed         =      0;
    gdt[0].read_write       =      0;
    gdt[0].direction        =      0;
    gdt[0].executable       =      0;
    gdt[0].reserved_1       =      0;
    gdt[0].privilege_level  =      0;
    gdt[0].present          =      0;

    gdt[0].limit_16_19      =    0x0;
    gdt[0].reserved_2       =      0;
    gdt[0].size             =      0;
    gdt[0].granularity      =      0;

    gdt[0].base_24_31       =   0x00;
}

void GDT_fill_entry(uint8_t index, bool executable, uint8_t privilegeLevel)
{
    gdt[index].limit_0_15 = 0xFFFF;
    gdt[index].base_0_15 = 0x0000;
    gdt[index].base_16_23 = 0x00;

    gdt[index].accessed = 0;
    gdt[index].read_write = 1;
    gdt[index].direction = 0;
    gdt[index].executable = executable;
    gdt[index].reserved_1 = 1;
    gdt[index].privilege_level = privilegeLevel;
    gdt[index].present = 1;

    gdt[index].limit_16_19 = 0xf;
    gdt[index].reserved_2 = 0;
    gdt[index].size = 1;
    gdt[index].granularity = 1;

    gdt[index].base_24_31 = 0x00;
}