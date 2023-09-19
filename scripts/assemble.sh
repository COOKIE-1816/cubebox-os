echo "-> Assembling assembly language sources..."

SOURCES_ASM=$(find -type f -name "*.s")

i686-elf-as $SOURCES_ASM 