GCC_VERSION=10.3.0
BINUTILS_VERSION=2.36.1

GDB_VERSION=8.3.1-3
PYTHON_VERSION=3.8.9-2

TARGET=i686-elf
PREFIX="/d/msys64/opt/cross/i686-elf/"

WGET_FLAGS=-q
TAR_FLAGS=-xf

.PHONY: get_gcc get_binutils src src-binutils src-gcc always clean delete_src

build: clean_binaries get_gcc

src: src-binutils src-gcc

cmd_utils:
	pacman -Sy --noconfirm
	pacman --noconfirm --needed -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb make bison flex gmp-devel \
	mpc-devel mpfr-devel texinfo diffutils python libtool patch base-devel unzip \
	mingw-w64-x86_64-libtool mingw-w64-x86_64-cmake mingw-w64-x86_64-hdf5 dosfstools
#	wget -P ~ $(WGET_FLAGS) https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-gdb-$(GDB_VERSION)-any.pkg.tar.xz
	cp ~/mingw-w64-x86_64-gdb-$(GDB_VERSION)-any.pkg.tar.xz .
	wget $(WGET_FLAGS) https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-python-$(PYTHON_VERSION)-any.pkg.tar.zst
	pacman -U --noconfirm mingw-w64-x86_64-python-$(PYTHON_VERSION)-any.pkg.tar.zst
	pacman -U --noconfirm mingw-w64-x86_64-gdb-$(GDB_VERSION)-any.pkg.tar.xz
	rm -f mingw-w64-x86_64-python-$(PYTHON_VERSION)-any.pkg.tar.zst* mingw-w64-x86_64-gdb-$(GDB_VERSION)-any.pkg.tar.xz*

get_gcc: src-gcc get_binutils 
	cd gcc-build; ../gcc-$(GCC_VERSION)/configure --target=$(TARGET) --prefix=$(PREFIX) --host=x86_64-w64-mingw32 --disable-nls --enable-languages=c,c++ --without-headers
	cd gcc-build; make -j4 all-gcc
	cd gcc-build; make all-target-libgcc
	cd gcc-build; make install-gcc install-target-libgcc
	rm -rf gcc-build
	rm -rf gcc-$(GCC_VERSION) gcc-$(GCC_VERSION).tar.gz gcc-$(GCC_VERSION).present

get_binutils: src-binutils
	cd binutils-build; ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --with-sysroot --disable-werror
	$(MAKE) -C binutils-build -j4
	$(MAKE) -C binutils-build install
	rm -rf binutils-build
	rm -rf binutils-$(BINUTILS_VERSION) binutils-$(BINUTILS_VERSION).tar.gz binutils-$(BINUTILS_VERSION).present

#
# Files setup for compilation
#
src-binutils: binutils-$(BINUTILS_VERSION).present cmd_utils
	mkdir -p binutils-build

src-gcc: gcc-$(GCC_VERSION).present cmd_utils
	mkdir -p gcc-build

#
# Unpack functions
#
gcc-$(GCC_VERSION).present: gcc-$(GCC_VERSION).tar.gz
	tar $(TAR_FLAGS) gcc-$(GCC_VERSION).tar.gz
	touch gcc-$(GCC_VERSION).present

binutils-$(BINUTILS_VERSION).present: binutils-$(BINUTILS_VERSION).tar.gz
	tar $(TAR_FLAGS) binutils-$(BINUTILS_VERSION).tar.gz
	touch binutils-$(BINUTILS_VERSION).present
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
	rm -rf gcc-$(GCC_VERSION).tar.gz gcc-$(GCC_VERSION)/ gcc-$(GCC_VERSION).present gcc-build
	rm -rf binutils-$(BINUTILS_VERSION).tar.gz binutils-$(BINUTILS_VERSION)/ binutils-$(BINUTILS_VERSION).present binutils-build

clean_binaries:
	rm -rf $(PREFIX)*