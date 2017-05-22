#include "screen/screen.h"
#include "mm/paging.h"
#include "printf.h"

#include "include/acpi.h"
#undef memset

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef UINT32 ACPI_STATUS;
typedef UINT64 ACPI_PHYSICAL_ADDRESS;

void putp(void*, char c)
{
    screen::putChar(c);
}

/*
 * OSL Initialization and shutdown primitives
 */

ACPI_STATUS AcpiOsInitialize()
{
	screen::write("\n AcpiOsInitialize");

    init_printf(nullptr, putp);
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsTerminate()
{
	screen::write("\n AcpiOsTerminate");
    // TODO
	return AE_OK;
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

	screen::write("\n AcpiOsGetRootPointer RESULT: ");
    screen::writePtr((void*)Ret);
	
    return Ret;
}

ACPI_STATUS AcpiOsPredefinedOverride(
    const ACPI_PREDEFINED_NAMES *InitVal,
    ACPI_STRING                 *NewVal)
{
	//screen::write("\n AcpiOsPredefinedOverride");
    *NewVal = nullptr;
	return AE_OK;
}

ACPI_STATUS AcpiOsTableOverride(
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_TABLE_HEADER       **NewTable)
{
	//screen::write("\n AcpiOsTableOverride");
    *NewTable = nullptr;
	return AE_OK;
}

ACPI_STATUS AcpiOsPhysicalTableOverride(
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_PHYSICAL_ADDRESS   *NewAddress,
    UINT32                  *NewTableLength)
{
	//screen::write("\n AcpiOsPhysicalTableOverride");
    *NewAddress = 0;
	return AE_OK;
}

/*
 * Spinlock primitives
 */

ACPI_STATUS AcpiOsCreateLock(
    ACPI_SPINLOCK           *OutHandle)
{
	//screen::write("\n AcpiOsCreateLock");
    // TODO
	return AE_OK;
}

void AcpiOsDeleteLock (
    ACPI_SPINLOCK           Handle)
{
	//screen::write("\n AcpiOsDeleteLock");
    // TODO
}

ACPI_CPU_FLAGS AcpiOsAcquireLock (
    ACPI_SPINLOCK           Handle)
{
	//screen::write("\n AcpiOsAcquireLock");
    // TODO
	return AE_OK;
}

void AcpiOsReleaseLock (
    ACPI_SPINLOCK           Handle,
    ACPI_CPU_FLAGS          Flags)
{
	//screen::write("\n AcpiOsReleaseLock");
    // TODO
}

/*
 * Semaphore primitives
 */

ACPI_STATUS AcpiOsCreateSemaphore (
    UINT32                  MaxUnits,
    UINT32                  InitialUnits,
    ACPI_SEMAPHORE          *OutHandle)
{
	//screen::write("\n AcpiOsCreateSemaphore");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsDeleteSemaphore (
    ACPI_SEMAPHORE          Handle)
{
	//screen::write("\n AcpiOsDeleteSemaphore");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsWaitSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units,
    UINT16                  Timeout)
{
	//screen::write("\n AcpiOsWaitSemaphore");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsSignalSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units)
{
	//screen::write("\n AcpiOsSignalSemaphore");
    // TODO
	return AE_OK;
}

/*
 * Mutex primitives. May be configured to use semaphores instead via
 * ACPI_MUTEX_TYPE (see platform/acenv.h)
 */
#if (ACPI_MUTEX_TYPE != ACPI_BINARY_SEMAPHORE)

ACPI_STATUS AcpiOsCreateMutex (
    ACPI_MUTEX              *OutHandle)
{
	//screen::write("\n AcpiOsCreateMutex");
    // TODO
	return AE_OK;
}

void AcpiOsDeleteMutex (
    ACPI_MUTEX              Handle)
{
	//screen::write("\n AcpiOsDeleteMutex");
    // TODO
}

ACPI_STATUS AcpiOsAcquireMutex (
    ACPI_MUTEX              Handle,
    UINT16                  Timeout)
{
	//screen::write("\n AcpiOsAcquireMutex");
    // TODO
	return AE_OK;
}

void AcpiOsReleaseMutex (
    ACPI_MUTEX              Handle)
{
	//screen::write("\n AcpiOsReleaseMutex");
    // TODO
}

#endif /* (ACPI_MUTEX_TYPE != ACPI_BINARY_SEMAPHORE) */


/*
 * Memory allocation and mapping
 */

void* AcpiOsAllocate (
    ACPI_SIZE               Size)
{
	//screen::write("\n AcpiOsAllocate");
    // TODO
	return malloc(Size);
}

void* AcpiOsAllocateZeroed (
    ACPI_SIZE               Size)
{
	//screen::write("\n AcpiOsAllocateZeroed");
    // TODO
	auto ret = malloc(Size);
    memset(ret, 0, Size);

    return ret;
}

void AcpiOsFree (
    void *                  Memory)
{
	//screen::write("\n AcpiOsFree");
    // TODO
    free(Memory);
}

void* AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length)
{
    const uint64_t acpiLoc = 0xFFFFFFFC00000000;

/*
	screen::write("\n AcpiOsMapMemory ");
	screen::writePtr((void*)Where);
	screen::write(", ");
	screen::writeUInt(Length);
*/

    uint64_t pageStart = Where & ~(paging::pageSizeHuge - 1);
    uint64_t offsetInPage = Where - pageStart;
    uint64_t totalLength = Length + offsetInPage;
    auto ret = (void*)(acpiLoc + offsetInPage);
/*
	screen::write("\n");
	screen::writePtr((void*)pageStart);
	screen::write(", ");
	screen::writePtr((void*)offsetInPage);
	screen::write(", ");
	screen::writeInt(totalLength);
	screen::write(", ");
	screen::writePtr(ret);
*/
    paging::mapRangeHuge(pageStart, (void*)acpiLoc, totalLength, paging::writeable | paging::executeDisable);


    // TODO
	return ret;
}

void AcpiOsUnmapMemory (
    void                    *LogicalAddress,
    ACPI_SIZE               Size)
{
	//screen::write("\n AcpiOsUnmapMemory");
    // TODO
}

ACPI_STATUS AcpiOsGetPhysicalAddress (
    void                    *LogicalAddress,
    ACPI_PHYSICAL_ADDRESS   *PhysicalAddress)
{
	screen::write("\n AcpiOsGetPhysicalAddress");
    // TODO
	return AE_OK;
}

/*
 * Memory/Object Cache
 */
/*
ACPI_STATUS AcpiOsCreateCache (
    char                    *CacheName,
    UINT16                  ObjectSize,
    UINT16                  MaxDepth,
    ACPI_CACHE_T            **ReturnCache)
{
	screen::write("\n AcpiOsCreateCache");
    // TODO
    //*ReturnCache = malloc(ObjectSize);
	return AE_OK;
}

ACPI_STATUS AcpiOsDeleteCache (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsDeleteCache");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsPurgeCache (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsPurgeCache");
    // TODO
	return AE_OK;
}

void* AcpiOsAcquireObject (
    ACPI_CACHE_T            *Cache)
{
	screen::write("\n AcpiOsAcquireObject");
    // TODO
	return 0;
}

ACPI_STATUS AcpiOsReleaseObject (
    ACPI_CACHE_T            *Cache,
    void                    *Object)
{
	screen::write("\n AcpiOsReleaseObject");
    // TODO
	return AE_OK;
}
*/
/*
 * Interrupt handlers
 */

ACPI_STATUS AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context)
{
	screen::write("\n AcpiOsInstallInterruptHandler");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine)
{
	screen::write("\n AcpiOsRemoveInterruptHandler");
    // TODO
	return AE_OK;
}

