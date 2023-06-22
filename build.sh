#! /bin/sh

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

gcc_flags="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs"
link_flags="linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc"

# Function Declerations

comple_sources_fn (){
    i686-elf-gcc $1 -c libs/stringt.c                  -o build/obj/libs/stringt.c.o               $gcc_flags
    i686-elf-gcc $1 -c drivers/vga.c                   -o build/obj/drivers/vga.c.o                $gcc_flags
    i686-elf-gcc $1 -c kernel/tty.c                    -o build/obj/kernel/tty.c.o                 $gcc_flags
    i686-elf-gcc $1 -c kernel/kmain.c                  -o build/obj/kernel/kmain.c.o               $gcc_flags
    i686-elf-gcc $1 -c kernel/gdt/gdt.c                -o build/obj/kernel/gdt/gdt.c.o             $gcc_flags
    i686-elf-gcc $1 -c kernel/interrupt/isr.c          -o build/obj/kernel/interrupt/isr.c.o       $gcc_flags
    i686-elf-gcc $1 -c kernel/interrupt/idt.c          -o build/obj/kernel/interrupt/idt.c.o       $gcc_flags
    i686-elf-gcc $1 -c kernel/common.c                 -o build/obj/kernel/common.c.o              $gcc_flags
    i686-elf-gcc $1 -c drivers/keyboard.c              -o build/obj/drivers/keyboard.c.o           $gcc_flags
    i686-elf-gcc $1 -c drivers/rtc.c                   -o build/obj/drivers/rtc.c.o                $gcc_flags
    i686-elf-gcc $1 -c kernel/kdrivers.c               -o build/obj/kernel/kdrivers.c.o            $gcc_flags
    i686-elf-gcc $1 -c drivers/buzzer.c                -o build/obj/drivers/buzzer.c.o             $gcc_flags
    #i686-elf-gcc $1 -c kernel/sound/beep.c             -o build/obj/kernel/sound/beep.c.o          $gcc_flags
    i686-elf-gcc $1 -c drivers/timer.c                 -o build/obj/drivers/timer.c.o              $gcc_flags
    i686-elf-gcc $1 -c drivers/pic.c                   -o build/obj/drivers/pic.c.o                $gcc_flags
    #i686-elf-gcc $1 -c drivers/floppy.c                -o build/obj/drivers/floppy.c.o             $gcc_flags
    i686-elf-gcc $1 -c kernel/interrupt/irq.c          -o build/obj/kernel/interrupt/irq.c.o       $gcc_flags
    i686-elf-gcc $1 -c drivers/pci.c                   -o build/obj/drivers/pci.c.o                $gcc_flags
    i686-elf-gcc $1 -c drivers/ide.c                   -o build/obj/drivers/ide.c.o                $gcc_flags
    i686-elf-gcc $1 -c drivers/acpi.c                  -o build/obj/drivers/acpi.c.o               $gcc_flags
    i686-elf-gcc $1 -c drivers/acpi/shutdown.c         -o build/obj/drivers/acpi/shutdown.c.o      $gcc_flags
    i686-elf-gcc $1 -c kernel/system.c                 -o build/obj/kernel/system.c.o              $gcc_flags
    i686-elf-gcc $1 -c kernel/memory/free.c            -o build/obj/kernel/memory/free.c.o         $gcc_flags
    i686-elf-gcc $1 -c kernel/memory/malloc.c          -o build/obj/kernel/memory/malloc.c.o       $gcc_flags
}

link_obj_fn(){
    i686-elf-gcc $1 -T $link_flags \
                build/obj/kernel/kdrivers.c.o \
                build/obj/kernel/kmain.c.o \
                build/obj/kernel/crt/crti.s.o \
                build/obj/kernel/crt/crtn.s.o \
                build/obj/kernel/gdt/gdt.asm.o \
                build/obj/kernel/common.c.o \
                build/obj/libs/stringt.c.o \
                build/obj/boot.s.o \
                build/obj/kernel/gdt/gdt.c.o \
                build/obj/kernel/tty.c.o \
                build/obj/drivers/vga.c.o \
                build/obj/kernel/interrupt/isr.asm.o \
                build/obj/kernel/interrupt/isr.c.o \
                build/obj/kernel/interrupt/idt.c.o \
                build/obj/drivers/keyboard.c.o \
                build/obj/drivers/rtc.c.o \
                build/obj/drivers/buzzer.c.o \
                build/obj/drivers/timer.c.o \
                build/obj/drivers/pic.c.o \
                build/obj/kernel/interrupt/irq.c.o \
                build/obj/drivers/pci.c.o \
                build/obj/drivers/ide.c.o  \
                build/obj/drivers/acpi.c.o \
                build/obj/drivers/acpi/shutdown.c.o \
                build/obj/kernel/system.c.o \
                build/obj/kernel/memory/free.c.o \
                build/obj/kernel/memory/malloc.c.o
                #build/obj/drivers/floppy.c.o
                #[addfile.py: obj]

} 

mkdir -p build/obj/drivers/keyboard
mkdir    build/obj/drivers/acpi
mkdir -p build/obj/libs
mkdir -p build/obj/kernel/crt
mkdir    build/obj/kernel/gdt
mkdir    build/obj/kernel/interrupt
mkdir    build/obj/kernel/timing
mkdir    build/obj/kernel/sound
mkdir    build/obj/kernel/memory

echo STEP 1: Assemble assembly files
i686-elf-as  boot.s                                     -o build/obj/boot.s.o
i686-elf-as  kernel/crt/crti.s                          -o build/obj/kernel/crt/crti.s.o
i686-elf-as  kernel/crt/crtn.s                          -o build/obj/kernel/crt/crtn.s.o
#nasm -felf32  kernel/probe.s                             -o build/obj/kernel/probe.s.o
nasm -felf32 kernel/gdt/gdt.asm                         -o build/obj/kernel/gdt/gdt.asm.o
nasm -felf32 kernel/interrupt/isr.asm                   -o build/obj/kernel/interrupt/isr.asm.o
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
    echo MB Confirmed.
    echo STEP 5: Create bootable ISO image

    mkdir -p build/iso/boot/grub
    cp $binfile build/iso/boot/cb_bin.bin
    cp grub.cfg build/iso/boot/grub/grub.cfg

    cp splash-*x*.png build/iso/boot/splash.png

    grub-mkrescue -o $isofile build/iso
else
    echo MB not confirmed.
fi
