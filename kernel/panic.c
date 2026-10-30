#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "term.h"
#include "vga.h"
#include "panic.h"
#include "main.h"

void panic(uint8_t err) {
    term_fill(vga_entry_color(VGA_YELLOW, VGA_BLACK));
    trow = 0;
    tcolor = vga_entry_color(VGA_BLACK, VGA_YELLOW);
    for (int i = 0; i < 32; i++) {term_writestring("P A N I C ");}
    trow = 21;
    for (int i = 0; i < 32; i++) {term_writestring("P A N I C ");}
    trow = 4;
    tcolor = vga_entry_color(VGA_WHITE, VGA_BLACK);
    term_writestring("KERNEL PANIC!! Please reboot.");
    trow +=1;
    tcol = 0;
    term_writestring("Error code ");
    char buf[5];
    convert_hex(err, buf);
    term_write(buf, strlen(buf));
    if (err == 1) {
        term_writestring(": Manually triggered panic");
    }
    else {
        term_writestring(": Unknown reason");
    }
    term_setcursor(80, 25);
    hlt();
}
