#pragma once
#include "typedef.h"

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t value;

    __asm__("inw %1, %0"
            : "=a"(value)
            : "Nd"(port));
    io_wait();

    return value;
}

static inline void outw(uint16_t port, uint16_t val)
{
    __asm__("outw %0, %1"
            :
            : "a"(val), "Nd"(port));
    io_wait();
}

static inline uint32_t inl(uint16_t port)
{
    uint32_t value;

    __asm__("inl %1, %0"
            : "=a"(value)
            : "Nd"(port));
    io_wait();

    return value;
}

static inline void outl(uint16_t port, uint32_t val)
{
    __asm__("outl %0, %1"
            :
            : "a"(val), "Nd"(port));
    io_wait();
}

static inline void enable_interrupts()
{
    __asm__("sti" ::);
}

static inline void disable_interrupts()
{
    __asm__("cli" ::);
}

static inline void wait()
{
    __asm__("outb %%al, $0x80"
            :
            : "a"(0));
}
