#include "screen/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "include/acpi.h"

typedef UINT32 ACPI_STATUS;
typedef UINT64 ACPI_PHYSICAL_ADDRESS;

/*
 * OSL Initialization and shutdown primitives
 */

ACPI_STATUS AcpiOsInitialize()
{
	screen::write("\n AcpiOsInitialize");
	return 0;
}

ACPI_STATUS AcpiOsTerminate()
{
	screen::write("\n AcpiOsTerminate");
	return 0;
}

/*
 * ACPI Table interfaces
 */

ACPI_PHYSICAL_ADDRESS AcpiOsGetRootPointer()
{
	screen::write("\n AcpiOsGetRootPointer");
	ACPI_PHYSICAL_ADDRESS  Ret;
	Ret = 0;
	AcpiFindRootPointer(&Ret);
	return Ret;
}

ACPI_STATUS AcpiOsPredefinedOverride(
    const ACPI_PREDEFINED_NAMES *InitVal,
    ACPI_STRING                 *NewVal)
{
	screen::write("\n AcpiOsPredefinedOverride");
	return 0;
}

ACPI_STATUS AcpiOsTableOverride(
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_TABLE_HEADER       **NewTable)
{
	screen::write("\n AcpiOsTableOverride");
	return 0;
}

ACPI_STATUS AcpiOsPhysicalTableOverride(
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_PHYSICAL_ADDRESS   *NewAddress,
    UINT32                  *NewTableLength)
{
	screen::write("\n AcpiOsPhysicalTableOverride");
	return 0;
}

/*
 * Spinlock primitives
 */

ACPI_STATUS AcpiOsCreateLock(
    ACPI_SPINLOCK           *OutHandle)
{
	screen::write("\n AcpiOsCreateLock");
	return 0;
}

void AcpiOsDeleteLock (
    ACPI_SPINLOCK           Handle)
{
	screen::write("\n AcpiOsDeleteLock");
}

ACPI_CPU_FLAGS AcpiOsAcquireLock (
    ACPI_SPINLOCK           Handle)
{
	screen::write("\n AcpiOsAcquireLock");
	return 0;
}

void AcpiOsReleaseLock (
    ACPI_SPINLOCK           Handle,
    ACPI_CPU_FLAGS          Flags)
{
	screen::write("\n AcpiOsReleaseLock");
}

/*
 * Semaphore primitives
 */

ACPI_STATUS AcpiOsCreateSemaphore (
    UINT32                  MaxUnits,
    UINT32                  InitialUnits,
    ACPI_SEMAPHORE          *OutHandle)
{
	screen::write("\n AcpiOsCreateSemaphore");
	return 0;
}

ACPI_STATUS AcpiOsDeleteSemaphore (
    ACPI_SEMAPHORE          Handle)
{
	screen::write("\n AcpiOsDeleteSemaphore");
	return 0;
}

ACPI_STATUS AcpiOsWaitSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units,
    UINT16                  Timeout)
{
	screen::write("\n AcpiOsWaitSemaphore");
	return 0;
}

ACPI_STATUS AcpiOsSignalSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units)
{
	screen::write("\n AcpiOsSignalSemaphore");
	return 0;
}

/*
 * Mutex primitives. May be configured to use semaphores instead via
 * ACPI_MUTEX_TYPE (see platform/acenv.h)
 */
#if (ACPI_MUTEX_TYPE != ACPI_BINARY_SEMAPHORE)

ACPI_STATUS AcpiOsCreateMutex (
    ACPI_MUTEX              *OutHandle)
{
	screen::write("\n AcpiOsCreateMutex");
	return 0;
}

void AcpiOsDeleteMutex (
    ACPI_MUTEX              Handle)
{
	screen::write("\n AcpiOsDeleteMutex");
}

ACPI_STATUS AcpiOsAcquireMutex (
    ACPI_MUTEX              Handle,
    UINT16                  Timeout)
{
	screen::write("\n AcpiOsAcquireMutex");
	return 0;
}

