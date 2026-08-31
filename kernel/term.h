#ifndef TERM_H
#define TERM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

extern size_t trow;
extern size_t tcol;
extern uint8_t tcolor;
extern uint16_t* term_buffer;
extern uint8_t read_port;
void term_setcolor(uint8_t color);
void term_putentryat(char c, uint8_t color, size_t x, size_t y);
void term_putchar(char c);
void term_set_cursor(int row, int col);
void term_write(const char* data, size_t size);
void term_cursor_sync(void);
void term_writestring(const char* data);
void term_print_port(uint16_t port);
void term_fill(uint8_t color);
void term_kb_write(void);
void term_init(void);

#endif
