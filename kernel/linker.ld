ENTRY(_start)

_stack_size = 1024 * 1024;
_bootstrap_physical_base = 1M;
_kernel_physical_base = 2M;
_kernel_virtual_offset = 0xFFFFFFFFC0000000;

SECTIONS
{
	. = _bootstrap_physical_base;

	.bootstrap ALIGN(4K) :
	{
		/* ensure that the multiboot header is at the beginning */
		KEEP(*(.multiboot_header))
		build/bootstrap/boot.o
		build/bootstrap/long_mode_init.o
	}

	. = _kernel_virtual_offset;
	. = ALIGN(4K);

	KERNEL_START = .;
	_rodata_start = .;

	.rodata : AT(ADDR(.rodata) - _kernel_virtual_offset + _kernel_physical_base)
	{
		*(.rodata .rodata.*)
		. = ALIGN(4K);
	}

	_rodata_end = .;
	_text_start = .;

	.text : AT(ADDR(.text) - _kernel_virtual_offset + _kernel_physical_base)
	{	
		*(.text .text.*)
		. = ALIGN(4K);
	}

	_text_end = .;
	_data_start = .;

	.data : AT(ADDR(.data) - _kernel_virtual_offset + _kernel_physical_base)
	{
		*(.data .data.*)
		. = ALIGN(4K);
	}

	_data_end = .;
	_bss_start = .;

	.bss : AT(ADDR(.bss) - _kernel_virtual_offset + _kernel_physical_base)
	{
		*(.bss .bss.*)
		. = ALIGN(4K);
	}

	_bss_end = .;
	_data_rel_start = .;

	.data.rel.ro ALIGN(4K) : AT(ADDR(.data.rel.ro) - _kernel_virtual_offset + _kernel_physical_base)
	{
		*(.data.rel.ro.local*) *(.data.rel.ro .data.rel.ro.*)
		. = ALIGN(4K);
	}

	_data_rel_end = .;
	_other_start = .;

	.other : AT(ADDR(.other) - _kernel_virtual_offset + _kernel_physical_base)
	{
		*(.debug*)
		. = ALIGN(4K);
	}
	
	_other_end = .;
	_stack_start = .;

	.stack : AT(ADDR(.stack) - _kernel_virtual_offset + _kernel_physical_base)
	{
		. += _stack_size;
	}
	
	_stack_end = .;
	KERNEL_END = .;
}