#include "paging.h"
#include "paging_structures.h"
#include "../bootstrap/linker_symbols.h"
#include "../screen/screen.h"

static void zeromem(void* target, uint64_t count)
{
	auto t = reinterpret_cast<uint8_t*>(target);

	for(uint64_t i = 0; i < count; i++)
	{
		t[i] = 0;
	}
}
//xp /1024wx 0x400000
//x /4096wx 0x400000
//xp /4096wx 0x400000
//x /4096wx 0x101000
//xp /1024wx 0x101000
// info tab

[[maybe_unused]]
constexpr uint64_t executeDisable	= 1ULL << 63;
[[maybe_unused]]
constexpr uint64_t page2Mb			= 1 << 7;
[[maybe_unused]]
constexpr uint64_t cacheDisable		= 1 << 4;
[[maybe_unused]]
constexpr uint64_t writeThrough		= 1 << 3;
[[maybe_unused]]
constexpr uint64_t user				= 1 << 2;
[[maybe_unused]]
constexpr uint64_t writeable		= 1 << 1;
[[maybe_unused]]
constexpr uint64_t present			= 1 << 0;

[[maybe_unused]]
//constexpr uint64_t addressMask		= 0x000FFFFFFFFFF000;
constexpr uint64_t addressMask		= 0xFFFFFFFFFFFFFFFF;


void paging::init()
{
	const auto kernelOffset = &_kernel_virtual_offset - &_kernel_physical_base;
	const auto kernelPhysicalEnd = &KERNEL_END - kernelOffset;
	const auto oneMB = 1024*1024;
	const auto twoMB = 2*oneMB;
	const auto oneGB = 1024*oneMB;
	const auto pageSize = 4*1024;

	//const auto initialPagingOffset = (char*)(uint64_t(kernelPhysicalEnd + twoMB - 1) & ~(twoMB - 1));
	const auto initialPagingOffset = (char*)0x400000;
	const auto pagingVirtualOffset = &_kernel_virtual_offset - oneGB;

	screen::write("\n_kernel_virtual_offset:");
	screen::writePtr(&_kernel_virtual_offset);
	screen::write("\n_kernel_physical_base:");
	screen::writePtr(&_kernel_physical_base);
	screen::write("\nkernelOffset:");
	screen::writePtr((void*)kernelOffset);

	screen::write("\ninitialPagingOffset:");
	screen::writePtr(initialPagingOffset);

	screen::write("\npagingVirtualOffset:");
	screen::writePtr(pagingVirtualOffset);
	screen::write("\n");

	auto currentPagingOffset = initialPagingOffset;
/////////////////
	uint64_t* pd4 = (uint64_t*)currentPagingOffset;
	currentPagingOffset += pageSize;

	zeromem(pd4, 4096);
	pd4[511] = ((uint64_t)currentPagingOffset & addressMask) | present | writeable;
/////////////////
	uint64_t* pd3 = (uint64_t*)currentPagingOffset;
	currentPagingOffset += pageSize;

	zeromem(pd3, 4096);
	pd3[511] = ((uint64_t)currentPagingOffset & addressMask) | present | writeable;
/////////////////
	uint64_t* pd2 = (uint64_t*)currentPagingOffset;
	currentPagingOffset += pageSize;

	zeromem(pd2, 4096);
	for(auto i = 0; i < 512; ++i)
	{
		const uint64_t offset = twoMB * i + twoMB;
		pd2[i] = (offset & addressMask) | page2Mb | present | writeable;
	}

	const auto cr3 = initialPagingOffset;
	screen::write("\ncr3:");
	screen::writePtr(cr3);

	asm volatile("movq %%rax, %%cr3;"
					:
					: "a" (cr3)
					: );
}
