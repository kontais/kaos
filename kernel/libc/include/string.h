#pragma once


#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

//libcxx stubs
char* strchr(const char* __s, int __c);
char* strpbrk(const char* __s1, const char* __s2);
char* strrchr(const char* __s, int __c);
void* memchr(const void* __s, int __c, size_t __n);
char* strstr(const char* __s1, const char* __s2);

#ifdef __cplusplus
}
#endif
