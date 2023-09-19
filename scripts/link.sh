echo "-> Linking object files together..."
i686-elf-g++ -T src/linker.ld -o build/bin/cubebox.bin -ffreestanding -O2 -nostdlib build/obj/* -lgcc

OBJFILES=$(find -type f -name "*.out")
cp $OBJFILES "build/obj"
rm -f $OBJFILES