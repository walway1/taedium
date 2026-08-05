#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga_textmode.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEM_BASE 0xB8000

enum VGA_COLORS {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
};

void VGA_CLEAR(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        *(volatile uint16_t*)(VGA_MEM_BASE + i * 2) = (BLACK << 12) | ' ';
    }
}