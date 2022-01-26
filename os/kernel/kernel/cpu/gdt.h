#pragma once

#define GDT_SIZE 5

typedef struct GDT_entry
{
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base_16_23;

    uint8_t accessed : 1;
    uint8_t read_write : 1;
    uint8_t direction : 1;
    uint8_t executable : 1;
    uint8_t reserved_1 : 1;
    uint8_t privilege_level : 2;
    uint8_t present : 1;

    uint8_t limit_16_19 : 4;
    uint8_t reserved_2 : 2;
    uint8_t size : 1;
    uint8_t granularity : 1;

    uint8_t base_24_31;

} _packed gdt_entry;

typedef struct gdt_info
{
    uint16_t size;
    uint32_t offset;
} _packed gdt_info;


void GDT_init();
void GDT_fill_NULL_entry();
void GDT_fill_entry(uint8_t index, bool executable, uint8_t privilegeLevel);