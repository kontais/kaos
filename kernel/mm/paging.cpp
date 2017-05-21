#include "paging.h"
#include "page_allocator.h"
#include "paging_structures.h"
#include "../bootstrap/linker_symbols.h"
#include "../screen/screen.h"
#include <string.h>


//#define PRINT_PAGING

// where in memory will be the initial pagetagles
uint8_t* physicalPageTable = (uint8_t*)0x400000ULL;
uint8_t* const mappedPageTable = (uint8_t*)0xFFFFFFFF80000000ULL;

class PageTables
{
public:
	void init()
	{
		physicalPageTable = reinterpret_cast<uint8_t*>(paging::allocator::allocateHugePage());

		memset(physicalPageTable, 0, pageTableMapSize);

		nextFreePageTable = physicalPageTable;
		masterPageTable = physicalPageTable;
		physicalMapping[0] = (uint64_t)physicalPageTable;
		for(uint64_t i = 1; i < PageTables::numPagetableMappings; ++i)
			physicalMapping[i] = 0;

		for(uint64_t i = 0; i < (pageTableMapSize / pageSize) - 1; ++i)
		{
			int64_t* p = (int64_t*)&physicalPageTable[i * pageSize];
			*p = pageSize; // point to next free page
		}

		// reserve master page table
		allocatePageTablePage();
	}

	void mapPageTableTo(void* linearAddress)
	{
		auto pt = getPhysicalOffset(nextFreePageTable);

#ifdef PRINT_PAGING
		screen::write("\nmapPageTableTo:");
		screen::writePtr(linearAddress);
		screen::write("\nnextFreePageTable:");
		screen::writePtr(nextFreePageTable);
		screen::write(" --> ");
		screen::writePtr((void*)pt);
#endif

		masterPageTable = (uint8_t *)linearAddress;
		nextFreePageTable = (uint8_t *)getVirtualOffset(pt);

#ifdef PRINT_PAGING
		screen::write("\nnextFreePageTable:");
		screen::writePtr(nextFreePageTable);
		screen::write(" --> ");
		screen::writePtr(nextFreePageTable);
#endif	

	}

	uint64_t getPhysicalOffset(void* address)
	{
		auto offsetRaw = reinterpret_cast<uint64_t>(address) - reinterpret_cast<uint64_t>(masterPageTable);
		auto offsetMapping = offsetRaw / pageTableMapSize;
		auto offsetWithinMapping = offsetRaw % pageTableMapSize;

		return physicalMapping[offsetMapping] + offsetWithinMapping;
	}

	void* getVirtualOffset(uint64_t address)
	{
		for(uint64_t i = 0; i < numPagetableMappings; ++i)
		{
			const auto physicalOffset = physicalMapping[i];
			if(address >= physicalOffset && address < (physicalOffset + pageTableMapSize))
			{
				auto virtualOffset = masterPageTable + (i * pageTableMapSize);
				return virtualOffset + address - physicalOffset;
			}
		}
		return nullptr;
	}

	void* allocatePageTablePage()
	{
		uint64_t* page = (uint64_t*)nextFreePageTable;

		int64_t* nextFree = (int64_t*)nextFreePageTable;
		nextFreePageTable = nextFreePageTable + *nextFree;

#ifdef PRINT_PAGING
		screen::write("\nnextFreePageTable:");
		screen::writePtr(nextFreePageTable);
#endif

		memset(page, 0, 4096);

		return page;
	}

	uint64_t* getMasterPageTable()
	{
		return (uint64_t*)masterPageTable;
	}


private:
	static constexpr uint64_t pageTableMapSize = 0x200000ULL;
	static constexpr uint64_t pageSize = 4096;
	static constexpr uint64_t numPagetableMappings = 512;

	uint8_t* nextFreePageTable;
	uint64_t physicalMapping[numPagetableMappings];
	uint8_t* masterPageTable;
};

PageTables pageTables;

