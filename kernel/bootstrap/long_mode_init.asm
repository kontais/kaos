global long_mode_start
extern kernel_main
extern _stack_end

section .text
bits 64
long_mode_start:
	; load 0 into all data segment registers
	mov ax, 0
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov rsp, _stack_end

	; call the kernel main
	call kernel_main

	; print `OKAY` to screen
	mov rax, 0x2f442f4e2f452f20
	mov qword [0xb8000 + 80 * 25 * 2 - 8], rax
shutdown:
	hlt
	jmp shutdown
