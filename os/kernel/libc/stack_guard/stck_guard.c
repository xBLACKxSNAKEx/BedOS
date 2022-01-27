#include "stck_guard.h"

void _noreturn __stack_chk_fail(void)
{
    VGA_color c;
    c.color_with_blink.background = VGA_MODE_03H_COLOR_BLACK;
    c.color_with_blink.letter = VGA_MODE_03H_COLOR_RED;
    c.color_with_blink.blikning = VGA_MODE_03H_NOT_BLINK;
    VGA_print_string_color("ERROR: stack smashed!", &c);
    //TODO: if in kernel ask user to restart
}