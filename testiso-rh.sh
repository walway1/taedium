#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

read -p "This will overwrite whatever data is on /dev/sda. Continue? [Y/N]" yn
case $yn in 
	[Yy]* )
		make && ./makeiso.sh && dd if=taedium.iso of=/dev/sda conv=fsync bs=4K status=progress
	;;
	[Nn]* )
		exit 1
	;;
esac
