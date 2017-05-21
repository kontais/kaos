ISODIR=isodir
ISO=myos.iso

.PHONY: all clean kernel iso $(ISODIR)/boot/kernel.bin


all: $(ISO)
iso: $(ISO)
kernel: isodir/boot/kernel.bin

$(ISODIR)/boot/kernel.bin: $(ISODIR)
	make -C kernel
	cp kernel/kernel.bin $(ISODIR)/boot/kernel.bin

$(ISODIR):
	mkdir -p $(ISODIR)
	mkdir -p $(ISODIR)/boot
	mkdir -p $(ISODIR)/boot/grub


$(ISODIR)/boot/grub/grub.cfg: $(ISODIR)
	echo "set timeout=0"					>  $(ISODIR)/boot/grub/grub.cfg
	echo "set default=0"					>> $(ISODIR)/boot/grub/grub.cfg
	echo ""									>> $(ISODIR)/boot/grub/grub.cfg
	echo "menuentry \"my os\" {"			>> $(ISODIR)/boot/grub/grub.cfg
	echo "	multiboot2 /boot/kernel.bin"	>> $(ISODIR)/boot/grub/grub.cfg
	echo "	boot"							>> $(ISODIR)/boot/grub/grub.cfg
	echo "}"								>> $(ISODIR)/boot/grub/grub.cfg

$(ISO): $(ISODIR)/boot/kernel.bin $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(ISODIR)

bochs: $(ISO)
	DISPLAY=:0 bochs -rc bochscommands

qemu: $(ISO)
	qemu-system-x86_64 -cdrom myos.iso -monitor stdio -curses

qemu-X: $(ISO)
	DISPLAY=:0 qemu-system-x86_64 -cdrom myos.iso -monitor stdio

clean:
	make -C kernel clean
	rm -rf $(ISODIR)
	rm -f $(ISO)


