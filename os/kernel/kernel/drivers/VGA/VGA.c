#include "vga.h"

//! Pointer to current screen
/*!
    Points to array of characters
*/ 
volatile screen_char *VGA_video;

//! Current video screen.
uint8_t VGA_current_printing_screen = 0;

//! Current offset for screen.
/*!
    When we add this to `VGA_video` we wil get address of screen we should work on.
*/
uint16_t VGA_screen_offset = 0;

//! Current text mode.
uint8_t VGA_current_mode = 0;

//! Number of columns screens for current text mode.
uint16_t VGA_current_columns = 0;

//! Number of rows screens for current text mode.
uint16_t VGA_current_rows = 0;

//! Number of max screens for current text mode.
uint16_t VGA_current_max_screens = 0;

//! Offset between screens for current text mode.
uint16_t VGA_current_screen_offset = 0;

uint8_t VGA_init(uint8_t mode)
{
    switch(mode)
    {
        case VGA_MODE_00H:
            VGA_current_mode = mode;
            VGA_current_columns = VGA_MODE_00H_SCREEN_COLUMNS;
            VGA_current_rows = VGA_MODE_00H_SCREEN_ROWS;
            VGA_current_max_screens = VGA_MODE_00H_MAX_SCREENS;
            VGA_current_screen_offset = VGA_MODE_00H_SCREEN_OFFSET;
            VGA_set_cursor_pos(0, 0);
            VGA_current_printing_screen = 0;
            VGA_screen_offset = 0;
            VGA_video = (volatile screen_char *)(VGA_MODE_00H_BASE_ADDR);
            VGA_clear_all_screens();
            return 1;
        case VGA_MODE_01H:
            VGA_current_mode = mode;
            VGA_current_columns = VGA_MODE_01H_SCREEN_COLUMNS;
            VGA_current_rows = VGA_MODE_01H_SCREEN_ROWS;
            VGA_current_max_screens = VGA_MODE_01H_MAX_SCREENS;
            VGA_current_screen_offset = VGA_MODE_01H_SCREEN_OFFSET;
            VGA_set_cursor_pos(0, 0);
            VGA_current_printing_screen = 0;
            VGA_screen_offset = 0;
            VGA_video = (volatile screen_char *)(VGA_MODE_01H_BASE_ADDR);
            VGA_clear_all_screens();
            return 1;
        case VGA_MODE_02H:
            VGA_current_mode = mode;
            VGA_current_columns = VGA_MODE_02H_SCREEN_COLUMNS;
            VGA_current_rows = VGA_MODE_02H_SCREEN_ROWS;
            VGA_current_max_screens = VGA_MODE_02H_MAX_SCREENS;
            VGA_current_screen_offset = VGA_MODE_02H_SCREEN_OFFSET;
            VGA_set_cursor_pos(0, 0);
            VGA_current_printing_screen = 0;
            VGA_screen_offset = 0;
            VGA_video = (volatile screen_char *)(VGA_MODE_02H_BASE_ADDR);
            VGA_clear_all_screens();
            return 1;
        case VGA_MODE_03H:
            VGA_current_mode = mode;
            VGA_current_columns = VGA_MODE_03H_SCREEN_COLUMNS;
            VGA_current_rows = VGA_MODE_03H_SCREEN_ROWS;
            VGA_current_max_screens = VGA_MODE_03H_MAX_SCREENS;
            VGA_current_screen_offset = VGA_MODE_03H_SCREEN_OFFSET;
            VGA_set_cursor_pos(0, 0);
            VGA_current_printing_screen = 0;
            VGA_screen_offset = 0;
            VGA_video = (volatile screen_char *)(VGA_MODE_03H_BASE_ADDR);
            VGA_clear_all_screens();
            return 1;
        case VGA_MODE_07H:
            VGA_current_mode = mode;
            VGA_current_columns = VGA_MODE_07H_SCREEN_COLUMNS;
            VGA_current_rows = VGA_MODE_07H_SCREEN_ROWS;
            VGA_current_max_screens = VGA_MODE_07H_MAX_SCREENS;
            VGA_current_screen_offset = VGA_MODE_07H_SCREEN_OFFSET;
            VGA_set_cursor_pos(0, 0);
            VGA_current_printing_screen = 0;
            VGA_screen_offset = 0;
            VGA_video = (volatile screen_char *)(VGA_MODE_07H_BASE_ADDR);
            VGA_clear_all_screens();
            return 1;
        default:
            return -1;
    }
    
}

