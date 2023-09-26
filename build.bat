@echo off >NUL

rem wsl sh ./build.sh

mkdir tmp
mkdir build
mkdir build\obj
mkdir build\bin

del /F /Q build\obj\*
del /F /Q build\bin\*

wsl  find -type f -name '*.s'	^| paste -sd " "    > 	tmp/sources_asm
wsl  find -type f -name '*.c'   ^| paste -sd " " > 	tmp/sources_c
wsl  find -type f -name '*.cpp' ^| paste -sd " "> 	tmp/sources_cpp

set /p SOURCES_ASM=<tmp/sources_asm
set /p SOURCES_C=<tmp\sources_c
set /p SOURCES_CPP=<tmp\sources_cpp

set  LD_SCRIPTS="src/linker.ld"

set  FLAGS=-ffreestanding -O2 -fno-exceptions -Wall -Wextra -Isrc -Isrc/libs/libc
set  CFLAGS=-std=gnu99
set  CPFLAGS=-fno-rtti
set  LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

echo ===== [  LANG: C  ] =====
i686-elf-gcc %FLAGS% %CFLAGS% -c %SOURCES_C%

rem echo ===== [ LANG: C++ ] =====
rem i686-elf-g++ %FLAGS% %CPFLAGS% -c %SOURCES_CPP%

echo ===== [ ASSEMBLY  ] =====
rem : For some reason, the code bellow not working.
rem   Looks like assembler needs output file to be specified.
rem i686-elf-as %SOURECS_ASM% 

i686-elf-as src/kernel/entry.s -o entry.o



echo ==========================
echo Linking everything together...

wsl  find -type f -name '*.o'  >tmp/out
set /p OUTF=<tmp\out

i686-elf-gcc -T %LD_SCRIPTS% %LDFLAGS% -o build/bin/kernel.bin %OUTF%

move *.o build\obj

wsl ./scripts/bootloader.sh

del /F /S /Q tmp\*