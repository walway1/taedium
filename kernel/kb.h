#ifndef KB_H
#define KB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern bool shift_pressed;
extern bool ctrl_pressed;
char scancode_to_char(uint8_t port, bool shift);
#endif
