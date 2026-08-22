make clean
make -j$(nproc)
./makeiso.sh
qemu-system-x86_64 -cdrom taedium.iso
