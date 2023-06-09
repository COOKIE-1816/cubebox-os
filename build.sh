  src_c=$(find ./src -name *.c)
#src_asm=$(find ./src -name *.asm)

#nasm -felf32 $src_asm
nasm -felf64 src/boot.asm -o build/obj/boot.asm.o
gcc -c $src_c -ffreestanding -O2 -Wall -Wextra -std=gnu99 -I inc

mv *.o build/obj

ld -T src/linker.ld -o cubebox.bin -O2 -nostdlib build/obj/boot.asm.o build/obj/kmain.o -z noexecstack