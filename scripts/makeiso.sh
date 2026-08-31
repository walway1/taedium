mv ../taedium ../iso/boot/Taedium

if ! type "grub2-mkrescue" > /dev/null; then
	grub-mkrescue -o ../taedium.iso ../iso/
else
	grub2-mkrescue -o ../taedium.iso ../iso/
fi
