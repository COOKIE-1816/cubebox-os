echo "-> Checking binaries for valid multiboot headers..."

# grub-file --is-x86-multiboot myos.bin
if grub-file --is-x86-multiboot myos.bin; then
	echo "-> Generating bootable ISO with GRUB bootloader..."
	
	mkdir -p build/isodir/boot/grub
	cp myos.bin build/isodir/boot/myos.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	
	grub-mkrescue -o build/iso/cubebox.iso build/isodir
else
	echo "ERR: Multiboot could not be confirmed."
fi