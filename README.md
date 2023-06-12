# CubeBox OS
Free, open-source experimental operating system.

## Why am i doing it?
Well, there is no such a good reason i am doing this, but it is probably **just for fun and for education**. Anyways, if you find this project good, i will be glad for everyone using it.

## What are this project goals?
* The main goal of this project is to create an operating system **compatible with both modern and old (*crappy*) computers.**  
    To statisfy this goal, it is required to **implement hardware drivers for both modern and old hardware devices**. This includes (for example) floppy disk controller, old displays, SSDs, USB 3.0., NVMe disks, etc.  
* It is also needed to create a system that is **as lightweight as possible**. Operating system can not be too hungry for resources, as old computers does not have as many resources, as modern computers have.
* Another goal is to create an **environment simliar to linux**, but not re-create it too much.
* Also, goal of this project is to create it a bit **nostalgic** but also usable at once.

## Why should i use it?
Althrough project is not complete, i believe in that, one day you will find it usefull. As i said, the main goal of this project is to make an operating system that runs (and fits) on every machine - both modern and old "*crappy*" computers.  

Also, if you are going to use it for educational purposes, the doors are always open for you :).

## Build dependency list
These are dependencies required to build:

* **GNU Cross Compiler and GNU assebler for i686** - required to build the most of the parts of the code. Probably a part of `binutils`. The specific binaries name are `i686-elf-gcc i686-elf-as`.
* **Netwide assembler AKA NASM** - required to assemble system parts that were not able to be built using `i686-elf-as`.
* **Grand Unified Bootloader AKA GNU GRUB** - required to make an ISO file containing the GNU GRUB bootloader. The required binaries are `grub-file` and `grub-mkrescue`.
* **xorriso and mtools** - packages required with GNU GRUB to make bootable ISO image.

This is how I installed everything on my computer running Debian-based distribution (Ubuntu):
```sh
$ sudo apt-get upadate
$ sudo apt install nasm grub-common xorriso mtools build-essential git bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
$ export PREFIX="$HOME/opt/cross"
$ export TARGET=i686-elf
$ export PATH="$PREFIX/bin:$PATH"
$ mkdir $HOME/opt/cross/bin
$ mkdir $HOME/src
$ cd $HOME/src
$ git clone --depth 1 https://github.com/bminor/binutils-gdb.git ~/src/binutils-gdb
$ mkdir ~/src/binutils-gdb/build-binutils
$ cd ~/src/binutils-gdb/build-binutils
$ ../configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
$ make
$ make install
$ which -- $TARGET-as || echo $TARGET-as is not in the PATH
$ git clone --depth 1 https://github.com/gcc-mirror/gcc.git ~/src/gcc
$ mkdir ~/src/gcc/build-gcc
$ cd ~/src/gcc/build-gcc
$ ../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
$ make all-gcc
$ make all-target-libgcc
$ make install-gcc
$ make install-target-libgcc
$ which -- $TARGET-gcc || echo $TARGET-gcc is not in the PATH
```

If you are not running on Linux, you are probably going to go through the hell, especially for Windows users. Wish you good luck.

> **NOTE**: Installation may take a large amount of time, even a coupule of hours, depending on your machine and internet connection. Please, be patient.

## Build from sources
After installing build dependencies, you are finally ready to build sources.  
First, you need to get source code. You can do this using `git` by cloning a Git repository. *Alternatively, if something goes wrong, you can download whole branch as a ZIP archive*
```sh
$ git clone https://github.com/COOKIE-1816/cubebox-os.git
$ cd ./cubebox-os
```

After having Git repo clonned, run `./build.sh` script. Now, just sit and wait.

```
vhajsman@main:~/Desktop/cubebox$ sh ./build.sh 
------------------------------------------------
CubeBox Build script
 -   CubeBox version: v0.0.1.0a
 -   Phase:           alpha
 -   ISO Location:    build/cubebox-v0.0.1.0a-alpha.iso
------------------------------------------------
STEP 1: Assemble assembly files
STEP 2: Compile sources
STEP 3: Link object files
STEP 4: Verify multiboot
MB Confirmed.
STEP 5: Create bootable ISO image
xorriso 1.5.4 : RockRidge filesystem manipulator, libburnia project.

Drive current: -outdev 'stdio:build/cubebox-v0.0.1.0a-alpha.iso'
Media current: stdio file, overwriteable
Media status : is blank
Media summary: 0 sessions, 0 data blocks, 0 data,  178g free
Added to ISO image: directory '/'='/tmp/grub.wh9806'
xorriso : UPDATE :     579 files added in 1 seconds
Added to ISO image: directory '/'='/home/vhajsman/Desktop/cubebox/build/iso'
xorriso : UPDATE :     584 files added in 1 seconds
xorriso : NOTE : Copying to System Area: 512 bytes from file '/usr/lib/grub/i386-pc/boot_hybrid.img'
xorriso : UPDATE : Thank you for being patient. Working since 0 seconds.
ISO image produced: 5739 sectors
Written to medium : 5739 sectors at LBA 0
Writing to 'stdio:build/cubebox-v0.0.1.0a-alpha.iso' completed successfully.

```

## Where does the object files, binaries and ISO file go after build?
```
ISO File(s)   ->  ./build/              (*.iso)
ISO Contents  ->  ./build/iso           
Binary files  ->  ./build/bin           (*.bin)
Object files  ->  ./build/obj           (*.<source-extension>.o)
```
