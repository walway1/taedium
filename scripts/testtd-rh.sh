#!/bin/bash

read -p "Please type the path of the device the ISO will be burnt to (e.g. /dev/sda) " device
read -p "WARNING! This WILL overwrite whatever data is on the device IRREVERSIBLY! Continue? [y/N]" yn
case $yn in 
	[Yy]* )
		cd ..
		make clean
		make -j$(nproc)
		cd scripts
		./makeiso.sh
		sudo dd if=../taedium.iso of=$device conv=fsync bs=4K status=progress
	;;
	[Nn]* )
		exit 1
	;;
	* )
		exit 1
	;;
esac
