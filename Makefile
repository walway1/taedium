cc = i686-elf-gcc 
as = i686-elf-as 
c = src/i686/boot/kernel.c 
asm = src/i686/boot/boot.s
ld = targets/i686/iso/boot/linker.ld
all: taedium

taedium: $(ld) src/i686/boot/boot.o src/i686/boot/kernel.o 
	$(cc) -T $(ld) -o taedium -ffreestanding -nostdlib src/i686/boot/boot.o src/i686/boot/kernel.o  -fno-use-linker-plugin 
src/i686/boot/boot.o: src/i686/boot/boot.s
	$(as) src/i686/boot/boot.s -o src/i686/boot/boot.o
src/i686/boot/kernel.o: src/i686/boot/kernel.c
	$(cc) -c src/i686/boot/kernel.c -o src/i686/boot/kernel.o -std=gnu99 -ffreestanding -Wall -Wextra -I	src/i686/boot
clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "taedium" -delete
	find . -type f -name "Taedium" -delete
	rm -f taedium.iso
 
