#include <sys/mman.h>
#include "../../screen/screen.h"
#include "../../mm/paging.h"
#include "../../mm/page_allocator.h"

extern "C"
{

void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset)
{
	screen::write("\nmmap: ");
	screen::writePtr(addr);
	screen::write(", ");
	screen::writeInt(length);
	screen::write(", ");
	screen::writePtr((void*)(uint64_t)prot);
	screen::write(", ");
	screen::writePtr((void*)(uint64_t)flags);
	screen::write(", ");
	screen::writeInt(fd);
	screen::write(", ");
	screen::writePtr((void*)(uint64_t)offset);

	static uint8_t* currentKernelHeap = (uint8_t*)0xFFFFFFFF40000000;
	void* ret = currentKernelHeap;

	for(size_t c = 0; c < length; c += paging::pageSize, currentKernelHeap += paging::pageSize)
	{
		const auto page = paging::allocator::allocatePage();
		paging::mapPage(page, currentKernelHeap, false, paging::writeable | paging::executeDisable);
	}

	return ret;
}

int munmap(void *addr, size_t length)
{
	screen::write("\nmunmap: ");
	screen::writePtr(addr);
	screen::write(", ");
	screen::writeInt(length);

	return 0;
}

void abort()
{
	screen::write("\nABORT CALLED\n");
	while(true);
}


void *memset(void *s, int c, size_t n)
{
	uint8_t* t = static_cast<uint8_t*>(s);

	for(uint64_t i = 0; i < n; i++)
	{
		t[i] = c;
	}

	return s;
}

void *memcpy(void *destP, const void *srcP, size_t amount)
{
	auto dest = static_cast<uint8_t*>(destP);
	auto src = static_cast<const uint8_t*>(srcP);

	for(size_t i = 0; i < amount; ++i)
	{
		dest[i]=src[i];
	}

	return destP;
}

}