mkdir -p build/bin  
mkdir -p build/obj  
rm -f build/obj/* 
rm -f build/bin/* 
SOURCES_ASM=$(find -type f -name "*.s")
SOURCES_CPP=$(find -type f -name "*.cpp")
SOURCES_C=$(find -type f -name "*.c")
SOURCES_H=$(find -type f -name "*.h")
WORKDIR=$PWD
CFLAGS=" -ffreestanding -O2 -Wall -fno-exceptions -Wextra "
SEARCH=" -Isrc -Isrc/libs/libc "
echo "-> Assembling assembly language sources..." 
i686-elf-as $SOURCES_ASM
echo "-> Compiling source code..." 
echo "   C   | $SOURCES_C" 
i686-elf-gcc $CFLAGS  -c -lc $SOURCES_C $SEARCH -std=gnu99  
echo "   C++ | $SOURCES_C" 
i686-elf-g++ $CFLAGS -c  -lc $SOURCES_CPP $SEARCH -fno-rtti   
echo "-> Linking object files together..." 
i686-elf-g++ -T src/linker.ld -o build/bin/cubebox.bin -ffreestanding -O2 -nostdlib build/obj/* -lgcc  
OBJFILES=$(find -type f -name "*.o")
mv $OBJFILES build/obj 
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