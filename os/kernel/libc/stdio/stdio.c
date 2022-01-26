#include "stdio.h"

void putc(char c)
{
    VGA_print_char(c);
}

void puts(const char *str)
{
    while (*str)
    {
        putc(*str);
        str++;
    }
}

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_FLAGS 1
#define PRINTF_STATE_WIDTH 2
#define PRINTF_STATE_PRECISION 3
#define PRINTF_STATE_LENGTH 4
#define PRINTF_STATE_SPECIFIER 5

#define PRINTF_LENGTH_DEFAULT 0
#define PRINTF_LENGTH_SHORT 1
#define PRINTF_LENGTH_SHORT_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4
#define PRINTF_LENGTH_SIZE_T 5

int *printf_number(int *argp, int length, bool sign, int radix, bool toUpperCase);

void _cdecl printf(const char *fmt, ...)
{
    int state = PRINTF_STATE_NORMAL;
    int length = PRINTF_LENGTH_DEFAULT;
    bool sign = false;
    int radix = 10;
    int *argp = (int *)&fmt;
    argp++;

    while (*fmt)
    {
        switch (state)
        {
        case PRINTF_STATE_NORMAL:
            if (*fmt == '%')
                state = PRINTF_STATE_LENGTH;
            else
                putc(*fmt);
            fmt++;
            break;

        case PRINTF_STATE_LENGTH:
            switch (*fmt)
            {
            case 'h':
                length = PRINTF_LENGTH_SHORT;
                fmt++;
                if (*fmt == 'h')
                {
                    length = PRINTF_LENGTH_SHORT_SHORT;
                    fmt++;
                }
                break;

            case 'l':
                length = PRINTF_LENGTH_LONG;
                fmt++;
                if (*fmt == 'l')
                {
                    length = PRINTF_LENGTH_LONG_LONG;
                    fmt++;
                }
                break;

            case 'z':
                length = PRINTF_LENGTH_SIZE_T;
                fmt++;
                break;

            default:
                length = PRINTF_LENGTH_DEFAULT;
                break;
            }
            state = PRINTF_STATE_SPECIFIER;
            break;

        case PRINTF_STATE_SPECIFIER:
            switch (*fmt)
            {
            case 'd':
            case 'i':
                radix = 10;
                sign = true;
                argp = printf_number(argp, length, sign, radix, false);
                length = PRINTF_LENGTH_DEFAULT;
                break;

            case 'u':
                radix = 10;
                sign = false;
                argp = printf_number(argp, length, sign, radix, false);
                length = PRINTF_LENGTH_DEFAULT;
                break;
            case 'o':
                radix = 8;
                sign = false;
                argp = printf_number(argp, length, sign, radix, false);
                length = PRINTF_LENGTH_DEFAULT;
                break;
            case 'p':
                radix = 16;
                sign = false;
                argp = printf_number(argp, length, sign, radix, false);
                length = PRINTF_LENGTH_DEFAULT;
                break;
            case 'x':
                radix = 16;
                sign = false;
                argp = printf_number(argp, length, sign, radix, false);
                length = PRINTF_LENGTH_DEFAULT;
                break;
            case 'X':
                radix = 16;
                sign = false;
                argp = printf_number(argp, length, sign, radix, true);
                length = PRINTF_LENGTH_DEFAULT;
                break;
            case 'c':
                putc((char)*argp);
                argp++;
                break;
            case 's':
                puts((char *)*argp);
                argp++;
                break;
            case '%':
                putc('%');
                break;
            }
            fmt++;
            state = PRINTF_STATE_NORMAL;
            break;
        }
    }
}

const char g_HexChars[] = "0123456789abcdef";
const char g_HexChars_u[] = "0123456789ABCDEF";

int *printf_number(int *argp, int length, bool sign, int radix, bool toUpperCase)
{
    char buffer[32];
    unsigned long long number = 0;
    int number_sign = 1;
    int pos = 0;

    // process length
    switch (length)
    {
    case PRINTF_LENGTH_SHORT_SHORT:
    case PRINTF_LENGTH_SHORT:
    case PRINTF_LENGTH_DEFAULT:
        if (sign)
        {
            int n = *argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned int *)argp;
        }
        argp++;
        break;

    case PRINTF_LENGTH_LONG:
        if (sign)
        {
            long int n = *(long int *)argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long int *)argp;
        }
        argp += sizeof(unsigned long int)/sizeof(int);
        break;

    case PRINTF_LENGTH_LONG_LONG:
        if (sign)
        {
            long long int n = *(long long int *)argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long long int *)argp;
        }
        argp += sizeof(unsigned long long int)/sizeof(int);
        break;
    }

    // convert number to ASCII
    do
    {
        uint32_t rem = number % radix;
        number /= radix;
        if (toUpperCase)
            buffer[pos++] = g_HexChars_u[rem];
        else
            buffer[pos++] = g_HexChars[rem];
    } while (number > 0);

    // add sign
    if (sign && number_sign < 0)
        buffer[pos++] = '-';

    // print number in reverse order
    while (--pos >= 0)
        putc(buffer[pos]);

    return argp;
}