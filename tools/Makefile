GCC_VERSION=10.3.0
BINUTILS_VERSION=2.36.1

TARGET=i686-elf
PREFIX="/d/msys64/opt/cross/i686-elf/"

WGET_FLAGS=-q
TAR_FLAGS=-xf

.PHONY: get_gcc get_binutils src-binutils src-gcc always clean delete_src

build: cmd_utils clean_binaries get_gcc

cmd_utils:
	pacman --noconfirm --needed -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb make bison flex gmp-devel mpc-devel mpfr-devel texinfo diffutils python libtool patch base-devel unzip mingw-w64-x86_64-toolchain mingw-w64-x86_64-libtool mingw-w64-x86_64-cmake mingw-w64-x86_64-hdf5

get_gcc: src-gcc get_binutils 
	cd gcc-build; ../gcc-$(GCC_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --host=x86_64-w64-mingw32 --disable-nls --enable-languages=c,c++ --without-headers
	cd gcc-build; make -j4 all-gcc
	cd gcc-build; make all-target-libgcc
	cd gcc-build; make install-gcc install-target-libgcc
	rm -rf gcc-build gcc-$(GCC_VERSION)
	rm -rf gcc-$(GCC_VERSION).tar.gz

get_binutils: src-binutils
	cd binutils-build; ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --with-sysroot --disable-werror
	$(MAKE) -C binutils-build -j4
	$(MAKE) -C binutils-build install
	rm -rf binutils-build binutils-$(BINUTILS_VERSION)
	rm -rf binutils-$(BINUTILS_VERSION).tar.gz

#
# Files setup for compilation
#
src-binutils: binutils-$(BINUTILS_VERSION)/ cmd_utils
	mkdir -p binutils-build

src-gcc: gcc-$(GCC_VERSION)/
	mkdir -p gcc-build

#
# Unpack functions
#
gcc-$(GCC_VERSION)/: always gcc-$(GCC_VERSION).tar.gz
	tar $(TAR_FLAGS) gcc-$(GCC_VERSION).tar.gz

binutils-$(BINUTILS_VERSION)/: always binutils-$(BINUTILS_VERSION).tar.gz
	tar $(TAR_FLAGS) binutils-$(BINUTILS_VERSION).tar.gz
# 
# Src download helper functions
#
binutils-$(BINUTILS_VERSION).tar.gz:
	wget $(WGET_FLAGS) https://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.gz

gcc-$(GCC_VERSION).tar.gz:
	wget $(WGET_FLAGS) https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VERSION)/gcc-$(GCC_VERSION).tar.gz

#
# Clean
#
clean: delete_src

delete_src:
	rm -rf 

clean_binaries:
	rm -rf $(PREFIX)*