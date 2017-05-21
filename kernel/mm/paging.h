#pragma once

#include <cstdint>


namespace paging
{
	[[maybe_unused]]
	constexpr uint64_t executeDisable	= 1ULL << 63;
	[[maybe_unused]]
	constexpr uint64_t writeable		= 1 << 1;

	constexpr auto pageSize = 4*1024;

	void init();

	void mapPage(uint64_t physicalAddress, const void* linearAddress, const bool use2MB, const uint64_t flags = paging::writeable);
	void mapRange(uint64_t physicalAddress, const void* linearAddress, int64_t size, const uint64_t flags = paging::writeable);
}