void VGA_print_char(char character)
{
    VGA_screen_pos VGA_cursor_pos = VGA_get_cursor_pos();
    uint16_t pos = __VGA_calcualte_position_with_offset(VGA_cursor_pos.x, VGA_cursor_pos.y);

    if (character != '\n')
    {
        VGA_video[pos].character.ascii_code = character;
        VGA_video[pos].character.color = __VGA_get_default_terminal_color(VGA_current_mode);
        VGA_cursor_pos.x += 1;
        if (VGA_cursor_pos.x == VGA_current_columns)
        {
            VGA_set_cursor_pos_struct(VGA_cursor_pos);
            VGA_newline();
            VGA_cursor_pos = VGA_get_cursor_pos();
        }
    }
    else
    {
        VGA_set_cursor_pos_struct(VGA_cursor_pos);
        VGA_newline();
        VGA_cursor_pos = VGA_get_cursor_pos();
    }
    VGA_set_cursor_pos_struct(VGA_cursor_pos);
}

void VGA_print_char_color(char character, VGA_color *color)
{
    VGA_screen_pos VGA_cursor_pos = VGA_get_cursor_pos();
    uint16_t pos = __VGA_calcualte_position_with_offset(VGA_cursor_pos.x, VGA_cursor_pos.y);

    if (character != '\n')
    {
        VGA_video[pos].character.ascii_code = character;
        VGA_video[pos].character.color = *color;
        VGA_cursor_pos.x += 1;
        if (VGA_cursor_pos.x == VGA_current_columns)
        {
            VGA_set_cursor_pos_struct(VGA_cursor_pos);
            VGA_newline();
            VGA_cursor_pos = VGA_get_cursor_pos();
        }
    }
    else
    {
        VGA_set_cursor_pos_struct(VGA_cursor_pos);
        VGA_newline();
        VGA_cursor_pos = VGA_get_cursor_pos();
    }
    VGA_set_cursor_pos_struct(VGA_cursor_pos);
}

void VGA_print_string(const char *str)
{
    const char *ptr = str;
    while (*ptr != 0)
    {
        VGA_print_char(*ptr);
        ptr++;
    }
}

void VGA_print_string_color(const char *str, VGA_color *color)
{
    const char *ptr = str;
    while (*ptr != 0)
    {
        VGA_print_char_color(*ptr, color);
        ptr++;
    }
}

void VGA_set_char(uint16_t x, uint16_t y, char character)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    VGA_video[pos].character.ascii_code = character;
}

void VGA_set_char_struct(VGA_screen_pos spos, char c)
{
    VGA_set_char(spos.x, spos.y, c);
}

char VGA_get_char(uint16_t x, uint16_t y)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    return VGA_video[pos].character.ascii_code;
}

char VGA_get_char_struct(VGA_screen_pos spos)
{
    return VGA_get_char(spos.x, spos.y);
}

void VGA_set_color(uint16_t x, uint16_t y, VGA_color col)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    VGA_video[pos].character.color = col;
}

void VGA_set_color_struct(VGA_screen_pos spos, VGA_color col)
{
    VGA_set_color(spos.x, spos.y, col);
}

VGA_color VGA_get_color(uint16_t x, uint16_t y)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    return VGA_video[pos].character.color;
}

VGA_color VGA_get_color_struct(VGA_screen_pos spos)
{
    return VGA_get_color(spos.x, spos.y);
}

void VGA_set_character(uint16_t x, uint16_t y, VGA_character character)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    VGA_video[pos].character = character;
}

void VGA_set_character_struct(VGA_screen_pos spos, VGA_character character)
{
    VGA_set_character(spos.x, spos.y, character);
}

VGA_character VGA_get_character(uint16_t x, uint16_t y)
{
    uint16_t pos = __VGA_calcualte_position_with_offset(x, y);
    return VGA_video[pos].character;
}

VGA_character VGA_get_character_struct(VGA_screen_pos spos)
{
    return VGA_get_character(spos.x, spos.y);
}

