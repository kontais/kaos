OBJ = \
	interrupt/interrupt.o \
	screen/screen.o \
	paging/paging.o \
	kernel.o \
	bootstrap/boot.o \
	bootstrap/long_mode_init.o \
	bootstrap/multiboot_header.o

KERNEL_TARGET=kernel.bin

CC=clang-5.0
CXX=clang++-5.0
LD=ld
AS=as
NASM=nasm

CFLAGS=-mno-red-zone -mcmodel=large -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti --target=x86_64-pc-none-elf
CXXFLAGS=$(CFLAGS) --std=c++1z

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



