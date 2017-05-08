if grub-file --is-x86-multiboot isodir/boot/kernel.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi

if grub-file --is-x86-multiboot2 isodir/boot/kernel.bin; then
  echo multiboot2 confirmed
else
  echo the file is not multiboot2
fi


