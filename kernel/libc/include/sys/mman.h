#pragma once

#include <stddef.h>
#include <sys/types.h>

#define PROT_READ           0x01
#define PROT_WRITE          0x02
#define MAP_PRIVATE         0x02
#define MAP_ANONYMOUS       0x20


#ifdef __cplusplus
extern "C" {
#endif

void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
int munmap(void *addr, size_t length);

#ifdef __cplusplus
}
#endif
