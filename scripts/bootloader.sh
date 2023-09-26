echo "-> Checking binaries for valid multiboot headers..." 
if grub-file --is-x86-multiboot build/bin/kernel.bin; then 
	echo "-> Generating bootable ISO with GRUB bootloader..." 
	mkdir -p build/isodir/boot/grub 
	cp kernel.bin build/isodir/boot/kernel.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/iso/kernel.iso build/isodir 
else
	echo "ERR: Multiboot could not be confirmed." 
fi 