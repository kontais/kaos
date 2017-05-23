#pragma once

#include <bootstrap/multiboot.h>


namespace paging::allocator
{
	void initEarly(const multiboot::MemoryMap& memoryMap);
	uint64_t allocatePage();
	uint64_t allocateHugePage();
}
