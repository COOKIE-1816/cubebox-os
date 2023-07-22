SOURCES_CPP=$(find -type f -name "*.cpp")
SOURCES_C=$(find -type f -name "*.c")
SOURCES_ASM=$(find -type f -name "*.s")

CFLAGS=" -ffreestanding -O2 -Wall -Wextra -fno-exceptions -I ./src/"

i686-elf-as $SOURCES_ASM 
i686-elf-gcc $CFLAGS $SOURCES_C  -std=gnu99
i686-elf-g++ $CFLAGS $SOURCES_CPP -fno-rtti

OBJFILES=$(find -type f -name "*.out")
cp $OBJFILES "build/obj"
rm -f $OBJFILES

i686-elf-g++ -T src/linker.ld -o build/bin/cubebox.bin -ffreestanding -O2 -nostdlib build/obj/* -lgcc