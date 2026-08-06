cc = i686-elf-gcc 
as = i686-elf-as 
c = src/i386/boot/kernel.c 
asm = src/i386/boot/boot.s
ld = targets/i386/iso/boot/linker.ld
all: taedium

taedium: $(ld) src/i386/boot/boot.o src/i386/boot/kernel.o 
	$(cc) -T $(ld) -o taedium -ffreestanding -nostdlib src/i386/boot/boot.o src/i386/boot/kernel.o  -fno-use-linker-plugin 
src/i386/boot/boot.o: src/i386/boot/boot.s
	$(as) src/i386/boot/boot.s -o src/i386/boot/boot.o
src/i386/boot/kernel.o: src/i386/boot/kernel.c
	$(cc) -c src/i386/boot/kernel.c -o src/i386/boot/kernel.o -std=gnu99 -ffreestanding -Wall -Wextra -I	src/i386/boot
clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "taedium" -delete
	find . -type f -name "Taedium" -delete
	rm -f taedium.iso
 
