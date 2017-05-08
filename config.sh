SYSTEM_HEADER_PROJECTS="kernel"
PROJECTS="kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=ar
export AS=as
export CC=clang-5.0
export CXX=clang++-5.0

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 --target=i686-pc-none-elf -march=i686'
export CPPFLAGS='-O2 --target=i686-pc-none-elf -march=i686'

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/isodir"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
