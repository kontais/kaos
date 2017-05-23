#include "multiboot.h"
#include <screen/screen.h>


struct MultibyteTag
{
	uint32_t type;
	uint32_t size;
	union
	{
		struct
		{
			uint32_t buidDevice;
			uint32_t partition;
			uint32_t subPartition;
		} biosBootDevice;
		struct
		{
			char string[32];
		} bootCommandLine;
		struct
		{
			uint32_t modulesStart;
			uint32_t modulesEnd;
			char string[32];
		} modules;
		struct
		{
			uint32_t entrySize;
			uint32_t entryVersion;
			struct
			{
				uint64_t baseAddress;
				uint64_t length;
				uint32_t type;
				uint32_t reserved;
			} entries[1];
		} memoryMap;
		struct
		{
			char string[32];
		} bootLoaderName;
	};
};
struct MBMemoryMapEntry
{
	uint64_t baseAddress;
	uint64_t length;
	uint32_t type;
	uint32_t reserved;
};

multiboot::MultibootInfo multiboot::parseMultiboot(const Header* header)
{
	MultibootInfo ret;

	screen::write("multiboot info location: ");
	screen::writePtr(header);
	screen::write("\nmultiboot length: ");
	screen::writeInt(header->totalSize);

	uint8_t* currentLoc = ((uint8_t*)header) + 8;
	const uint8_t* headerEnd = ((uint8_t*)header) + header->totalSize;

	while(currentLoc < headerEnd)
	{
		MultibyteTag* currentTag = (MultibyteTag*)currentLoc;

		screen::write("\nfound tag: ");
		screen::writeInt(currentTag->type);
		screen::write("  size: ");
		screen::writeInt(currentTag->size);

		if(currentTag->type == 6)
		{
			screen::write("\nentrySize: ");
			screen::writeInt(currentTag->memoryMap.entrySize);
			screen::write("  version: ");
			screen::writeInt(currentTag->memoryMap.entryVersion);

			char* entryC = (char*)currentTag->memoryMap.entries;
			char* entryEnd = entryC+currentTag->size;

			ret.memoryMap.count = 0;

			while(entryC < entryEnd)
			{
				MBMemoryMapEntry* entry = (MBMemoryMapEntry*)entryC;

				screen::write("\nbase: ");
				screen::writePtr((void*)entry->baseAddress);
				screen::write("  length: ");
				screen::writePtr((void*)entry->length);
				screen::write("  type: ");
				screen::writeInt(entry->type);
				screen::write("  reserved: ");
				screen::writeInt(entry->reserved);

				if(ret.memoryMap.count < memoryMapEntries)
				{
					ret.memoryMap.entries[ret.memoryMap.count].start = entry->baseAddress;
					ret.memoryMap.entries[ret.memoryMap.count].length = entry->length;
					ret.memoryMap.entries[ret.memoryMap.count].type = (MemoryType)entry->type;
					ret.memoryMap.count++;
				}

				entryC += currentTag->memoryMap.entrySize;
			}
		}
		
		const auto paddedSize = (currentTag->size+7) & 0xFFFFFFF8U;
		currentLoc += paddedSize;
	}

	return ret;
}
