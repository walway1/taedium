#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#include "vga.h"
#include "term.h"
#include "kb.h"
#include "main.h"

bool shift_pressed = 0;
bool ctrl_pressed = 0;

char scancode_to_char(uint8_t port, bool shift) {
	uint8_t kbport = asm_in(port);
	switch (kbport) {
		case 0x10: return shift ? 'Q' : 'q';
		case 0x11: return shift ? 'W' : 'w';
		case 0x12: return shift ? 'E' : 'e';
		case 0x13: return shift ? 'R' :	'r';
		case 0x14: return shift ? 'T' : 't';
		case 0x15: return shift ? 'Y' : 'y';
		case 0x16: return shift ? 'U' : 'u';
		case 0x17: return shift ? 'I' : 'i';
		case 0x18: return shift ? 'O' : 'o';
		case 0x19: return shift ? 'P' : 'p';
		case 0x1A: return shift ? '{' : '[';
		case 0x1B: return shift ? '}' : ']';
		case 0x1E: return shift ? 'A' : 'a';
		case 0x1F: return shift ? 'S' : 's';
		case 0x20: return shift ? 'D' : 'd';
		case 0x21: return shift ? 'F' : 'f';
		case 0x22: return shift ? 'G' : 'g';
		case 0x23: return shift ? 'H' : 'h';
		case 0x24: return shift ? 'J' : 'j';
		case 0x25: return shift ? 'K' : 'k';
		case 0x26: return shift ? 'L' : 'l';
		case 0x27: return shift ? ':' : ';';
		case 0x28: return shift ? '"' : '\'';
		case 0x29: return shift ? '~' : '`';
		case 0x2B: return shift ? '|' : '\\';
		case 0x2C: return shift ? 'Z' : 'z';
		case 0x2D: return shift ? 'X' : 'x';
		case 0x2E: return shift ? 'C' : 'c';
		case 0x2F: return shift ? 'V' : 'v';
		case 0x30: return shift ? 'B' : 'b';
		case 0x31: return shift ? 'N' : 'n';
		case 0x32: return shift ? 'M' : 'm';
		case 0x33: return shift ? '<' : ',';
		case 0x34: return shift ? '>' : '.';
		case 0x35: return shift ? '?' : '/';
		case 0x39: return ' ' ;
		case 0x0E: return '\b' ;
		default: return 0;
	}
}