/*
 * Threads and Scheduling
 */

ACPI_THREAD_ID AcpiOsGetThreadId (
    void)
{
	//screen::write("\n AcpiOsGetThreadId");
    // TODO
	return 1;
}

ACPI_STATUS AcpiOsExecute (
    ACPI_EXECUTE_TYPE       Type,
    ACPI_OSD_EXEC_CALLBACK  Function,
    void                    *Context)
{
	screen::write("\n AcpiOsExecute");
    // TODO
	return AE_OK;
}

void AcpiOsWaitEventsComplete (
    void)
{
	screen::write("\n AcpiOsWaitEventsComplete");
    // TODO
}

void AcpiOsSleep (
    UINT64                  Milliseconds)
{
	screen::write("\n AcpiOsSleep");
    // TODO
}

void AcpiOsStall (
    UINT32                  Microseconds)
{
	//screen::write("\n AcpiOsStall");

    volatile uint64_t ss = 0;
    for(uint64_t i = 0; i < Microseconds * 1000ULL; ++i)
    {
        ss++;
    }
    // TODO
}

/*
 * Platform and hardware-independent I/O interfaces
 */
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
static inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ( "inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
static inline uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile ( "inl %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void outw(uint16_t port, uint16_t val)
{
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void outl(uint16_t port, uint32_t val)
{
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}

ACPI_STATUS AcpiOsReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsReadPort ");
	screen::writePtr((void*)Address);
	screen::write(", ");
	screen::writeInt(Width);

    switch(Width)
    {
    case 8:
        *Value = inb(Address);
        break;
    case 16:
        *Value = inw(Address);
        break;
    case 32:
        *Value = inl(Address);
        break;
    default:
        break;
    }

	screen::write(", ");
	screen::writeInt(*Value);

	return AE_OK;
}

ACPI_STATUS AcpiOsWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWritePort");
	screen::writePtr((void*)Address);
	screen::write(", ");
	screen::writeInt(Width);
	screen::write(", ");
	screen::writeInt(Value);

    switch(Width)
    {
    case 8:
        outb(Address, Value);
        break;
    case 16:
        outw(Address, Value);
        break;
    case 32:
        outl(Address, Value);
        break;
    default:
        break;
    }

	return AE_OK;
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
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWriteMemory");
    // TODO
	return AE_OK;
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
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  Value,
    UINT32                  Width)
{
	screen::write("\n AcpiOsWritePciConfiguration");
    // TODO
	return AE_OK;
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
	return AE_OK;
}

BOOLEAN AcpiOsWritable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{
	screen::write("\n AcpiOsWritable");
	return AE_OK;
}
*/
UINT64 AcpiOsGetTimer (
    void)
{
	screen::write("\n AcpiOsGetTimer");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsSignal (
    UINT32                  Function,
    void                    *Info)
{
	screen::write("\n AcpiOsSignal");
    // TODO
	return AE_OK;
}

ACPI_STATUS AcpiOsEnterSleep (
    UINT8                   SleepState,
    UINT32                  RegaValue,
    UINT32                  RegbValue)
{
	screen::write("\n AcpiOsEnterSleep");
    // TODO
	return AE_OK;
}

/*
 * Debug print routines
 */

void ACPI_INTERNAL_VAR_XFACE AcpiOsPrintf (
    const char              *Format,
    ...)
{
    va_list va;
    va_start(va,Format);
    tfp_format(nullptr,putp,Format,va);
    va_end(va);

	//screen::write("\n AcpiOsPrintf: ");
	//screen::write(Format);
    // TODO
}

void AcpiOsVprintf (
    const char              *Format,
    va_list                 Args)
{
    tfp_format(nullptr,putp,Format,Args);

	//screen::write("\n AcpiOsVprintf: ");
	//screen::write(Format);
    // TODO
}

void AcpiOsRedirectOutput (
    void                    *Destination)
{
	screen::write("\n AcpiOsRedirectOutput");
    // TODO
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
	return AE_OK;
}

ACPI_STATUS AcpiOsInitializeDebugger (
    void)
{
	screen::write("\n AcpiOsInitializeDebugger");
	return AE_OK;
}

void AcpiOsTerminateDebugger (
    void)
{
	screen::write("\n AcpiOsTerminateDebugger");
	return AE_OK;
}

ACPI_STATUS AcpiOsWaitCommandReady (
    void)
{
	screen::write("\n AcpiOsWaitCommandReady");
	return AE_OK;
}

ACPI_STATUS AcpiOsNotifyCommandComplete (
    void)
{
	screen::write("\n AcpiOsNotifyCommandComplete");
	return AE_OK;
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
	return AE_OK;
}

ACPI_STATUS AcpiOsGetTableByIndex (
    UINT32                  Index,
    ACPI_TABLE_HEADER       **Table,
    UINT32                  *Instance,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
	screen::write("\n AcpiOsGetTableByIndex");
	return AE_OK;
}

ACPI_STATUS AcpiOsGetTableByAddress (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       **Table)
{
	screen::write("\n AcpiOsGetTableByAddress");
	return AE_OK;
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
