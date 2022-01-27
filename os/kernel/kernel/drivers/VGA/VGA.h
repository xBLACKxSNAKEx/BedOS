#pragma once
#include "x86.h"


enum VGA_TEXT_MODES
{
    VGA_MODE_00H = 0x00, /*!< VGA mode 00h. */
    VGA_MODE_01H = 0x01, /*!< VGA mode 01h. */
    VGA_MODE_02H = 0x02, /*!< VGA mode 02h. */
    VGA_MODE_03H = 0x03, /*!< VGA mode 03h. */
    VGA_MODE_07H = 0x07  /*!< VGA mode 07h. */
};

// Mode 00h

//! The base memory address for mode 00h.
#define VGA_MODE_00H_BASE_ADDR              0xB8000
//! The number of columns in mode 00h.
#define VGA_MODE_00H_SCREEN_COLUMNS         40
//! The number of rows in mode 00h.
#define VGA_MODE_00H_SCREEN_ROWS            25

#define VGA_MODE_00H_COLOR_BLACK            0x00
#define VGA_MODE_00H_COLOR_BLUE             0x01
#define VGA_MODE_00H_COLOR_GREEN            0x02
#define VGA_MODE_00H_COLOR_CYAN             0x03
#define VGA_MODE_00H_COLOR_RED              0x04
#define VGA_MODE_00H_COLOR_MAGENTA          0x05
#define VGA_MODE_00H_COLOR_BROWN            0x06
#define VGA_MODE_00H_COLOR_LIGHT_GRAY       0x07
#define VGA_MODE_00H_COLOR_DARK_GRAY        0x08
#define VGA_MODE_00H_COLOR_LIGHT_BLUE       0x09
#define VGA_MODE_00H_COLOR_LIGHT_GREEN      0x0A
#define VGA_MODE_00H_COLOR_LIGHT_CYAN       0x0B
#define VGA_MODE_00H_COLOR_LIGHT_RED        0x0C
#define VGA_MODE_00H_COLOR_LIGHT_MAGENTA    0x0D
#define VGA_MODE_00H_COLOR_YELLOW           0x0E
#define VGA_MODE_00H_COLOR_WHITE            0x0F
#define VGA_MODE_00H_NOT_BLINK              0x00
#define VGA_MODE_00H_BLINK                  0x01

#define VGA_MODE_00H_MAX_SCREENS            8
#define VGA_MODE_00H_SCREEN_OFFSET          4000

// Mode 01h

//! The base memory address for mode 01h.
#define VGA_MODE_01H_BASE_ADDR              0xB8000
//! The number of columns in mode 01h.
#define VGA_MODE_01H_SCREEN_COLUMNS         40
//! The number of rows in mode 01h.
#define VGA_MODE_01H_SCREEN_ROWS            25

#define VGA_MODE_01H_COLOR_BLACK            0x00
#define VGA_MODE_01H_COLOR_BLUE             0x01
#define VGA_MODE_01H_COLOR_GREEN            0x02
#define VGA_MODE_01H_COLOR_CYAN             0x03
#define VGA_MODE_01H_COLOR_RED              0x04
#define VGA_MODE_01H_COLOR_MAGENTA          0x05
#define VGA_MODE_01H_COLOR_BROWN            0x06
#define VGA_MODE_01H_COLOR_LIGHT_GRAY       0x07
#define VGA_MODE_01H_COLOR_DARK_GRAY        0x08
#define VGA_MODE_01H_COLOR_LIGHT_BLUE       0x09
#define VGA_MODE_01H_COLOR_LIGHT_GREEN      0x0A
#define VGA_MODE_01H_COLOR_LIGHT_CYAN       0x0B
#define VGA_MODE_01H_COLOR_LIGHT_RED        0x0C
#define VGA_MODE_01H_COLOR_LIGHT_MAGENTA    0x0D
#define VGA_MODE_01H_COLOR_YELLOW           0x0E
#define VGA_MODE_01H_COLOR_WHITE            0x0F
#define VGA_MODE_01H_NOT_BLINK              0x00
#define VGA_MODE_01H_BLINK                  0x01

#define VGA_MODE_01H_MAX_SCREENS            8
#define VGA_MODE_01H_SCREEN_OFFSET          4000

// Mode 02h

//! The base memory address for mode 02h.
#define VGA_MODE_02H_BASE_ADDR              0xB8000
//! The number of columns in mode 02h.
#define VGA_MODE_02H_SCREEN_COLUMNS         80
//! The number of rows in mode 02h.
#define VGA_MODE_02H_SCREEN_ROWS            25

