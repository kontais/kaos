#include <cstdint>
#include "../screen/screen.h"


namespace acpi
{
	void dsdt(void*, uint64_t);
}


void acpi::dsdt(void* ptr, uint64_t length)
{
	screen::write("\nDSDT:");
	screen::writePtr(ptr);
	screen::write(" length: ");
	screen::writeInt(length);
}
