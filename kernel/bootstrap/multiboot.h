#pragma once

#include <stdint.h>


namespace multiboot
{
	struct Header
	{
		uint32_t totalSize;
		uint32_t reserved;
	};

	void parseMultiboot(const Header* header);
}
