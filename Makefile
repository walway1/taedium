CC = i686-elf-gcc
AS = i686-elf-as
C = kernel/main.c kernel/kb.c kernel/term.c
CH = kernel/main.h kernel/kb.h kernel/term.h kernel/vga.h
OBJ = kernel/main.o kernel/kb.o kernel/term.o boot/boot.o
LD = iso/boot/linker.ld
all: taedium

taedium: $(OBJ)
	$(CC) -T $(LD) -o taedium -ffreestanding -nostdlib $(OBJ) -fno-use-linker-plugin
boot/boot.o: boot/boot.s
	$(AS) boot/boot.s -o boot/boot.o
kernel/%.o: kernel/%.c
	$(CC) -c $< -o $@ -s -std=gnu99 -ffreestanding -Wall -Wextra -I kernel/
clean:
	find . -type f -name "*.o" -delete
	find . -type f -iname "taedium" -delete
	rm -rf taedium.iso
configure:
	@echo "This project isn't that advanced yet :)"
