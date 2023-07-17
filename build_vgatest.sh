version=v0.0.1.0a
phase=alpha

binfile=build/bin/cb_bin-vgatest.bin
#isofile=build/cubebox-$version-$phase.iso

gcc_flags="-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -m32 -I ./include/ -I ./include/libs/libc -I ./include/libs/libk -D __E_VGATEST"
link_flags="src/linker.ld -o $binfile -ffreestanding -O2 -nostdlib -lgcc"

#rm -f $(find build/obj -name "*.o")

comple_sources_fn (){
    #i686-elf-c++ $1 -c src/libs/stringt.cpp                  -o build/obj/libs/stringt.cpp.o               $gcc_flags
    #i686-elf-c++ $1 -c src/drivers/vga.cpp                   -o build/obj/drivers/vga.cpp.o                $gcc_flags
    #i686-elf-c++ $1 -c src/kernel/tty.cpp                    -o build/obj/kernel/tty.cpp.o                 $gcc_flags
    i686-elf-c++ $1 -c src/kernel/kmain.cpp                -o build/obj/kernel/kmain.cpp.o               $gcc_flags
}

link_obj_fn(){
    i686-elf-c++ $1 -T $link_flags \
        build/obj/libs/libc/stringt.cpp.o \
        build/obj/drivers/vga.cpp.o \
        build/obj/kernel/tty.cpp.o \
        build/obj/kernel/kmain.cpp.o \
        build/obj/kernel/cursor.cpp.o \
        build/obj/kernel/common.cpp.o \
        build/obj/boot.s.o
}

echo STEP 5: Assemble assembly files
i686-elf-as  src/boot.s                                     -o build/obj/boot.s.o
i686-elf-as  src/kernel/crt/crti.s                          -o build/obj/kernel/crt/crti.s.o
i686-elf-as  src/kernel/crt/crtn.s                          -o build/obj/kernel/crt/crtn.s.o

if [ "$1" != "no-war" ]; 
then
    echo STEP 6: Compile sources
    comple_sources_fn "";
    #[addfile.py: c]

    echo STEP 7: Link object files
    link_obj_fn "";
else
    echo STEP 6: Compile sources
    comple_sources_fn "-w";
    #[addfile.py: c]

    echo STEP 7: Link object files
    link_obj_fn "-w";

fi

echo STEP 8: Verify multiboot
if grub-file --is-x86-multiboot $binfile; then
    echo "-> Multiboot confirmed. Continuing to build an ISO file with GRUB."
else
    echo "-> Multiboot not confirmed. ISO file will not build."
fi