#building #iso #binaries

# Build dependencies
To successfully build an ISO image from sources, You will need to install some build dependencies on your Linux machine. These are:
*  **GNU Cross Compiler and GNU assebler for i686** - required to build the most of the parts of the code. Probably a part of `binutils`. The specific binaries name are `i686-elf-gcc i686-elf-as`
* **Grand Unified Bootloader AKA GNU GRUB** - required to make an ISO file containing the GNU GRUB bootloader. The required binaries are `grub-file` and `grub-mkrescue`.
*  **xorriso and mtools** - packages required with GNU GRUB to make bootable ISO image.
* **ImageMagick** - for image files conversion.
To install them on Debian-based system, simply run this script:
```sh
sudo apt-get update 
sudo apt install nasm grub-common xorriso mtools build-essential git bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev && export PREFIX="$HOME/opt/cross" && export TARGET=i686-elf && export PATH="$PREFIX/bin:$PATH" && mkdir $HOME/opt/cross/bin && mkdir $HOME/src && cd $HOME/src && git clone --depth 1 https://github.com/bminor/binutils-gdb.git ~/src/binutils-gdb && mkdir ~/src/binutils-gdb/build-binutils && cd ~/src/binutils-gdb/build-binutils && ../configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && make && make install
which -- $TARGET-as || echo $TARGET-as is not in the PATH
git clone --depth 1 https://github.com/gcc-mirror/gcc.git ~/src/gcc && mkdir ~/src/gcc/build-gcc && cd ~/src/gcc/build-gcc && ../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc
which -- $TARGET-gcc || echo $TARGET-gcc is not in the PATH
```

Please note that, the installation may took larger amount of time, usually multiple hours. It also depends on your network connection and your machines hardware.
# Building from sources
After installing build dependencies, you are finally ready to build sources.  
First, you need to get source code. You can do this using `git` by cloning a Git repository. 
```sh
$ git clone https://github.com/COOKIE-1816/cubebox-os.git
$ cd ./cubebox-os
```

_Alternatively, if something goes wrong, you can download whole branch as a ZIP archive._

After having Git repo clonned, run `./build.sh` script. Now, just sit and wait.