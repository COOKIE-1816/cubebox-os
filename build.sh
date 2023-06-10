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

echo STEP 1: Assemble boot sector
i686-elf-as boot.s -o build/obj/boot.s.o

echo STEP 2: Compile sources
i686-elf-gcc -c libs/stringt.c -o build/obj/libs/stringt.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c drivers/vga.c -o build/obj/drivers/vga.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c kernel/tty.c -o build/obj/kernel/tty.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs
i686-elf-gcc -c kernel/kmain.c -o build/obj/kernel/kmain.c.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs


echo STEP 3: Link object files
i686-elf-gcc -T linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc \
                build/obj/libs/stringt.c.o \
                build/obj/boot.s.o \
                build/obj/kernel/kmain.c.o \
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