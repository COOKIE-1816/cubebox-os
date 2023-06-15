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

gcc_flags="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I ./ -I libs"
link_flags="linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc"

mkdir -p build/obj/drivers/keyboard
mkdir -p build/obj/libs
mkdir -p build/obj/kernel/crt
mkdir    build/obj/kernel/gdt
mkdir    build/obj/kernel/interrupt
mkdir    build/obj/kernel/timing

echo STEP 1: Assemble assembly files
i686-elf-as  boot.s                                     -o build/obj/boot.s.o
i686-elf-as  kernel/crt/crti.s                          -o build/obj/kernel/crt/crti.s.o
i686-elf-as  kernel/crt/crtn.s                          -o build/obj/kernel/crt/crtn.s.o
#nasm -felf32  kernel/probe.s                             -o build/obj/kernel/probe.s.o
nasm -felf32 kernel/gdt/gdt.asm                         -o build/obj/kernel/gdt/gdt.asm.o
nasm -felf32 kernel/interrupt/isr.asm                   -o build/obj/kernel/interrupt/isr.asm.o
nasm -felf32 drivers/keyboard/i86_keyboard_irq_asm.asm  -o build/obj/drivers/keyboard/i86_keyboard_irq_asm.asm.o
#[addfile.py: assembly]

echo STEP 2: Compile sources
i686-elf-gcc -c libs/stringt.c                  -o build/obj/libs/stringt.c.o               $gcc_flags
i686-elf-gcc -c drivers/vga.c                   -o build/obj/drivers/vga.c.o                $gcc_flags
i686-elf-gcc -c kernel/tty.c                    -o build/obj/kernel/tty.c.o                 $gcc_flags
i686-elf-gcc -c kernel/kmain.c                  -o build/obj/kernel/kmain.c.o               $gcc_flags
i686-elf-gcc -c kernel/gdt/gdt.c                -o build/obj/kernel/gdt/gdt.c.o             $gcc_flags
i686-elf-gcc -c kernel/interrupt/isr.c          -o build/obj/kernel/interrupt/isr.c.o       $gcc_flags
i686-elf-gcc -c kernel/interrupt/idt.c          -o build/obj/kernel/interrupt/idt.c.o       $gcc_flags
i686-elf-gcc -c kernel/common.c                 -o build/obj/kernel/common.c.o              $gcc_flags
i686-elf-gcc -c drivers/keyboard.c              -o build/obj/drivers/keyboard.c.o           $gcc_flags
i686-elf-gcc -c drivers/keyboard/leds.c         -o build/obj/drivers/keyboard/leds.c.o      $gcc_flags
i686-elf-gcc -c kernel/timing/rtc.c             -o build/obj/kernel/timing/rtc.c.o          $gcc_flags
i686-elf-gcc -c kernel/kdrivers.c               -o build/obj/kernel/kdrivers.c.o            $gcc_flags
i686-elf-gcc -c drivers/buzzer.c                -o build/obj/drivers/buzzer.c.o             $gcc_flags
i686-elf-gcc -c kernel/sound/beep.c             -o build/obj/kernel/sound/beep.c.o          $gcc_flags
#[addfile.py: c]


echo STEP 3: Link object files
i686-elf-gcc -T $link_flags \
                build/obj/kernel/crt/crti.s.o \
                build/obj/kernel/crt/crtn.s.o \
                build/obj/kernel/gdt/gdt.asm.o \
                build/obj/kernel/common.c.o \
                build/obj/libs/stringt.c.o \
                build/obj/boot.s.o \
                build/obj/kernel/kdrivers.c.o \
                build/obj/kernel/kmain.c.o \
                build/obj/kernel/gdt/gdt.c.o \
                build/obj/kernel/tty.c.o \
                build/obj/drivers/vga.c.o \
                build/obj/kernel/interrupt/isr.asm.o \
                build/obj/kernel/interrupt/isr.c.o \
                build/obj/kernel/interrupt/idt.c.o \
                build/obj/drivers/keyboard.c.o \
                build/obj/drivers/keyboard/leds.c.o \
                build/obj/drivers/keyboard/i86_keyboard_irq_asm.asm.o \
                build/obj/kernel/timing/rtc.c.o \
                build/obj/drivers/buzzer.c.o \
                build/obj/kernel/sound/beep.c.o
                #[addfile.py: obj]

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