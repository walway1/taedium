all: taedium

taedium: targets/i386/iso/boot/linker.ld src/i386/boot/boot.o src/i386/boot/kernel.o src/i386/boot/vga_textmode.o
	i386-elf-gcc -T targets/i386/iso/boot/linker.ld -o taedium -ffreestanding -O2 -nostdlib src/i386/boot/boot.o src/i386/boot/kernel.o src/i386/boot/vga_textmode.o -fno-use-linker-plugin 
boot.o: src/i386/boot/boot.s
	i386-elf-as src/i386/boot/boot.s -o src/i386/boot/boot.o
kernel.o: src/i386/boot/kernel.c src/i386/boot/vga_textmode.h
	i386-elf-gcc -c src/i386/boot/kernel.c -o src/i386/boot/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I	src/i386/boot
vga_textmode.o: src/i386/boot/vga_textmode.c src/i386/boot/vga_textmode.h
	i386-elf-gcc -c src/i386/boot/vga_textmode.c -o src/i386/boot/vga_textmode.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I	src/i386/boot
clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "taedium" -delete
	find . -type f -name "Taedium" -delete
	rm -f taedium.iso
