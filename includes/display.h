#ifndef     DISPLAY_H_
#define     DISPLAY_H_

#include    "vga.h"

int terminal_putnbr(int n);

void terminal_initialize(void);

void terminal_setcolor(u8 color);

void terminal_putentryat(char c, u8 color, u32 x, u32 y);

void terminal_putchar(char c);

void terminal_write(const char* data, u32 size);

void terminal_writestring(const char* data);

#endif