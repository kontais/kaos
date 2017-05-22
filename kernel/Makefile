include acpi/acpica/acpica.mk

LIBC_OBJ = \
	build/libc/src/libc.o

LIBCXX_OBJ = \
	build/libcxx/src/new.o

OBJ = \
	$(LIBC_OBJ) \
	$(LIBCXX_OBJ) \
	$(ACPICA_OBJ) \
	build/acpi/acpi.o \
	build/acpi/dsdt.o \
	build/bootstrap/boot.o \
	build/bootstrap/long_mode_init.o \
	build/bootstrap/multiboot.o \
	build/bootstrap/multiboot_header.o \
	build/interrupt/interrupt.o \
	build/mm/malloc.o \
	build/mm/paging.o \
	build/mm/page_allocator.o \
	build/screen/screen.o \
	build/kernel.o


KERNEL_TARGET=kernel.bin

CC=clang-5.0
CXX=clang++-5.0
LD=ld
AS=as
NASM=nasm
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
#-DLACKS_ERRNO_H -DNO_MALLOC_STATS -DLACKS_TIME_H -DLACKS_STDLIB_H -DLACKS_STRING_H 
JEMALLOC_DEFINES=-DUSE_SPIN_LOCKS=0 -DHAVE_MORECORE=0 -DHAVE_MMAP=1 -DHAVE_MREMAP=0 -DNO_MALLOC_STATS=1 \
  -DLACKS_UNISTD_H -DLACKS_FCNTL_H -DLACKS_SYS_PARAM_H \
  -DLACKS_STRINGS_H -DLACKS_ERRNO_H \
  -DLACKS_SCHED_H -DLACKS_TIME_H -DMALLOC_FAILURE_ACTION \
  -DUSE_LOCKS=0 -DDEFAULT_GRANULARITY=2097152
LIB_C=-I. -Ilibc/include -D__ELF__ -D_ISOC11_SOURCE -nostdinc
LIB_CXX=-Ilibcxx/include -D__ELF__ -D_LIBCPP_HAS_NO_THREADS -nostdinc++
CFLAGS=-mno-red-zone -mcmodel=large -ffreestanding -O2 -Wall -Wextra -Werror --target=x86_64-pc-none-elf $(LIB_C) $(JEMALLOC_DEFINES)
CXXFLAGS= --std=c++1z -fno-exceptions -fno-rtti $(LIB_CXX) $(CFLAGS)


.PHONY: all test clean

all: kernel.bin

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -MMD -o $@

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -MMD -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $< -o $@

build/%.o: %.asm
	@mkdir -p $(dir $@)
	$(NASM) -felf64 $< -o $@

clean:
	rm -f $(OBJ) $(KERNEL_TARGET) $(OBJ:.o=.d)

kernel.bin: $(OBJ)
	$(LD) -n -T linker.ld -o $(KERNEL_TARGET) -O2 -nostdlib $(OBJ)

DEPS := $(OBJ:.o=.d)
-include $(DEPS)

#.IGNORE : stdlib/include

