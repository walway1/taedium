mv ../taedium ../iso/boot/Taedium
mflags=""
while getopts ":f" option "$@"; do
	case $option in
		f)
			mflags="biosdisk memdisk multiboot normal play part_msdos"
			;;
		*)
			mflags="biosdisk iso9660 multiboot normal play part_msdos"
			;;
	esac
done

if [ -z "$mflags" ]; then
	mflags="biosdisk iso9660 multiboot normal play part_msdos"
fi
if ! type "grub2-mkrescue" > /dev/null; then
	grub-mkrescue -o ../taedium.iso ../iso/ \
		--locales="" \
		--fonts="" \
		--directory=/usr/lib/grub/i386-pc \
		--install-modules="$mflags"
else
	grub2-mkrescue -o ../taedium.iso ../iso/ \
		--locales="" \
		--fonts="" \
		--directory=/usr/lib/grub/i386-pc \
		--install-modules="$mflags"
fi
