#!/bin/bash

qflags="-audiodev alsa,id=snd0 -machine pcspk-audiodev=snd0"
qemu="qemu-system-x86_64"
miflags=""
rebuild="1"
while [[ $# -gt 0 ]]; do
    case "$1" in
		-h|--help)
            echo "Flags for testtd.sh
        -h, --help
            Display this help message
        -i, --i386
            Use qemu-system-i386 instead of qemu-system-x86_64
        -nb, --no-buzzer
            Disable PC speaker emulation in QEMU
        -nr, --no-rebuild
            Launch QEMU without rebuilding Taedium
        --miflags [flags]
            Pass flags to makeiso.sh"
            exit 0
			;;
        -i|--i386)
            qemu="qemu-system-i386"
            shift
            ;;
        -nb|--no-buzzer)
            qflags=""
            shift
            ;;
        --miflags)
            if [ -z "$2" ]; then
                echo "Error: Must provide flags to pass to ./makeiso.sh if --miflags is used"
                exit 1
            fi
                miflags="$2"
                shift 2
            ;;
        -nr|--no-rebuild)
            rebuild="0"
            if [ -n "$miflags" ]; then
                echo "Error: -nr and --miflags cannot be used together"
                exit 1
            fi
            shift
            ;;
        *)
            echo "Error: Unknown flag '$1'"
            exit 1
            ;;
esac
done
cd ..
if [ $rebuild == 1 ]; then
    make clean
    make -j$(nproc)
    if [ $? -ne 0 ]; then
        exit 1
    else
        cd scripts/
        ./makeiso.sh $miflags
        $qemu -cdrom ../taedium.iso $qflags
    fi
else
    $qemu -cdrom taedium.iso $qflags
fi


