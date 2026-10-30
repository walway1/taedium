cd ..
make clean
make -j$(nproc)
if [ $? -ne 0 ]; then
    exit 1
else
    cd scripts/
    ./makeiso.sh
    qemu-system-x86_64 -cdrom ../taedium.iso -audiodev alsa,id=snd0 -machine pcspk-audiodev=snd0
fi
