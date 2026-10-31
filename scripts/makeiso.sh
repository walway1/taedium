#!/bin/bash

mflags="biosdisk multiboot normal part_msdos"
j="play"
medium="iso9660"
modules=""
while [[ $# -gt 0 ]]; do
    case "$1" in
		-h|--help)
			echo "Flags for makeiso.sh:
	-f, --floppy
		Build ISO for a floppy disk instead of a CD/DVD/USB
		Warning: Will not work on 720KB DD floppies
	-nj, --no-jingle
		Build ISO without the startup jingle (saves 4KiB)"
			exit 0
			;;
		-f|--floppy)
			medium="memdisk"
			shift
			;;
		-nj|--no-jingle)
			j=""
			shift
			;;
		*)
			echo "Error: Unknown flag '$1'"
			exit 1
			;;
	esac
done
modules="$mflags $j $medium"
mv ../taedium ../iso/boot/Taedium
if ! type "grub2-mkrescue" > /dev/null; then
	grub-mkrescue -o ../taedium.iso ../iso/ \
		--locales="" \
		--fonts="" \
		--directory=/usr/lib/grub/i386-pc \
		--install-modules="$modules"
else
	grub2-mkrescue -o ../taedium.iso ../iso/ \
		--locales="" \
		--fonts="" \
		--directory=/usr/lib/grub/i386-pc \
		--install-modules="$modules"
fi
