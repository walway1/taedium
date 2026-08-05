#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main(void)
{

    *(volatile uint32_t*)0xB80BC = 0x0A4F0F5B;
    *(volatile uint32_t*)0xB80C0 = 0x0F5D0A4B;
 
}
 