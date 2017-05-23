#include "acpi.h"
#include "structures.h"
#include <screen/screen.h>
#include <mm/paging.h>

#include "acpica/include/acpi.h"


void acpi::init()
{
	//auto status = AcpiInitializeTables (TableArray, ACPI_MAX_INIT_TABLES, TRUE);
	auto Status = AcpiInitializeSubsystem ();
	screen::write("\nAcpiInitializeSubsystem() --> ");
	screen::writeInt(Status);

	Status = AcpiInitializeTables (nullptr, 16, FALSE);
	screen::write("\nAcpiInitializeTables() --> ");
	screen::writeInt(Status);

	Status = AcpiLoadTables ();
	screen::write("\nAcpiLoadTables() --> ");
	screen::writeInt(Status);

	Status = AcpiEnableSubsystem (ACPI_FULL_INITIALIZATION);
	screen::write("\nAcpiEnableSubsystem() --> ");
	screen::writeInt(Status);

	Status = AcpiInitializeObjects (ACPI_FULL_INITIALIZATION);
	screen::write("\nAcpiInitializeObjects() --> ");
	screen::writeInt(Status);
}

void acpi::halt()
{
	AcpiEnterSleepStatePrep(5);
	AcpiEnterSleepState(5);
}