void VGA_set_cursor_pos(uint16_t x, uint16_t y)
{
    uint16_t pos = __VGA_calcualte_position_without_offset(x, y);

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void VGA_set_cursor_pos_struct(VGA_screen_pos spos)
{
    VGA_set_cursor_pos(spos.x, spos.y);
}

// TODO: Returned position is not valid after printing some string.
VGA_screen_pos VGA_get_cursor_pos()
{
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    VGA_screen_pos cursor_pos;
    cursor_pos.x = pos % VGA_current_columns;
    cursor_pos.y = pos / VGA_current_columns;
    return cursor_pos;
}

void VGA_clear_screen()
{
    VGA_color col = __VGA_get_default_terminal_color(VGA_current_mode);
    // Clear all rows
    for (uint16_t i = 0; i < VGA_current_rows; ++i)
    {
        // Clear all lines
        for (uint16_t j = 0; j < VGA_current_columns; ++j)
        {
            uint16_t pos = __VGA_calcualte_position_with_offset(j, i);
            // Clear
            VGA_video[pos].character.ascii_code = 0;
            VGA_video[pos].character.color = col;
        }
    }
    VGA_screen_pos VGA_cursor_pos;
    VGA_cursor_pos.x = 0;
    VGA_cursor_pos.y = 0;
    VGA_set_cursor_pos_struct(VGA_cursor_pos);
}

void VGA_clear_given_screen(uint8_t screen)
{
    if (screen < VGA_current_max_screens)
    {
        VGA_color col = __VGA_get_default_terminal_color(VGA_current_mode);
        uint16_t offset_to_screen = VGA_current_screen_offset * (uint16_t)screen;
        // Clear all rows
        for (uint16_t i = 0; i < VGA_current_rows; ++i)
        {
            // Clear all lines
            for (uint16_t j = 0; j < VGA_current_columns; ++j)
            {
                uint16_t pos = __VGA_calcualte_position_without_offset(j, i);
                // Clear
                VGA_video[pos + offset_to_screen].character.ascii_code = 0;
                VGA_video[pos + offset_to_screen].character.color = col;
            }
        }
    }
}

void VGA_clear_all_screens()
{
    VGA_clear_screen();
    for(int i = 1; i < VGA_current_max_screens; ++i)
    {
        VGA_clear_given_screen(i);
    }
}

void VGA_change_printing_screen(uint8_t screen)
{
    if (screen < VGA_current_max_screens)
    {
        VGA_current_printing_screen = screen;
        VGA_screen_offset = VGA_current_screen_offset * (uint16_t)screen;
    }
}

void VGA_copy_screen(uint8_t from, uint8_t to)
{
    if (from < VGA_current_max_screens && to < VGA_current_max_screens)
    {
        uint16_t offset_from = VGA_current_screen_offset * (uint16_t)from;
        uint16_t offset_to = VGA_current_screen_offset * (uint16_t)to;

        // Copy all rows
        for (uint16_t i = 0; i < VGA_current_rows; ++i)
        {
            // Copy all lines
            for (uint16_t j = 0; j < VGA_current_columns; ++j)
            {
                uint16_t pos = __VGA_calcualte_position_without_offset(j, i);
                // Copy
                VGA_video[pos + offset_to].value = VGA_video[pos + offset_from].value;
            }
        }
    }
}

void VGA_cursor_on()
{
    __VGA_enable_cursor(14, 15);
}

void VGA_cursor_off()
{
    __VGA_disable_cursor();
}

void VGA_newline()
{
    VGA_screen_pos VGA_cursor_pos = VGA_get_cursor_pos();
    VGA_cursor_pos.x = 0;
    VGA_cursor_pos.y++;
    // When we reach end of screen
    if (VGA_cursor_pos.y == VGA_current_rows)
    {
        // To current line we copy next line
        for (uint16_t i = 0; i < VGA_current_rows - 1; ++i)
        {
            for (uint16_t j = 0; j < VGA_current_columns; ++j)
            {
                uint16_t pos = __VGA_calcualte_position_with_offset(j, i);
                // Copy byte from next line
                VGA_video[pos] = VGA_video[pos + VGA_current_columns];
            }
        }
        VGA_cursor_pos.y = VGA_current_rows - 1;

        // Clear last line
        VGA_color col = __VGA_get_default_terminal_color(VGA_current_mode);
        for (uint16_t i = 0; i < VGA_current_columns; ++i)
        {
            uint16_t pos = __VGA_calcualte_position_with_offset(i, VGA_cursor_pos.y);
            // Clear
            VGA_video[pos].character.ascii_code = 0;
            VGA_video[pos].character.color = col;
        }
    }
    VGA_set_cursor_pos_struct(VGA_cursor_pos);
}

uint16_t __VGA_calcualte_position_with_offset(uint16_t x, uint16_t y)
{
    return (x + y * VGA_current_columns) + VGA_screen_offset;
}

uint16_t __VGA_calcualte_position_without_offset(uint16_t x, uint16_t y)
{
    return x + y * VGA_current_columns;
}

void __VGA_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void __VGA_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

VGA_color __VGA_get_default_terminal_color(uint8_t VGA_current_mode)
{
    VGA_color col;
    switch(VGA_current_mode)
    {
        case VGA_MODE_00H:
            col.color_without_blink.background = VGA_MODE_00H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_00H_COLOR_LIGHT_GRAY; 
            break;
        case VGA_MODE_01H:
            col.color_without_blink.background = VGA_MODE_01H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_01H_COLOR_LIGHT_GRAY;
            break;
        case VGA_MODE_02H:
            col.color_without_blink.background = VGA_MODE_02H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_02H_COLOR_LIGHT_GRAY;
            break;
        case VGA_MODE_03H:
            col.color_without_blink.background = VGA_MODE_03H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_03H_COLOR_LIGHT_GRAY;
            break;
        case VGA_MODE_07H:
            col.color_without_blink.background = VGA_MODE_07H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_07H_COLOR_LIGHT_GRAY;
            break;
        default:
            col.color_without_blink.background = VGA_MODE_03H_COLOR_BLACK;
            col.color_without_blink.letter = VGA_MODE_03H_COLOR_LIGHT_GRAY;
            break;
    }
    return col;
}