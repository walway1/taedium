read -p "This will overwrite whatever data is on /dev/sda. Continue? [Y/N]" yn
case $yn in 
	[Yy]* )
		make clean && make -j$(nproc) && ./makeiso.sh && sudo dd if=taedium.iso of=/dev/sda conv=fsync bs=4K status=progress
	;;
	[Nn]* )
		exit 1
	;;
esac
