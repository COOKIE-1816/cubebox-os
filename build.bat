@echo off >NUL

rem wsl sh ./build.sh

mkdir tmp
mkdir build
mkdir build\obj
mkdir build\bin

del /F /Q build\obj\*
del /F /Q build\bin\*

wsl  find -type f -name '*.s'    > 	tmp/sources_asm
wsl  find -type f -name '*.c'    > 	tmp/sources_c
wsl  find -type f -name '*.cpp'  > 	tmp/sources_cpp

set  SOURCES_ASM=<tmp/sources_asm
set  SOURCES_C=<tmp\sources_c
set  SOURCES_CPP=<tmp\sources_cpp

set  LD_SCRIPTS="src/linker.ld"

set  FLAGS="-ffreestanding -O2 -fno-exceptions -Wall -Wextra"
set  CFLAGS="-std=gnu99"
set  CPFLAGS="-fno-rtti"
set  LDFLAGS="-ffreestanding -O2 -nostdlib -lgcc"
set  ASFLAGS=""

echo ===== [  LANG: C  ] =====
echo %SOURCES_C%
i686-elf-gcc %FLAGS% %CFLAGS% %SOURCES_C%

echo ===== [ LANG: C++ ] =====
echo %SOURCES_CPP%
i686-elf-g++ %FLAGS% %CPFLAGS% %SOURCES_CPP%

echo ===== [ ASSEMBLY  ] =====
echo %SOURCES_ASM%
i686-elf-as %SOURECS_ASM% %AFLAGS%

echo ==========================
echo Linking everything together...
i686-elf-g++ -T %LD_SCRIPTS% %LDFLAGS% build/obj/* -o build/bin/kernel.bin

wsl ./scripts/bootloader.sh

del /F /S tmp