.code32

.set ALIGN,	1<<0 
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGICNO,	0x1BADB002
.set CHECKSUM, -(MAGICNO + FLAGS)

.section .mboot
.align 4
.long MAGICNO
.long FLAGS
.long CHECKSUM

/* everything above here is multiboot stuff, NOT multiboot2 */


.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


.section .text
.global _start
.type _start, @function
_start:
mov $stack_top, %esp
movl $0x0F6F0F42, 0xB8000 /* Write "Boot... [OK]" SystemD style */
movl $0x0F740F6F, 0xB8004
movl $0x0F2E0F2E, 0xB8008
movl $0x0F200F2E, 0xB800C
movl $0x0A4F0F5B, 0xB8010
movl $0x0F5D0A4B, 0xB8014
movl $0x0F6F0F4C, 0xB80A0
movl $0x0F640F61, 0xB80A4
movl $0x0F4B0020, 0xB80A8
movl $0x0F720F65, 0xB80AC
movl $0x0F650F6E, 0xB80B0
movl $0x0F2E0F6C, 0xB80B4
movl $0x0F2E0F2E, 0xB80B8


call kernel_main
cli
1:  hlt
jmp 1b
.size _start, . - _start
