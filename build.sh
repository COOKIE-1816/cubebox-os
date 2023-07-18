#! /bin/sh

version=v0.0.1.0a
phase=alpha

binfile=build/bin/cb_bin.bin
isofile=build/cubebox-$version-$phase.iso

cat ./cb_ascii.txt

sleep 2

echo ""
echo "------------------------------------------------"
echo "CubeBox Build script"
echo " -   CubeBox version: $version"
echo " -   Phase:           $phase"
echo " -   ISO Location:    $isofile"
echo "------------------------------------------------"

gcc_flags="-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -m32 -I ./include/ -I ./include/libs/ -I ./include/libs/libc/ -I ./include/libs/libk/"
link_flags="src/linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc"

rm -f $(find build/obj -name "*.o")

# Function Declerations

comple_sources_fn (){
    i686-elf-c++ $1 -c src/libs/libc/stringt.cpp                  -o build/obj/libs/libc/stringt.cpp.o               $gcc_flags
    i686-elf-c++ $1 -c src/drivers/vga.cpp                   -o build/obj/drivers/vga.cpp.o                $gcc_flags
    i686-elf-c++ $1 -c src/kernel/tty.cpp                    -o build/obj/kernel/tty.cpp.o                 $gcc_flags
    i686-elf-c++ $1 -c src/kernel/kmain.cpp                -o build/obj/kernel/kmain.cpp.o               $gcc_flags
    i686-elf-c++ $1 -c src/kernel/gdt/gdt.cpp                -o build/obj/kernel/gdt/gdt.cpp.o             $gcc_flags
    i686-elf-c++ $1 -c src/kernel/interrupt/isr.cpp          -o build/obj/kernel/interrupt/isr.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/kernel/interrupt/idt.cpp          -o build/obj/kernel/interrupt/idt.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/kernel/common.cpp                 -o build/obj/kernel/common.cpp.o              $gcc_flags
    i686-elf-c++ $1 -c src/drivers/keyboard.cpp              -o build/obj/drivers/keyboard.cpp.o           $gcc_flags
    i686-elf-c++ $1 -c src/drivers/rtc.cpp                   -o build/obj/drivers/rtc.cpp.o                $gcc_flags
    i686-elf-c++ $1 -c src/kernel/kdrivers.cpp               -o build/obj/kernel/kdrivers.cpp.o            $gcc_flags
    i686-elf-c++ $1 -c src/drivers/buzzer.cpp                -o build/obj/drivers/buzzer.cpp.o             $gcc_flags
    #i686-elf-c++ $1 -c kernel/sound/beep.c             -o build/obj/kernel/sound/beep.c.o          $gcc_flags
    i686-elf-c++ $1 -c src/drivers/pit.cpp                 -o build/obj/drivers/pit.cpp.o              $gcc_flags
    i686-elf-c++ $1 -c src/drivers/pic.cpp                   -o build/obj/drivers/pic.cpp.o                $gcc_flags
    #i686-elf-c++ $1 -c drivers/floppy.c                -o build/obj/drivers/floppy.c.o             $gcc_flags
    i686-elf-c++ $1 -c src/kernel/interrupt/irq.cpp          -o build/obj/kernel/interrupt/irq.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/drivers/pci.cpp                   -o build/obj/drivers/pci.cpp.o                $gcc_flags
    #i686-elf-c++ $1 -c src/drivers/ide.c                   -o build/obj/drivers/ide.c.o                $gcc_flags
    i686-elf-c++ $1 -c src/drivers/acpi.cpp                  -o build/obj/drivers/acpi.cpp.o               $gcc_flags
    i686-elf-c++ $1 -c src/drivers/acpi/shutdown.cpp         -o build/obj/drivers/acpi/shutdown.cpp.o      $gcc_flags
    i686-elf-c++ $1 -c src/kernel/system.cpp                 -o build/obj/kernel/system.cpp.o              $gcc_flags
    i686-elf-c++ $1 -c src/kernel/memory/free.cpp            -o build/obj/kernel/memory/free.cpp.o         $gcc_flags
    i686-elf-c++ $1 -c src/kernel/memory/malloc.cpp          -o build/obj/kernel/memory/malloc.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/kernel/cursor.cpp                 -o build/obj/kernel/cursor.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/kernel/panic.cpp                 -o build/obj/kernel/panic.cpp.o       $gcc_flags
    i686-elf-c++ $1 -c src/kernel/error.cpp                 -o build/obj/kernel/error.cpp.o       $gcc_flags
    #i686-elf-c++ $1 -c src/text_ui/shapes.cpp                -o build/obj/text_ui/shapes.cpp.o             $gcc_flags
}

