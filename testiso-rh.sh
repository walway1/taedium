read -p "WARNING! This WILL overwrite whatever data is on /dev/sda IRREVERSIBLY! Continue? [y/N]" yn
case $yn in 
	[Yy]* )
		make clean && make -j$(nproc) && ./makeiso.sh && sudo dd if=taedium.iso of=/dev/sda conv=fsync bs=4K status=progress
	;;
	[Nn]* )
		exit 1
	;;
	* )
		exit 1
	;;
esac