void AcpiOsReleaseMutex (
    ACPI_MUTEX              Handle)
{
	screen::write("\n AcpiOsReleaseMutex");
}

#endif /* (ACPI_MUTEX_TYPE != ACPI_BINARY_SEMAPHORE) */


/*
 * Memory allocation and mapping
 */

void* AcpiOsAllocate (
    ACPI_SIZE               Size)
{
	screen::write("\n AcpiOsAllocate");
	return 0;
}

void* AcpiOsAllocateZeroed (
    ACPI_SIZE               Size)
{
	screen::write("\n AcpiOsAllocateZeroed");
	return 0;
}

void AcpiOsFree (
    void *                  Memory)
{
	screen::write("\n AcpiOsFree");
}

void* AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length)
{
	screen::write("\n AcpiOsMapMemory");
	return 0;
}

void AcpiOsUnmapMemory (
    void                    *LogicalAddress,
    ACPI_SIZE               Size)
{
	screen::write("\n AcpiOsUnmapMemory");
}

ACPI_STATUS AcpiOsGetPhysicalAddress (
    void                    *LogicalAddress,
    ACPI_PHYSICAL_ADDRESS   *PhysicalAddress)
{
	screen::write("\n AcpiOsGetPhysicalAddress");
	return 0;
}

/*
 * Memory/Object Cache
 */

ACPI_STATUS AcpiOsCreateCache (
    char                    *CacheName,
    UINT16                  ObjectSize,
    UINT16                  MaxDepth,
    ACPI_CACHE_T            **ReturnCache)
{
	screen::write("\n AcpiOsCreateCache");
	return 0;
}

ACPI_STATUS AcpiOsDeleteCache (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsDeleteCache");
	return 0;
}

ACPI_STATUS AcpiOsPurgeCache (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsPurgeCache");
	return 0;
}

void* AcpiOsAcquireObject (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsAcquireObject");
	return 0;
}

ACPI_STATUS AcpiOsReleaseObject (
    ACPI_CACHE_T            *Cache,
    void                    *Object)
{
	screen::write("\n AcpiOsReleaseObject");
	return 0;
}

/*
 * Interrupt handlers
 */

ACPI_STATUS AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context)
{
	screen::write("\n AcpiOsInstallInterruptHandler");
	return 0;
}

ACPI_STATUS AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine)
{
	screen::write("\n AcpiOsRemoveInterruptHandler");
	return 0;
}

/*
 * Threads and Scheduling
 */

ACPI_THREAD_ID AcpiOsGetThreadId (
    void)
{
	screen::write("\n AcpiOsRemoveInterruptHandler");
	return 0;
}

ACPI_STATUS AcpiOsExecute (
    ACPI_EXECUTE_TYPE       Type,
    ACPI_OSD_EXEC_CALLBACK  Function,
    void                    *Context)
{
	screen::write("\n AcpiOsExecute");
	return 0;
}

void AcpiOsWaitEventsComplete (
    void)
{
	screen::write("\n AcpiOsWaitEventsComplete");
}

void AcpiOsSleep (
    UINT64                  Milliseconds)
{
	screen::write("\n AcpiOsSleep");
}

void AcpiOsStall (
    UINT32                  Microseconds)
{
	screen::write("\n AcpiOsStall");
}

/*
 * Platform and hardware-independent I/O interfaces
 */

ACPI_STATUS AcpiOsReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsReadPort");
	return 0;
}

ACPI_STATUS AcpiOsWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWritePort");
	return 0;
}

/*
 * Platform and hardware-independent physical memory interfaces
 */

ACPI_STATUS AcpiOsReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsReadMemory");
	return 0;
}

ACPI_STATUS AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWriteMemory");
	return 0;
}

/*
 * Platform and hardware-independent PCI configuration space access
 * Note: Can't use "Register" as a parameter, changed to "Reg" --
 * certain compilers complain.
 */