#define VGA_MODE_02H_COLOR_BLACK            0x00
#define VGA_MODE_02H_COLOR_BLUE             0x01
#define VGA_MODE_02H_COLOR_GREEN            0x02
#define VGA_MODE_02H_COLOR_CYAN             0x03
#define VGA_MODE_02H_COLOR_RED              0x04
#define VGA_MODE_02H_COLOR_MAGENTA          0x05
#define VGA_MODE_02H_COLOR_BROWN            0x06
#define VGA_MODE_02H_COLOR_LIGHT_GRAY       0x07
#define VGA_MODE_02H_COLOR_DARK_GRAY        0x08
#define VGA_MODE_02H_COLOR_LIGHT_BLUE       0x09
#define VGA_MODE_02H_COLOR_LIGHT_GREEN      0x0A
#define VGA_MODE_02H_COLOR_LIGHT_CYAN       0x0B
#define VGA_MODE_02H_COLOR_LIGHT_RED        0x0C
#define VGA_MODE_02H_COLOR_LIGHT_MAGENTA    0x0D
#define VGA_MODE_02H_COLOR_YELLOW           0x0E
#define VGA_MODE_02H_COLOR_WHITE            0x0F
#define VGA_MODE_02H_NOT_BLINK              0x00
#define VGA_MODE_02H_BLINK                  0x01

#define VGA_MODE_02H_MAX_SCREENS            8
#define VGA_MODE_02H_SCREEN_OFFSET          4000

// Mode 03h

//! The base memory address for mode 03h.
#define VGA_MODE_03H_BASE_ADDR              0xB8000
//! The number of columns in mode 03h.
#define VGA_MODE_03H_SCREEN_COLUMNS         80
//! The number of rows in mode 03h.
#define VGA_MODE_03H_SCREEN_ROWS            25

#define VGA_MODE_03H_COLOR_BLACK            0x00
#define VGA_MODE_03H_COLOR_BLUE             0x01
#define VGA_MODE_03H_COLOR_GREEN            0x02
#define VGA_MODE_03H_COLOR_CYAN             0x03
#define VGA_MODE_03H_COLOR_RED              0x04
#define VGA_MODE_03H_COLOR_MAGENTA          0x05
#define VGA_MODE_03H_COLOR_BROWN            0x06
#define VGA_MODE_03H_COLOR_LIGHT_GRAY       0x07
#define VGA_MODE_03H_COLOR_DARK_GRAY        0x08
#define VGA_MODE_03H_COLOR_LIGHT_BLUE       0x09
#define VGA_MODE_03H_COLOR_LIGHT_GREEN      0x0A
#define VGA_MODE_03H_COLOR_LIGHT_CYAN       0x0B
#define VGA_MODE_03H_COLOR_LIGHT_RED        0x0C
#define VGA_MODE_03H_COLOR_LIGHT_MAGENTA    0x0D
#define VGA_MODE_03H_COLOR_YELLOW           0x0E
#define VGA_MODE_03H_COLOR_WHITE            0x0F
#define VGA_MODE_03H_NOT_BLINK              0x00
#define VGA_MODE_03H_BLINK                  0x01

#define VGA_MODE_03H_MAX_SCREENS            8
#define VGA_MODE_03H_SCREEN_OFFSET          4000

// Mode 07h

//! The base memory address for mode 07h.
#define VGA_MODE_07H_BASE_ADDR              0xB0000
//! The number of columns in mode 07h.
#define VGA_MODE_07H_SCREEN_COLUMNS         80
//! The number of rows in mode 07h.
#define VGA_MODE_07H_SCREEN_ROWS            25

#define VGA_MODE_07H_COLOR_BLACK            0x00
#define VGA_MODE_07H_COLOR_BLUE             0x01
#define VGA_MODE_07H_COLOR_GREEN            0x02
#define VGA_MODE_07H_COLOR_CYAN             0x03
#define VGA_MODE_07H_COLOR_RED              0x04
#define VGA_MODE_07H_COLOR_MAGENTA          0x05
#define VGA_MODE_07H_COLOR_BROWN            0x06
#define VGA_MODE_07H_COLOR_LIGHT_GRAY       0x07
#define VGA_MODE_07H_COLOR_DARK_GRAY        0x08
#define VGA_MODE_07H_COLOR_LIGHT_BLUE       0x09
#define VGA_MODE_07H_COLOR_LIGHT_GREEN      0x0A
#define VGA_MODE_07H_COLOR_LIGHT_CYAN       0x0B
#define VGA_MODE_07H_COLOR_LIGHT_RED        0x0C
#define VGA_MODE_07H_COLOR_LIGHT_MAGENTA    0x0D
#define VGA_MODE_07H_COLOR_YELLOW           0x0E
#define VGA_MODE_07H_COLOR_WHITE            0x0F
#define VGA_MODE_07H_NOT_BLINK              0x00
#define VGA_MODE_07H_BLINK                  0x01

