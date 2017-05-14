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
//xp /2048wx 0x400000
//x /4096wx 0x101000
//xp /1024wx 0x101000
// info tab
// 0 4 8 C
// where in memory will be the initial pagetagles
const auto initialPagingOffset = (uint64_t*)0x400000;
auto pagingOffset = initialPagingOffset;

paging::PTInfo allocatePageTablePage()
{
	static auto currentPagingOffset = initialPagingOffset;
	uint64_t* page = (uint64_t*)currentPagingOffset;
	currentPagingOffset += paging::pageSize / sizeof(uint64_t*);

	zeromem(page, 4096);

	return {reinterpret_cast<uint64_t>(page), page};
}

void mapPage(uint64_t physicalAddress, const void* linearAddress, const bool use2MB, const uint64_t flags = paging::writeable)
{
	using namespace screen;
	using namespace paging;

	screen::write("\nmapPage:");
	screen::writePtr(linearAddress);
	screen::write(" --> ");
	screen::writePtr((void*)physicalAddress);

	uint64_t lAddr = (uint64_t)linearAddress;
	auto p4Offset = (lAddr >> (12+9+9+9)) & 0x1FF;
	auto p4Entry = &pagingOffset[p4Offset];

	if(!(*p4Entry & present))
	{
		auto page = allocatePageTablePage();
		*p4Entry = (page.physicalAddress  & addressMask) | present | writeable;
	}

	screen::write("\np4Offset:");
	writeInt(p4Offset);
	screen::write(" p4Entry:");
	writePtr((void*)*p4Entry);

	const auto p3Base = (uint64_t*)(*p4Entry & addressMask);
	auto p3Offset = (lAddr >> (12+9+9)) & 0x1FF;
	auto p3Entry = &p3Base[p3Offset];

	if(!(*p3Entry & present))
	{
		auto page = allocatePageTablePage();
		*p3Entry = (page.physicalAddress  & addressMask) | present | writeable;
	}

	screen::write("\np3Offset:");
	writeInt(p3Offset);
	screen::write(" p3Base:");
	writePtr((void*)p3Base);
	screen::write(" p3Entry:");
	writePtr((void*)*p3Entry);

	const auto p2Base = (uint64_t*)(*p3Entry & addressMask);
	auto p2Offset = (lAddr >> (12+9)) & 0x1FF;
	auto p2Entry = &p2Base[p2Offset];

	if(!(*p2Entry & present))
	{
		if(use2MB || *p2Entry & page2Mb)
		{
			*p2Entry = (physicalAddress  & addressMask) | present | page2Mb | flags;
			screen::write("\np2Offset:");
			writeInt(p2Offset);
			screen::write(" p2Base:");
			writePtr((void*)p2Base);
			screen::write(" p2Entry:");
			writePtr((void*)*p2Entry);
			return;
		}
		else
		{
			auto page = allocatePageTablePage();
			*p2Entry = (page.physicalAddress  & addressMask) | present | writeable;
		}
	}

	screen::write("\np2Offset:");
	writeInt(p2Offset);
	screen::write(" p2Base:");
	writePtr((void*)p2Base);
	screen::write(" p2Entry:");
	writePtr((void*)*p2Entry);

	const auto p1Base = (uint64_t*)(*p2Entry & addressMask);
	auto p1Offset = (lAddr >> (12)) & 0x1FF;
	auto p1Entry = &p1Base[p1Offset];

	if(!(*p1Entry & present))
	{
		*p1Entry = (physicalAddress  & addressMask) | present | flags;
	}

	screen::write("\np1Offset:");
	writeInt(p1Offset);
	screen::write(" p1Base:");
	writePtr((void*)p1Base);
	screen::write(" p1Entry:");
	writePtr((void*)*p1Entry);
}

void map(uint64_t physicalAddress, const void* linearAddress, int64_t size, const uint64_t flags = paging::writeable)
{
	using namespace paging;

	char* lAddress = (char*)linearAddress;
	for(; size > 0; size -= pageSize)
	{
		mapPage(physicalAddress, lAddress, false, flags);

		physicalAddress += pageSize;
		lAddress += pageSize;
	}
}

#define POFF(x) (uint64_t)(&_##x##_start) - (uint64_t)(&_kernel_virtual_offset) + (uint64_t)(&_kernel_physical_base)
#define VOFF(x) &_##x##_start
#define LEN(x) (int64_t)(&_##x##_end) - (int64_t)(&_##x##_start)
#define KMAP(x, flags) map(POFF(x), VOFF(x), LEN(x), flags)

void paging::init()
{
	// allocate root page
	allocatePageTablePage();
	mapPage(0, (void*)0, true);
	mapPage((int64_t)initialPagingOffset, (void*)0xFFFFFFFF80000000, true);

	KMAP(rodata, executeDisable);
	KMAP(text, 0);
	KMAP(data, writeable | executeDisable);
	KMAP(bss, writeable | executeDisable);
	KMAP(data_rel, writeable | executeDisable);
	KMAP(other, writeable | executeDisable);
	KMAP(stack, writeable | executeDisable);


	asm volatile("movq %%rax, %%cr3;"
					:
					: "a" (initialPagingOffset)
					: );
}
