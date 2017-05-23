#include "interrupt.h"
#include <cstdint>
#include <screen/screen.h>

/**
 Interrupt Table: (intel manual: 6.4.1, reference: 6.15)
 0     #DE    Divide Error
              DIV and IDIV instructions.
 1     #DB    Debug
              Any code or data reference.
 2     NMI    Interrupt
              Non-maskable external interrupt.
 3     #BP    Breakpoint
              INT 3 instruction.
 4     #OF    Overflow
              INTO instruction.
 5     #BR    BOUND Range Exceeded
              BOUND instruction.
 6     #UD    Invalid Opcode (UnDefined Opcode)
              UD instruction or reserved opcode.
 7     #NM    Device Not Available (No Math Coprocessor)
              Floating-point or WAIT/FWAIT instruction
 8     #DF    Double Fault
              Any instruction that can generate an exception, an NMI, or an INTR.
 9     #MF    CoProcessor Segment Overrun (reserved)
              Floating-point instruction.
10     #TS    Invalid TSS
              Task switch or TSS access.
11     #NP    Segment Not Present
              Loading segment registers or accessing system segments.
12     #SS    Stack Segment Fault
              Stack operations and SS register loads.
13     #GP    General Protection
              Any memory reference and other protection checks.
14     #PF    Page Fault
              Any memory reference.
15     Reserved
16     #MF    Floating-Point Error (Math Fault)
              Floating-point or WAIT/FWAIT instruction.
17     #AC    Alignment Check
              Any data reference in memory.
18     #MC    Machine Check
              Error codes (if any) and source are model dependent.
19     #XM    SIMD Floating-Point Exception
              SIMD Floating-Point Instruction
20     #VE    Virtualization Exception
              EPT violations
21-31  Reserved
32-255 Maskable Interrupts External interrupt from INTR pin or INT n instruction.
*/

namespace interrupt
{
struct __attribute__((packed)) IDTDescription
{
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t flags; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};


struct __attribute__((packed)) IDTPointer{
   uint16_t   limit;
   uint64_t   base;
};


struct __attribute__((packed)) GDTDescription
{
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};

struct __attribute__((packed)) GDTPointer{
   uint16_t   limit;
   uint64_t   base;
};

IDTDescription idt[256];
IDTPointer idtPointer;

constexpr auto gdtCount = 4;
GDTDescription gdt[gdtCount];
GDTPointer gdtPointer;

void zeromem(void* target, uint64_t count)
{
	auto t = reinterpret_cast<uint8_t*>(target);

	for(uint64_t i = 0; i < count; i++)
	{
		t[i] = 0;
	}
}

void initGDT()
{
   	screen::write("Initialize GDT...");
	gdtPointer.limit = sizeof(GDTDescription) * gdtCount -1;
	gdtPointer.base = reinterpret_cast<uint64_t>(&gdt[0]);

	zeromem(gdt, sizeof(gdt));

	//gdt[1].

	//asm volatile("lgdt %0" : : "m" (gdtPointer));
   	screen::write(" done!\n");
}

using uword_t = unsigned long long int;

struct interrupt_frame
{
	uword_t ip;
	uword_t cs;
	uword_t flags;
	uword_t sp;
	uword_t ss;
};

__attribute__ ((interrupt))
void pageFault(interrupt_frame *frame)
{
	screen::write("\ninterrupt page fault...");
	screen::write("\n  ip:   ");
	screen::writePtr((void*)frame->ip);
	screen::write("\n  cs:   ");
	screen::writePtr((void*)frame->cs);
	screen::write("\n  flags:");
	screen::writePtr((void*)frame->flags);
	screen::write("\n  sp:   ");
	screen::writePtr((void*)frame->sp);
	screen::write("\n  ss:   ");
	screen::writePtr((void*)frame->ss);
	screen::write("\n");

	while(true);
}

template<int n>
__attribute__ ((interrupt))
void testhandler(interrupt_frame *frame)
{
	screen::write("\ninterrupt ");
	screen::writeInt(n);
	screen::write(" page fault...");
	screen::write("\n  ip:   ");
	screen::writePtr((void*)frame->ip);
	screen::write("\n  cs:   ");
	screen::writePtr((void*)frame->cs);
	screen::write("\n  flags:");
	screen::writePtr((void*)frame->flags);
	screen::write("\n  sp:   ");
	screen::writePtr((void*)frame->sp);
	screen::write("\n  ss:   ");
	screen::writePtr((void*)frame->ss);
	screen::write("\n");

	while(true);
}

void setISR(int interrupt, void(*handler)(interrupt_frame*), uint16_t selector, uint8_t flags)
{
	const auto handlerInt = reinterpret_cast<uint64_t>(handler);
	idt[interrupt].offset_1 = (handlerInt >>  0) & 0xffff;
	idt[interrupt].offset_2 = (handlerInt >> 16) & 0xffff;
	idt[interrupt].offset_3 = (handlerInt >> 32) & 0xffffffff;

	idt[interrupt].selector = selector;
	idt[interrupt].flags = flags;

	idt[interrupt].ist = 0;
	idt[interrupt].zero = 0;

#if 0
   	screen::write("setup interrupt(");
	screen::writeInt(interrupt);
   	screen::write(")\n  offset1: ");
	screen::writeInt(idt[interrupt].offset_1);
   	screen::write("\n  offset2: ");
	screen::writeInt(idt[interrupt].offset_2);
   	screen::write("\n  offset3: ");
	//screen::writeInt(idt[interrupt].offset_3);
   	//screen::write("\n  selector: ");
	screen::writeInt(idt[interrupt].selector);
   	screen::write("\n  flags: ");
	screen::writeInt(idt[interrupt].flags);
   	screen::write("\n  ist: ");
	screen::writeInt(idt[interrupt].ist);
   	screen::write("\n  zero: ");
	screen::writeInt(idt[interrupt].zero);
   	screen::write("\n");
#endif
}
}

