#! bin/sh

version=v0.0.1.0a
phase=alpha

binfile=build/bin/cb_bin.bin
isofile=build/cubebox-$version-$phase.iso

echo "------------------------------------------------"
echo "CubeBox Build script"
echo " -   CubeBox version: $version"
echo " -   Phase:           $phase"
echo " -   ISO Location:    $isofile"
echo "------------------------------------------------"

mkdir -p build/obj/drivers
mkdir -p build/obj/libs
mkdir -p build/obj/kernel/crt
mkdir    build/obj/kernel/gdt

echo STEP 1: Assemble assembly files
i686-elf-as boot.s -o build/obj/boot.s.o
i686-elf-as kernel/crt/crti.s -o build/obj/kernel/crt/crti.s.o
i686-elf-as kernel/crt/crtn.s -o build/obj/kernel/crt/crtn.s.o
nasm -felf32 kernel/gdt/gdt.asm -o build/obj/kernel/gdt/gdt.asm.o

echo STEP 2: Compile sources
i686-elf-gcc -c libs/stringt.c -o build/obj/libs/stringt.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c drivers/vga.c -o build/obj/drivers/vga.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c kernel/tty.c -o build/obj/kernel/tty.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c kernel/kmain.c -o build/obj/kernel/kmain.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c kernel/gdt/gdt.c -o build/obj/kernel/gdt/gdt.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs


echo STEP 3: Link object files
i686-elf-gcc -T linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc \
                build/obj/kernel/crt/crti.s.o \
                build/obj/kernel/crt/crtn.s.o \
                build/obj/kernel/gdt/gdt.asm.o \
                build/obj/libs/stringt.c.o \
                build/obj/boot.s.o \
                build/obj/kernel/kmain.c.o \
                build/obj/kernel/gdt/gdt.c.o \
                build/obj/kernel/tty.c.o \
                build/obj/drivers/vga.c.o

echo STEP 4: Verify multiboot
if grub-file --is-x86-multiboot $binfile; then
    echo MB Confirmed.
    echo STEP 5: Create bootable ISO image

    mkdir -p build/iso/boot/grub
    cp $binfile build/iso/boot/cb_bin.bin
    cp grub.cfg build/iso/boot/grub/grub.cfg

    grub-mkrescue -o $isofile build/iso
else
    echo MB not confirmed.
fi