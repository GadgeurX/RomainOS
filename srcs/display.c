#include    "display.h"
#include    "libc.h"

u32         terminal_row;
u32         terminal_column;
u8          terminal_color;
u16*        terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (u16*) 0xB8000;
	for (u32 y = 0; y < VGA_HEIGHT; y++) {
		for (u32 x = 0; x < VGA_WIDTH; x++) {
			const u32 index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(u8 color) {
	terminal_color = color;
}

void terminal_putentryat(char c, u8 color, u32 x, u32 y) {
	const u32 index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    if (c == '\n')
    {
        terminal_column = 0;
        terminal_row++;
        return;
    }
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, u32 size) {
	for (u32 i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

int terminal_putnbr(int n)
{
    if (n < 0)
    {
        terminal_putchar('-');
        n = -n;
    }
    if (n >= 10)
    {
        terminal_putnbr(n / 10);
        terminal_putchar(n % 10 + '0');
    }
    if (n < 10)
    {
        terminal_putchar(n % 10 + '0');
    }
    return (n);
}