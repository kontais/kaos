#pragma once


#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void * memmove ( void * destination, const void * source, size_t num );
int memcmp ( const void * ptr1, const void * ptr2, size_t num );

//libcxx stubs
char* strchr(const char* __s, int __c);
char* strpbrk(const char* __s1, const char* __s2);
char* strrchr(const char* __s, int __c);
void* memchr(const void* __s, int __c, size_t __n);
char* strstr(const char* __s1, const char* __s2);

size_t strxfrm ( char * destination, const char * source, size_t num );
size_t strcspn ( const char * str1, const char * str2 );
char * strcpy ( char * destination, const char * source );
char * strncpy ( char * destination, const char * source, size_t num );
char * strcat ( char * destination, const char * source );
char * strncat ( char * destination, const char * source, size_t num );
int strcmp ( const char * str1, const char * str2 );
int strncmp ( const char * str1, const char * str2, size_t num );
int strcoll ( const char * str1, const char * str2 );
size_t strspn ( const char * str1, const char * str2 );
char * strtok ( char * str, const char * delimiters );
char * strerror ( int errnum );
size_t strlen ( const char * str );

#ifdef __cplusplus
}
#endif
