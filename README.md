## Initial paging when entering C++ kernel (setup by assembly):
* 0x0000000000000000 --> 0x0
* 0xFFFFFFFFC0000000 --> 0x200000

## page map after paging::init()
* 0xFFFFFFFF00000000 --> unmapped - 
* 0xFFFFFFFF40000000 --> unmapped - kernel heap
* 0xFFFFFFFF80000000 --> 0x400000 - page tables, 2MB page used
* 0xFFFFFFFFC0000000 --> 0x200000 - kernel, 2MB page used
