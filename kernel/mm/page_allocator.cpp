#include "page_allocator.h"
#include "../screen/screen.h"
#include "../bootstrap/linker_symbols.h"
#include <cstdint>


using TableType = uint64_t;
constexpr uint64_t pageSize = 4 * 1024;
constexpr uint64_t hugePageSize = 2 * 1024 * 1024;
constexpr uint64_t initialOffset = 4 * 1024 * 1024;
constexpr uint64_t tableTypeBits = sizeof(TableType) * 8;
constexpr uint64_t initialMemoryMapped = hugePageSize * tableTypeBits;
constexpr uint64_t hugePageMultiplier = hugePageSize / pageSize;
constexpr uint64_t pageArraySize = initialMemoryMapped / pageSize / tableTypeBits;

TableType initialHugePages = 0;
TableType initialPages[pageArraySize] = {};

void markPage(const uint64_t offset, const bool set, const bool recurse = true);
void markPageHuge(const uint64_t offset, const bool set, const bool recurse = true);
bool isFree(const uint64_t offset);
bool isFreeHuge(const uint64_t offset);

void markHugePageByPage(const uint64_t offset)
{
	const auto rawOffset = offset & (hugePageSize - 1);
	bool allClear = true;

	for(uint64_t offset = 0; offset < hugePageSize; offset += pageSize)
	{
		if(!isFree(rawOffset + offset))
		{
			allClear = false;
			break;
		}
	}

	markPageHuge(offset, allClear, false);
}

void markPage(const uint64_t offset, const bool set, const bool recurse)
{
	const auto page = (offset / pageSize) / 64;
	const auto bit  = (offset / pageSize) % 64;

	if(set)
	{
		initialPages[page] |= 1ULL << bit;
	}
	else
	{
		initialPages[page] &= ~(1ULL << bit);
		// if page is in use, the corresponding huge page cannot be used either#
		if(recurse)
			markPageHuge(offset, set, false);
	}

}

bool isFree(const uint64_t offset)
{
	const auto page = (offset / pageSize) / 64;
	const auto bit  = (offset / pageSize) % 64;

	return initialPages[page] & (1ULL << bit);
}

void markPageHuge(const uint64_t offset, const bool set, const bool recurse)
{
	const auto bit = (offset / hugePageSize) % 64;

	if(set)
		initialHugePages |= 1ULL << bit;
	else
		initialHugePages &= ~(1ULL << bit);

	if(recurse)
	{
		// mirror changes for small pages
		for(uint64_t p = 0; p < hugePageMultiplier; ++p)
		{
			markPage(offset + p * pageSize, set, false);
		}
	}
}

bool isFreeHuge(const uint64_t offset)
{
	const auto bit = (offset / hugePageSize) % 64;

	return initialHugePages & (1ULL << bit);
}


void intialMarkMemoryFree(uint64_t start, const uint64_t end)
{
	int freePages = 0;

	for(; start < end; start += pageSize)
	{
		// ignore entries below 2MB for now
		if(start < initialOffset)
			continue;

		// only map the first 128MB
		if(start >= initialMemoryMapped)
			break;

		markPage(start, true, false);
		freePages++;
	}

	screen::write("\nfreePages: ");
	screen::writeInt(freePages);
}

void unmarkKernelSpace()
{
	auto kernelStart = reinterpret_cast<uint64_t>(&_kernel_physical_base);
	const auto kernelEnd = kernelStart + (&KERNEL_END - &KERNEL_START);

	screen::write("\nkernelStart: ");
	screen::writePtr((void*)kernelStart);
	screen::write("\nkernelEnd: ");
	screen::writePtr((void*)kernelEnd);

	for(; kernelStart < kernelEnd; kernelStart += pageSize)
	{
		markPage(kernelStart, false);
	}
}

void initialMarkHugePages()
{
	int totalAvailable = 0;

	for(uint64_t start = 0; start < initialMemoryMapped / hugePageSize; ++start)
	{
		bool available = true;
		for(uint64_t pageOffset = 0; pageOffset < hugePageMultiplier; ++pageOffset)
		{
			const auto page = (start * hugePageMultiplier) + pageOffset;
			const auto pageLoc = page / 64;
			const auto bit  = page % 64;
			const auto pageFreeMask = ~(1ULL << bit);

			if(!(initialPages[pageLoc] & pageFreeMask))
			{
				available = false;
				break;
			}
		}

		if(available)
		{
			markPageHuge(start * hugePageSize, true, false);
			totalAvailable++;
		}
	}
	screen::write("\ntotal Huge Available: ");
	screen::writeInt(totalAvailable);
}

void paging::allocator::initEarly(const multiboot::MemoryMap& memoryMap)
{
	using multiboot::MemoryType;

	for(auto i = 0; i < memoryMap.count; ++i)
	{
		const auto &entry = memoryMap.entries[i];

		if(entry.type == MemoryType::Available)
		{
			intialMarkMemoryFree(entry.start, entry.start + entry.length);
		}
	}

	unmarkKernelSpace();
	initialMarkHugePages();
}

uint64_t paging::allocator::allocatePage()
{
	for(uint64_t i = 0; i < pageArraySize; ++i)
	{
		// skip empty tables
		if(initialPages[i] == 0)
			continue;

		for(uint64_t b = 0; b < tableTypeBits; ++b)
		{
			const uint64_t pageLocation = (i * tableTypeBits + b) * pageSize;
			if(isFree(pageLocation))
			{
				markPage(pageLocation, false);
				//screen::write("\nallocatedPage: ");
				//screen::writePtr((void*)pageLocation);
				return pageLocation;
			}
		}
	}

	return -1ULL;
}

uint64_t paging::allocator::allocateHugePage()
{
	for(uint64_t i = 0; i < tableTypeBits; ++i)
	{
		uint64_t offset = i * hugePageSize;
		if(isFreeHuge(offset))
		{
			markPageHuge(offset, false);
			//screen::write("\nallocatedHugePage: ");
			//screen::writePtr((void*)offset);
			return offset;
		}
	}

	return -1ULL;
}
