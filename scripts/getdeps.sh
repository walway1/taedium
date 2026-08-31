#!/bin/bash

if command -v apt > /dev/null 2>&1; then
    sudo apt update
    sudo apt install grub-pc-bin grub-efi-amd64-bin xorriso qemu-system-x86
elif command -v dnf > /dev/null 2>&1; then
    sudo dnf install grub2-tools-extra grub2-efi-x64-modules xorriso qemu-system-x86-core
elif command -v zypper > /dev/null 2>&1; then
    sudo zypper install grub2 xorriso qemu-x86
elif command -v pacman > /dev/null 2>&1; then
    sudo pacman -S --needed grub libisoburn qemu-desktop
else
    echo "No known package manager found. Please notify the dev(s)."
    exit 1
fi

if ! command -v i686-elf-gcc > /dev/null 2>&1; then
    echo "i686-elf-gcc compiler not found. Please build one using this guide if you haven't: https://wiki.osdev.org/GCC_Cross-Compiler"
elif ! command -v i686-elf-as > /dev/null 2>&1; then
    echo "i686-elf-as compiler not found. Please build one using this guide if you haven't: https://wiki.osdev.org/GCC_Cross-Compiler"
elif ! command -v i686-elf-ld > /dev/null 2>&1; then
    echo "i686-elf-ld compiler not found. Please build one using this guide if you haven't: https://wiki.osdev.org/GCC_Cross-Compiler"
else
    while true; do
    read -p "All dependencies are satisfied. Attempt to build and test Taedium now? [Y/n]" yn1
case $yn1 in
    [Yy]* )
        ./testtd.sh
        exit 1
    ;;
    [Nn]* )
        echo "You can build and test anytime by running './testtd.sh'."
        exit 1
    ;;
    * )
    ;;
esac
done
fi
