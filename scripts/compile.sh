echo "-> Compiling source code..."

CFLAGS=" -ffreestanding -O2 -Wall -Wextra -fno-exceptions -I ./src/"

SOURCES_CPP=$(find -type f -name "*.cpp")
SOURCES_C=$(find -type f -name "*.c")

echo "   C   | $SOURCES_C"
i686-elf-gcc $CFLAGS $SOURCES_C  -std=gnu99

echo "   C++ | $SOURCES_C"
i686-elf-g++ $CFLAGS $SOURCES_CPP -fno-rtti