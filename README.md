# Taedium

Taedium (trans. Boredom) is an i686 monolithic kernel operating system I made out of pure boredom. Most code is... "borrowed" from the OS-Dev wiki's Bare-Bones tutorial.



# Building Taedium

To prepare for the build, you need to:

1. Make i686-elf cross compilers following [this](https://wiki.osdev.org/GCC_Cross-Compiler) guide 

2. Satisfy dependencies by running `getdeps.sh`

Afterwards, you should be able to run one of the scripts to build Taedium.

You need Cygwin or WSL to build Taedium on Windows.

# Scripts

## getdeps.sh

A script to check and install missing dependencies. This script does not install the cross compilers.

## testtd.sh

A script to build Taedium and test it using QEMU.

## testtd-rh.sh

A script to build Taedium and test it on real hardware by burning the ISO on a block device.

## makeiso.sh

A script to build Taedium and output an ISO.
