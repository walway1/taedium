# Taedium
Taedium (trans. Boredom) is an i686 monolithic kernel operating system I made out of pure boredom. Most code is... "borrowed" from the OS-Dev wiki's Bare-Bones tutorial.
## How to compile Taedium
To compile Taedium, you need an i686-elf c, ld and asm compiler. See [this](https://wiki.osdev.org/GCC_Cross-Compiler) guide on building your own i686-elf compilers. After, you can just run ``make -j$(nproc) && ./makeiso.sh`` to make a bootable iso. If you want to burn it to a USB stick to test on real hardware, you can run ``./testiso-rh.sh``
