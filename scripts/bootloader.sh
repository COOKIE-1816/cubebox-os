echo "-> Checking binaries for valid multiboot headers..." 
if grub-file --is-x86-multiboot build/bin/cubebox.bin; then 
	echo "-> Generating bootable ISO with GRUB bootloader..." 
	mkdir -p build/isodir/boot/grub 
	cp cubebox.bin build/isodir/boot/cubebox.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/iso/cubebox.iso build/isodir 
else
	echo "ERR: Multiboot could not be confirmed." 
fi 