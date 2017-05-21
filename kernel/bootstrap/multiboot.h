#pragma once

#include <cstdint>


namespace multiboot
{
	struct Header
	{
		uint32_t totalSize;
		uint32_t reserved;
	};

	enum class MemoryType
	{
		Available = 1,
		Reserved = 2,
		AcpiReclaimable = 3,
		AcpiNVS = 4,
		BadMemory = 5,
		Pci = 11, // unknown?
	};

	struct MemoryMapEntry
	{
		uint64_t start;
		uint64_t length;
		MemoryType type;
	};

	constexpr auto memoryMapEntries = 32;
	struct MemoryMap
	{
		int count;
		MemoryMapEntry entries[memoryMapEntries];
	};

	struct MultibootInfo
	{
		MemoryMap memoryMap;
	};

	MultibootInfo parseMultiboot(const Header* header);
}
