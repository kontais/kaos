#include "acpi.h"
#include "structures.h"
#include "../screen/screen.h"
#include "../mm/paging.h"

namespace acpi
{
	void dsdt(void*, uint64_t);
}

bool checksumACPIStructure(void* address, int length)
{
	auto ptr = (uint8_t*)address;
	auto end = ptr + length;
	uint8_t sum = 0;

	while(ptr < end)
	{
		sum += *ptr;
		++ptr;
	}

	screen::write("\nchecksumACPIStructure: ");
	screen::writeInt(sum);
	
	return sum == 0;
}

void parseDSDT(acpi::ACPISDTHeader* header)
{
	screen::write("\nDSDT:");
	screen::writePtr(header);
	screen::write(" length: ");
	screen::writeInt(header->Length-sizeof(*header));

	acpi::dsdt(&header[1], header->Length-sizeof(*header));
}

void parseFACP(acpi::FADT* facp, uint64_t mappedOffset)
{
	screen::write("\nFirmwareCtrl: ");
	screen::writePtr((void*)(uint64_t)facp->FirmwareCtrl);
	screen::write("\nDsdt: ");
	screen::writePtr((void*)(uint64_t)facp->Dsdt);

	screen::write("\nPreferredPowerManagementProfile: ");
	screen::writeInt(facp->PreferredPowerManagementProfile);
	screen::write("\nSCI_Interrupt: ");
	screen::writeInt(facp->SCI_Interrupt);
	screen::write("\nSMI_CommandPort: ");
	screen::writeInt(facp->SMI_CommandPort);
	screen::write("\nAcpiEnable: ");
	screen::writeInt(facp->AcpiEnable);
	screen::write("\nAcpiDisable: ");
	screen::writeInt(facp->AcpiDisable);

	parseDSDT((acpi::ACPISDTHeader*)(uint64_t)(facp->Dsdt+mappedOffset));
}

void readACPITable(void* address, uint64_t mappedOffset)
{
	screen::write("\nreadACPITable: ");
	screen::writePtr(address);
	auto header = (acpi::ACPISDTHeader*)((char*)address + mappedOffset);
	screen::write(" virt: ");
	screen::writePtr(header);
	screen::write("\n");
	screen::write(header->Signature);
	
	if(	header->Signature[0] == 'F' &&
		header->Signature[1] == 'A' &&
		header->Signature[2] == 'C' &&
		header->Signature[3] == 'P')
		parseFACP((acpi::FADT*)header, mappedOffset);
}

void acpi::init()
{
	// "RSD PTR "
	const auto rsdpSig = 0x2052545020445352;

	auto* acpiSearch = (uint64_t*)0xE0000;

	while(*acpiSearch != rsdpSig)
	{
		++acpiSearch;

		if(acpiSearch >= (uint64_t*)0xFFFFF)
			break;
	}

	screen::write("\nacpi rsdp table: ");
	screen::writePtr(acpiSearch);
	screen::write(" data: ");
	screen::write(((char*)acpiSearch));
	screen::write("\nacpi rsdp sig: ");

	auto rsdpDescriptor = (RSDPDescriptor*)acpiSearch;
	checksumACPIStructure(rsdpDescriptor, sizeof(RSDPDescriptor));

	screen::write("\nversion: ");
	screen::writeInt(rsdpDescriptor->Revision);
	screen::write("\nXSDT: ");
	screen::writePtr((void*)rsdpDescriptor->XsdtAddress);
	screen::write("\nRSDT: ");
	screen::writePtr((void*)(uint64_t)rsdpDescriptor->RsdtAddress);

	if(rsdpDescriptor->XsdtAddress != 0)
	{
		//not yet implemented
	}
	else if(rsdpDescriptor->RsdtAddress != 0)
	{
		const auto mappedAddress = rsdpDescriptor->RsdtAddress & ~(paging::pageSize * 512 - 1);
		const char* tempMap = (char*)0xFFFFFFFF00000000;
		uint64_t offset = (uint64_t)(tempMap - mappedAddress);

		paging::mapRange(mappedAddress,
						tempMap,
						0x2000000, 0); // hugepage, read only

		screen::write("\nRsdtAddress: ");
		screen::writePtr((void*)(uint64_t)rsdpDescriptor->RsdtAddress);
		screen::write(" mappedAddress: ");
		screen::writePtr((void*)(uint64_t)mappedAddress);
		screen::write(" offset: ");
		screen::writePtr((void*)(uint64_t)offset);

		auto rsdt = (RSDT*)(rsdpDescriptor->RsdtAddress + offset);
		auto numTables = (rsdt->header.Length - sizeof(ACPISDTHeader)) / sizeof(uint32_t);

		screen::write("\nRSDT Revision: ");
		screen::writeInt(rsdt->header.Revision);
		screen::write(" length: ");
		screen::writeInt(rsdt->header.Length);
		screen::write(" numTables: ");
		screen::writeInt(numTables);

		checksumACPIStructure(rsdt, rsdt->header.Length);
		uint32_t* adresses = (uint32_t*)&rsdt->otherSDT;
		for(uint32_t i = 0; i < numTables; ++i)
		{
			readACPITable((void*)(uint64_t)adresses[i], offset);
		}
	}
	else
	{
		screen::write("\nNEITHER RSDT NOR XSDT FOUND!");
		while(true);
	}

}
