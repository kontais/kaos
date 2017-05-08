#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
//#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "screen/screen.h"
#include "interrupt/interrupt.h"

const extern void* _text_start;

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(void) {
	_text_start;
	screen::initialize();

	interrupt::init();

	for(int i=0;i<1;i++)
		screen::write("Hello kernel World!!\nMULTILINE! :D\na\n");

	
	
	
	screen::write("the end!\n");
}