link_obj_fn(){
    i686-elf-c++ $1 -T $link_flags $(find build/obj -name "*.o")

} 

mkdir -p build/obj/drivers/keyboard         2> /dev/null
mkdir    build/obj/drivers/acpi             2> /dev/null
mkdir -p build/obj/libs/libc                2> /dev/null
mkdir -p build/obj/libs/libk                2> /dev/null
mkdir -p build/obj/kernel/crt               2> /dev/null
mkdir    build/obj/kernel/gdt               2> /dev/null
mkdir    build/obj/kernel/interrupt         2> /dev/null
mkdir    build/obj/kernel/timing            2> /dev/null
mkdir    build/obj/kernel/sound             2> /dev/null
mkdir    build/obj/kernel/memory            2> /dev/null
mkdir    build/obj/text_ui                  2> /dev/null
mkdir    build/iso/resources                2> /dev/null

convert ./logo.png ./resources/default/logo.tga

echo STEP 1: Assemble assembly files
i686-elf-as  src/boot.s                                     -o build/obj/boot.s.o
i686-elf-as  src/kernel/crt/crti.s                          -o build/obj/kernel/crt/crti.s.o
i686-elf-as  src/kernel/crt/crtn.s                          -o build/obj/kernel/crt/crtn.s.o
#nasm -felf32 src/kernel/gdt/asm.s                           -o build/obj/kernel/gdt/asm.s.o
#nasm -felf32  kernel/probe.s                             -o build/obj/kernel/probe.s.o
#nasm -felf32 src/kernel/gdt/asm.s                         -o build/obj/kernel/gdt/asm.s.o
#nasm -felf32 src/kernel/interrupt/isr.asm                   -o build/obj/kernel/interrupt/isr.asm.o
#[addfile.py: assembly]
if [ "$1" != "no-war" ]; 
then
    echo STEP 2: Compile sources
    comple_sources_fn "";
    #[addfile.py: c]

    echo STEP 3: Link object files
    link_obj_fn "";
else
    echo STEP 2: Compile sources
    comple_sources_fn "-w";
    #[addfile.py: c]

    echo STEP 3: Link object files
    link_obj_fn "-w";

fi

echo STEP 4: Verify multiboot
if grub-file --is-x86-multiboot $binfile; then
    echo "-> Multiboot confirmed. Continuing to build an ISO file with GRUB."

    sh ./build_vgatest.sh

    echo STEP 9: Create bootable ISO image

    mkdir -p build/iso/boot/grub
    cp $binfile build/iso/boot/cb_bin.bin 
    cp build/bin/cb_bin-vgatest.bin build/iso/boot/cb_bin-vgatest.bin
    cp src/grub.cfg build/iso/boot/grub/grub.cfg

    cp splash-*x*.png build/iso/boot/splash.png

    cp -r resources/* build/iso/resources/

    grub-mkrescue -o $isofile build/iso
else
    echo "-> Multiboot not confirmed. ISO file will not build."
fi

echo ""

echo "+-------------------------------------------+"
echo "| Thank you for patiently building CubeBox! |"
echo "|        We really appreciate that!         |"
echo "|                                           |"
echo "|    Hope you are going to enjoy using      |"
echo "| CubeBox. If there is a problem, or there  |"
echo "| was an error while building,  please let  |"
echo "|                us know.                   |"
echo "+-------------------------------------------+"

echo ""
echo "Copyright (C) Vaclav Hajsman (AKA COOKIE) 2023."