OBJ = \
	interrupt/interrupt.o \
	screen/screen.o \
	paging/paging.o \
	kernel.o \
	bootstrap/boot.o \
	bootstrap/long_mode_init.o \
	bootstrap/multiboot_header.o

KERNEL_TARGET=$(SYSROOT)/boot/kernel.bin

%.o: %.c
	clang-5.0 -c -mno-red-zone -mcmodel=large -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti --target=x86_64-pc-none-elf $< -o $@

%.o: %.cpp
	clang++-5.0 -c -mno-red-zone -mcmodel=large --std=c++1z -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti --target=x86_64-pc-none-elf $< -o $@

%.o: %.s
	as $< -o $@

%.o: %.asm
	nasm -felf64 $< -o $@

#clean:
#	rm -f $(OBJ) $(KERNEL_TARGET)
#bootstrap:
#	as -march=i686 --32 bootstrap/boot.s -o bootstrap/boot.o
#
#kernel: bootstrap
#	clang++-5.0 -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti --target=i686-pc-none-elf -march=i686
#	ld.gold -T linker.ld -o sysroot/boot/myos.kernel -O2 -nostdlib kernel.o bootstrap/boot.o

kernel: $(OBJ)
	ld -n -T linker.ld -o $(KERNEL_TARGET) -O2 -nostdlib $(OBJ)
