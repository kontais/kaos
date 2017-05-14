OBJ = \
	bootstrap/multiboot.o \
	interrupt/interrupt.o \
	screen/screen.o \
	mm/paging.o \
	mm/paging_early.o \
	kernel.o \
	bootstrap/boot.o \
	bootstrap/long_mode_init.o \
	bootstrap/multiboot_header.o
#	mm/malloc.o \


KERNEL_TARGET=kernel.bin

CC=clang-5.0
CXX=clang++-5.0
LD=ld
AS=as
NASM=nasm
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
#-DLACKS_ERRNO_H -DNO_MALLOC_STATS -DLACKS_TIME_H -DLACKS_STDLIB_H -DLACKS_STRING_H 
JEMALLOC_DEFINES=-DUSE_SPIN_LOCKS=0 -DHAVE_MORECORE=0 -DHAVE_MMAP=0 -DHAVE_MREMAP=0 -DNO_MALLOC_STATS=1 \
  -DLACKS_UNISTD_H -DLACKS_FCNTL_H -DLACKS_SYS_PARAM_H -DLACKS_SYS_MMAN_H \
  -DLACKS_STRINGS_H -DLACKS_STRING_H -DLACKS_SYS_TYPES_H -DLACKS_ERRNO_H \
  -DLACKS_STDLIB_H -DLACKS_SCHED_H -DLACKS_TIME_H -DMALLOC_FAILURE_ACTION
LIB_C=-I$(ROOT_DIR)/libc/include -D__ELF__ -D_ISOC11_SOURCE -nostdinc
LIB_CXX=-I$(ROOT_DIR)/libcxx/include -D__ELF__ -D_LIBCPP_HAS_NO_THREADS -nostdinc++
CFLAGS=-mno-red-zone -mcmodel=large -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti --target=x86_64-pc-none-elf $(LIB_C) $(JEMALLOC_DEFINES)
CXXFLAGS= --std=c++1z $(LIB_CXX) $(CFLAGS)


.PHONY: all test clean

all: kernel.bin

%.o: %.c
	$(CC) -c $(CFLAGS) $< -MMD -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -MMD -o $@

%.o: %.s
	$(AS) $< -o $@

%.o: %.asm
	$(NASM) -felf64 $< -o $@

clean:
	rm -f $(OBJ) $(KERNEL_TARGET) $(OBJ:.o=.d)

kernel.bin: $(OBJ)
	$(LD) -n -T linker.ld -o $(KERNEL_TARGET) -O2 -nostdlib $(OBJ)

DEPS := $(OBJ:.o=.d)
-include $(DEPS)

#.IGNORE : stdlib/include