void paging::mapPage(uint64_t physicalAddress, const void* linearAddress, const bool use2MB, const uint64_t flags)
{
	using namespace screen;
	using namespace paging;

#ifdef PRINT_PAGING
	screen::write("\nmapPage:");
	screen::writePtr(linearAddress);
	screen::write(" --> ");
	screen::writePtr((void*)physicalAddress);
#endif

	uint64_t lAddr = (uint64_t)linearAddress;
	auto p4Offset = (lAddr >> (12+9+9+9)) & 0x1FF;
	auto p4Entry = &pageTables.getMasterPageTable()[p4Offset];

	if(!(*p4Entry & present))
	{
		auto page = pageTables.allocatePageTablePage();
		auto pagePhysical = pageTables.getPhysicalOffset(page);
		*p4Entry = (pagePhysical  & addressMask) | present | writeable;
	}

#ifdef PRINT_PAGING
	screen::write("\np4Offset:");
	writeInt(p4Offset);
	screen::write(" p4Entry:");
	writePtr((void*)*p4Entry);
#endif

	const auto p3Base = (uint64_t*)pageTables.getVirtualOffset(*p4Entry & addressMask);
	auto p3Offset = (lAddr >> (12+9+9)) & 0x1FF;
	auto p3Entry = &p3Base[p3Offset];

#ifdef PRINT_PAGING
	screen::write("\np3Offset:");
	writeInt(p3Offset);
	screen::write(" p3Base:");
	writePtr((void*)p3Base);
#endif

	if(!(*p3Entry & present))
	{
		auto page = pageTables.allocatePageTablePage();
		auto pagePhysical = pageTables.getPhysicalOffset(page);
		*p3Entry = (pagePhysical  & addressMask) | present | writeable;
	}

#ifdef PRINT_PAGING
	screen::write(" p3Entry:");
	writePtr((void*)*p3Entry);
#endif

	const auto p2Base = (uint64_t*)pageTables.getVirtualOffset(*p3Entry & addressMask);
	auto p2Offset = (lAddr >> (12+9)) & 0x1FF;
	auto p2Entry = &p2Base[p2Offset];

	if(!(*p2Entry & present))
	{
		if(use2MB || *p2Entry & page2Mb)
		{
			*p2Entry = (physicalAddress  & addressMask) | present | page2Mb | flags;
#ifdef PRINT_PAGING
			screen::write("\np2Offset:");
			writeInt(p2Offset);
			screen::write(" p2Base:");
			writePtr((void*)p2Base);
			screen::write(" p2Entry:");
			writePtr((void*)*p2Entry);
#endif
			return;
		}
		else
		{
			auto page = pageTables.allocatePageTablePage();
			auto pagePhysical = pageTables.getPhysicalOffset(page);
			*p2Entry = (pagePhysical  & addressMask) | present | writeable;
		}
	}

#ifdef PRINT_PAGING
	screen::write("\np2Offset:");
	writeInt(p2Offset);
	screen::write(" p2Base:");
	writePtr((void*)p2Base);
	screen::write(" p2Entry:");
	writePtr((void*)*p2Entry);
#endif

	const auto p1Base = (uint64_t*)pageTables.getVirtualOffset(*p2Entry & addressMask);
	auto p1Offset = (lAddr >> (12)) & 0x1FF;
	auto p1Entry = &p1Base[p1Offset];

	if(!(*p1Entry & present))
	{
		*p1Entry = (physicalAddress  & addressMask) | present | flags;
	}

#ifdef PRINT_PAGING
	screen::write("\np1Offset:");
	writeInt(p1Offset);
	screen::write(" p1Base:");
	writePtr((void*)p1Base);
	screen::write(" p1Entry:");
	writePtr((void*)*p1Entry);
#endif
}

void paging::mapRange(uint64_t physicalAddress, const void* linearAddress, int64_t size, const uint64_t flags)
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
#define KMAP(x, flags) mapRange(POFF(x), VOFF(x), LEN(x), flags)

void paging::init()
{
	pageTables.init();

	mapPage((int64_t)physicalPageTable, mappedPageTable, true);

	KMAP(rodata, executeDisable);
	KMAP(text, 0);
	KMAP(data, writeable | executeDisable);
	KMAP(bss, writeable | executeDisable);
	KMAP(data_rel, writeable | executeDisable);
	KMAP(other, writeable | executeDisable);
	KMAP(stack, writeable | executeDisable);

	mapPage(0, (void*)0, true);

	asm volatile("movq %%rax, %%cr3;"
					:
					: "a" (physicalPageTable)
					: );

	pageTables.mapPageTableTo(mappedPageTable);
}
