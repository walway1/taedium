#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LIGHT_GREY = 7,
	VGA_DARK_GREY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_LIGHT_BROWN = 14,
	VGA_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}




#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t term_row;
size_t term_column;
uint8_t term_color;
uint16_t* term_buffer = (uint16_t*)VGA_MEMORY;

void term_init(void) 
{
	term_row = 0;
	term_column = 0;
	term_color = vga_entry_color(VGA_WHITE, VGA_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			term_buffer[index] = vga_entry(' ', term_color);
		}
	}
}

void term_setcolor(uint8_t color) 
{
	term_color = color;
}

void term_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	term_buffer[index] = vga_entry(c, color);
}

void term_putchar(char c) 
{
	term_putentryat(c, term_color, term_column, term_row);
	if (++term_column == VGA_WIDTH) {
		term_column = 0;
		if (++term_row == VGA_HEIGHT)
			term_row = 0;
	}
}

void term_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		term_putchar(data[i]);
}

void term_writestring(const char* data) 
{
	term_write(data, strlen(data));
}
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
void term_update_cursor(int row, int col) {
    uint16_t cursor_pos = row * 80 + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(cursor_pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((cursor_pos >> 8) & 0xFF));
}
static inline uint8_t asm_in(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
void convert_hex(uint8_t data, char *out) {
	const char hex_chars[] = "0123456789ABCDEF";
	out[0] = '0';
	out[1] = 'x';
	out[2] = hex_chars[(data >> 4) & 0xF];
	out[3] = hex_chars[data & 0xF];
	out[4] = '\0';

}
void term_print_port(uint16_t port) {
	uint8_t val = asm_in(port);
	char buf[5];
	convert_hex(val, buf);
	term_write(buf, strlen(buf));
}
void kernel_main(void) 
{
	*(volatile uint32_t*)0xB80BC = 0x0A4F0F5B;
    *(volatile uint32_t*)0xB80C0 = 0x0F5D0A4B;
	term_row = 2;
	term_column = 0;
	term_setcolor(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
	term_writestring("-------------------------");
	term_column = 24;
	term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
	term_writestring("Welcome to Taedium v0.0.2 Alpha");
	term_column = 55;
	term_setcolor(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
	term_writestring("--------------------------");
	term_row = 3;
	term_column = 0;
	term_setcolor(vga_entry_color(VGA_LIGHT_GREEN, VGA_BLACK));
	term_update_cursor(3, 8);
	term_writestring("Taedium>");
	term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
	term_print_port(0x60);
	size_t loop;
	while (true) {
		if (loop < 10000) {
			loop += 1;
		}
		else {
			term_row = 3;
			term_column = 8;
			term_print_port(0x60);
			loop = 0;
		}
	}
		
}
