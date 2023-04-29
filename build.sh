nasm -felf32 boot.s -o built/boot.s.o
i686-elf-gcc -T linker.ld -o built/iso/boot/krnl.bin -ffreestanding -O2 -nostdlib \
	built/boot.s.o \
	built/kernel/kernel.cpp.o \
	-lgcc

if grub-file --is-x86-multiboot built/iso/boot/krnl.bin; then
	echo multiboot confirmed
else
	echo warning: multiboot NOT confirmed
fi

grub-mkrescue -o built/img.iso built/iso