ACPI_STATUS AcpiOsReadPciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  *Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsReadPciConfiguration");
	return 0;
}

ACPI_STATUS AcpiOsWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWritePciConfiguration");
	return 0;
}

/*
 * Miscellaneous
 */
/*
BOOLEAN AcpiOsReadable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{
	screen::write("\n AcpiOsReadable");
	return 0;
}

BOOLEAN AcpiOsWritable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{
	screen::write("\n AcpiOsWritable");
	return 0;
}
*/
UINT64 AcpiOsGetTimer (
    void)
{
	screen::write("\n AcpiOsGetTimer");
	return 0;
}

ACPI_STATUS AcpiOsSignal (
    UINT32                  Function,
    void                    *Info)
{
	screen::write("\n AcpiOsSignal");
	return 0;
}

ACPI_STATUS AcpiOsEnterSleep (
    UINT8                   SleepState,
    UINT32                  RegaValue,
    UINT32                  RegbValue)
{
	screen::write("\n AcpiOsEnterSleep");
	return 0;
}

/*
 * Debug print routines
 */

void ACPI_INTERNAL_VAR_XFACE AcpiOsPrintf (
    const char              *Format,
    ...)
{
	screen::write("\n AcpiOsPrintf");
}

void AcpiOsVprintf (
    const char              *Format,
    va_list                 Args)
{
	screen::write("\n AcpiOsVprintf");
}

void AcpiOsRedirectOutput (
    void                    *Destination)
{
	screen::write("\n AcpiOsRedirectOutput");
}

/*
 * Debug IO
 * /

ACPI_STATUS AcpiOsGetLine (
    char                    *Buffer,
    UINT32                  BufferLength,
    UINT32                  *BytesRead)
{
	screen::write("\n AcpiOsGetLine");
	return 0;
}

ACPI_STATUS AcpiOsInitializeDebugger (
    void)
{
	screen::write("\n AcpiOsInitializeDebugger");
	return 0;
}

void AcpiOsTerminateDebugger (
    void)
{
	screen::write("\n AcpiOsTerminateDebugger");
	return 0;
}

ACPI_STATUS AcpiOsWaitCommandReady (
    void)
{
	screen::write("\n AcpiOsWaitCommandReady");
	return 0;
}

ACPI_STATUS AcpiOsNotifyCommandComplete (
    void)
{
	screen::write("\n AcpiOsNotifyCommandComplete");
	return 0;
}

void AcpiOsTracePoint (
    ACPI_TRACE_EVENT_TYPE   Type,
    BOOLEAN                 Begin,
    UINT8                   *Aml,
    char                    *Pathname)
{
}
*/
/*
 * Obtain ACPI table(s)
 * /

ACPI_STATUS AcpiOsGetTableByName (
    char                    *Signature,
    UINT32                  Instance,
    ACPI_TABLE_HEADER       **Table,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
	screen::write("\n AcpiOsGetTableByName");
	return 0;
}

ACPI_STATUS AcpiOsGetTableByIndex (
    UINT32                  Index,
    ACPI_TABLE_HEADER       **Table,
    UINT32                  *Instance,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
	screen::write("\n AcpiOsGetTableByIndex");
	return 0;
}

ACPI_STATUS AcpiOsGetTableByAddress (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       **Table)
{
	screen::write("\n AcpiOsGetTableByAddress");
	return 0;
}
*/
/*
 * Directory manipulation
 * /

void* AcpiOsOpenDirectory (
    char                    *Pathname,
    char                    *WildcardSpec,
    char                    RequestedFileType)
{
}
*/
/* RequesteFileType values * /

#define REQUEST_FILE_ONLY                   0
#define REQUEST_DIR_ONLY                    1

char* AcpiOsGetNextFilename (
    void                    *DirHandle)
{
}

void AcpiOsCloseDirectory (
    void                    *DirHandle)
{
}
*/

#ifdef __cplusplus
}
#endif
