#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#include "vga.h"
#include "term.h"
#include "kb.h"
#include "main.h"


size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void convert_hex(uint8_t data, char *out) {
	const char hex_chars[] = "0123456789ABCDEF";
	out[0] = '0';
	out[1] = 'x';
	out[2] = hex_chars[(data >> 4) & 0xF];
	out[3] = hex_chars[data & 0xF];
	out[4] = '\0';

}

void hlt(void){
	__asm__ volatile ("hlt");
}

void kernel_main(void) {
	*(volatile uint32_t*)0xB80BC = 0x0A4F0F5B;
	*(volatile uint32_t*)0xB80C0 = 0x0F5D0A4B;
	term_init();
	while (true) {
		for (volatile uint32_t i = 0; i < 35000000; i++) {}
		term_kb_write();
	}
}


// May this program compile flawlessly with zero bugs from now until ever, AMEN! 
