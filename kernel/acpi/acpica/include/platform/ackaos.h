#ifndef __ACKAOS_H__
#define __ACKAOS_H__

#include "acgcc.h"
#include <stdarg.h>

//#define ACPI_USE_SYSTEM_CLIBRARY
//#define ACPI_USE_DO_WHILE_0


//#define ACPI_USE_SYSTEM_INTTYPES

//#define ACPI_INIT_FUNCTION __init

/* Host-dependent types and defines for in-kernel ACPICA */

#define ACPI_MACHINE_WIDTH          64
//#define ACPI_EXPORT_SYMBOL(symbol)  EXPORT_SYMBOL(symbol);
//#define strtoul                     simple_strtoul

//#define ACPI_CACHE_T                struct kmem_cache
//#define ACPI_SPINLOCK               spinlock_t *
#define ACPI_CPU_FLAGS              unsigned long

/* Use native linux version of AcpiOsAllocateZeroed */

#define USE_NATIVE_ALLOCATE_ZEROED 1
#define ACPI_CACHE_T                ACPI_MEMORY_LIST
#define ACPI_USE_LOCAL_CACHE        1

/*#define ACPI_MSG_ERROR          KERN_ERR "ACPI Error: "
#define ACPI_MSG_EXCEPTION      KERN_ERR "ACPI Exception: "
#define ACPI_MSG_WARNING        KERN_WARNING "ACPI Warning: "
#define ACPI_MSG_INFO           KERN_INFO "ACPI: "

#define ACPI_MSG_BIOS_ERROR     KERN_ERR "ACPI BIOS Error (bug): "
#define ACPI_MSG_BIOS_WARNING   KERN_WARNING "ACPI BIOS Warning (bug): "
*/


//#define memcmp Acpi_memcmp
#define memcpy Acpi_memcpy
#define memset Acpi_memset

typedef __builtin_va_list va_list;


#endif /* __ACKAOS_H__ */
