#pragma once

#include <cstdint>

namespace paging
{
	[[maybe_unused]]
	constexpr uint64_t executeDisable	= 1ULL << 63;
	[[maybe_unused]]
	constexpr uint64_t global			= 1 << 8;
	[[maybe_unused]]
	constexpr uint64_t page2Mb			= 1 << 7;
	[[maybe_unused]]
	constexpr uint64_t dirtyBit			= ~(1 << 6);
	[[maybe_unused]]
	constexpr uint64_t accessedBit		= ~(1 << 5);
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
	constexpr uint64_t addressMask		= 0x000FFFFFFFFFF000;

	constexpr auto pageSize = 4*1024;

	struct PTInfo
	{
		uint64_t physicalAddress;
		void* linearAddress;
	};
}