void interrupt::init()
{
	idtPointer.limit = sizeof(IDTDescription) * 256 -1;
	idtPointer.base = reinterpret_cast<uint64_t>(&idt[0]);

	zeromem(idt, sizeof(idt));

	
	setISR(0, testhandler<0>, 0x08, 0x8E);
	setISR(1, testhandler<1>, 0x08, 0x8E);
	setISR(2, testhandler<2>, 0x08, 0x8E);
	setISR(3, testhandler<3>, 0x08, 0x8E);
	setISR(4, testhandler<4>, 0x08, 0x8E);
	setISR(5, testhandler<5>, 0x08, 0x8E);
	setISR(6, testhandler<6>, 0x08, 0x8E);
	setISR(7, testhandler<7>, 0x08, 0x8E);
	setISR(8, testhandler<8>, 0x08, 0x8E);
	setISR(9, testhandler<9>, 0x08, 0x8E);
	setISR(10, testhandler<10>, 0x08, 0x8E);
	setISR(11, testhandler<11>, 0x08, 0x8E);
	setISR(12, testhandler<12>, 0x08, 0x8E);
	setISR(13, testhandler<13>, 0x08, 0x8E);
	setISR(14, pageFault, 0x08, 0x8E);
	setISR(15, testhandler<15>, 0x08, 0x8E);
	setISR(16, testhandler<16>, 0x08, 0x8E);
	setISR(17, testhandler<17>, 0x08, 0x8E);
	setISR(18, testhandler<18>, 0x08, 0x8E);
	setISR(19, testhandler<19>, 0x08, 0x8E);
	
	setISR(200, testhandler<200>, 0x08, 0x8E);

   	screen::write("Enable IDT\n");
	//asm volatile("lgdt %0" : : "m" (gdtp));
	asm volatile("lidt %0" : : "m" (idtPointer));
}

void interrupt::enable()
{
   	screen::write("enable interrupts\n");
	asm volatile("sti");
   	screen::write("enable interrupts: DONE\n");
}

void interrupt::disable()
{
   	screen::write("enable interrupts\n");
	asm volatile("cli");
   	screen::write("enable interrupts: DONE\n");
}
