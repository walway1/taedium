#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "term.h"
#include "main.h"
#include "kb.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

size_t trow = 0;
size_t tcol = 0;
uint8_t tcolor = 0;
uint16_t* term_buffer = (uint16_t*)VGA_MEMORY;
uint8_t read_port = 0;

void term_setcolor(uint8_t color)
{
    tcolor = color;
}

void term_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    term_buffer[index] = vga_entry(c, color);
}

void term_putchar(char c) {
    if (c != 0 && c != '\b') {
        term_putentryat(c, tcolor, tcol, trow);
        if (++tcol == VGA_WIDTH) {
            tcol = 0;
            if (++trow == VGA_HEIGHT)
                trow = 0;
        }
    }
    else if (c == '\b') {
        if (tcol != 1) { tcol -= 1; }
        term_putentryat(' ', tcolor, tcol, trow);
    }
}
void term_set_cursor(int row, int col) {
    uint16_t cursor_pos = row * 80 + col;

    asm_out(0x3D4, 0x0F);
    asm_out(0x3D5, (uint8_t)(cursor_pos & 0xFF));
    asm_out(0x3D4, 0x0E);
    asm_out(0x3D5, (uint8_t)((cursor_pos >> 8) & 0xFF));
}
void term_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        term_putchar(data[i]);
}
void term_cursor_sync(void) {
    term_set_cursor(trow, tcol);
}
void term_writestring(const char* data)
{
    term_write(data, strlen(data));
    term_cursor_sync();
}
void term_print_port(uint16_t port) {
    uint8_t val = asm_in(port);
    char buf[5];
    convert_hex(val, buf);
    term_write(buf, strlen(buf));
}
void term_fill(uint8_t color) {
    tcolor = color;
    trow = 0;
    tcol = 0;

    for (int i = 0; i < 80 * 25; i++) {
        term_putchar(' ');
    }

    trow = 0;
    tcol = 0;
    term_cursor_sync();
    return;
}


void term_kb_write(void) {
    if ((asm_in(0x64) & 1) == 0) {}
    uint8_t kb = asm_in(0x60);
    if (kb == 0x2A || kb == 0x36) { shift_pressed = 1; }
    if (kb == 0xAA || kb == 0xB6) { shift_pressed = 0; }
    if (kb == 0x1D) { ctrl_pressed = 1; }
    if (kb == 0x9D) { ctrl_pressed = 0; }
    if (kb == 0x23 && ctrl_pressed == 1) {
        trow = 12;
        tcol = 8;
        term_setcolor(vga_entry_color(VGA_RED, VGA_BLACK));
        term_writestring("Notice: You will have to restart your machine to un-halt the CPU.");
        hlt();
    }
    if (kb == 0x2E && ctrl_pressed == 1) {
        term_fill(vga_entry_color(VGA_WHITE, VGA_BLACK));
        return;
    }
    term_putchar(scancode_to_char(0x60, shift_pressed));
    term_cursor_sync();

}
void term_init(void)
{

    trow = 2;
    tcol = 0;
    term_setcolor(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
    term_writestring("-------------------------");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
    term_writestring("Welcome to Taedium v0.0.3 Alpha");
    term_setcolor(vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK));
    term_writestring("------------------------");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
    term_writestring("Taedium (trans. Boredom) is an i686 monolithic kernel written in C based on the OS-Dev Wiki Bare-Bones tutorial. It is a hobby project with no means of becomingwidely used.");
    trow += 1;
    tcol = 0;
    term_writestring("Press ");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_RED));
    term_writestring("Ctrl + H");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
    term_writestring(" to halt the CPU and ");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_RED));
    term_writestring("Ctrl + C");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
    term_writestring(" to clear the screen.");
    trow += 1;
    tcol = 0;
    term_setcolor(vga_entry_color(VGA_LIGHT_GREEN, VGA_BLACK));
    term_writestring("Taedium>");
    term_setcolor(vga_entry_color(VGA_WHITE, VGA_BLACK));
    term_cursor_sync();
}