#define VGA_MODE_07H_MAX_SCREENS            1
#define VGA_MODE_07H_SCREEN_OFFSET          4000

// Struct that defines position on screen.
typedef struct VGA_screen_pos
{
    //! Position x on screen.
    uint16_t x;
    //! Position y on screen.
    uint16_t y;
} VGA_screen_pos;

/* Struct defining color and background of the letter in blinking mode.
Struct contains 4 bits of letter color, 3 bits of background color and 1 bit for indication of blinking character.*/
typedef struct VGA_color_with_blink
{
    // Color of letter.
    unsigned char letter : 4;
    // Color of background.
    unsigned char background : 3;
    // Flag for enable blinking.
    unsigned char blikning : 1;
} VGA_color_with_blink;

/* Struct defining color and background of the letter in non blinking mode.
Struct contains 4 bits of letter color and 4 bits of background color.*/
typedef struct VGA_color_without_blink
{
    // Color of letter.
    unsigned char letter : 4;
    // Color of background.
    unsigned char background : 4;
} VGA_color_without_blink;

// Color of one character.
/* Union that defines color of one character and it's background. When you use blinking mode you should use
`color_with_blink` field and when you use non blinking mode you should use `color_without_blink` field.*/
typedef union VGA_color {
    // Uses to define color in blinking mode.
    VGA_color_with_blink color_with_blink;
    // Uses to define color in non blinking mode.
    VGA_color_without_blink color_without_blink;
    // Uses to define color as value.
    uint8_t value;
} VGA_color;

// Struct that define one character.
/* Contains code of letter and it's color.*/
typedef struct VGA_character
{
    // ASCII code of letter.
    unsigned char ascii_code;
    // Color of letter and background. In blinking mode also include blinking flag.
    VGA_color color;
} VGA_character;

typedef union screen_char {
    //! 16 bit value of field.
    uint16_t value;
    //! Struct contains ASCII code and color data.
    VGA_character character;
} screen_char;

uint8_t VGA_init(uint8_t mode);

void VGA_print_char(char character);
void VGA_print_char_color(char character, VGA_color *color);

void VGA_newline();

void VGA_print_string(const char *str);
void VGA_print_string_color(const char *str, VGA_color *color);

void VGA_set_char(uint16_t x, uint16_t y, char character);
void VGA_set_char_struct(VGA_screen_pos spos, char character);

char vga_get_char(uint16_t x, uint16_t y);
char vga_get_char_struct(VGA_screen_pos spos);

void vga_set_color(uint16_t x, uint16_t y, VGA_color col);
void vga_set_color_struct(VGA_screen_pos spos, VGA_color col);

union vga_color vga_get_color(uint16_t x, uint16_t y);
union vga_color vga_get_color_struct(VGA_screen_pos spos);

void VGA_set_character(uint16_t x, uint16_t y, VGA_character character);
void VGA_set_character_struct(VGA_screen_pos spos, VGA_character character);

VGA_character VGA_get_character(uint16_t x, uint16_t y);
VGA_character VGA_get_character_struct(VGA_screen_pos spos);

void VGA_clear_screen();
void VGA_clear_all_screens();

void VGA_enable_cursor();
void VGA_disable_cursor();

void VGA_set_cursor_pos(uint16_t x, uint16_t y);
void VGA_set_cursor_pos_struct(VGA_screen_pos spos);
VGA_screen_pos VGA_get_cursor_pos();

uint16_t __VGA_calcualte_position_with_offset(uint16_t x, uint16_t y);
uint16_t __VGA_calcualte_position_without_offset(uint16_t x, uint16_t y);
void __VGA_enable_cursor(uint8_t, uint8_t);
void __VGA_disable_cursor();
void __move_cursor(uint16_t pos);
VGA_color __VGA_get_default_terminal_color(uint8_t VGA_current_mode);