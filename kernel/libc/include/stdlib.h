#pragma once

#include "stdint.h"

#ifdef __cplusplus
#define NORETURN [[noreturn]]
extern "C" {
#else
#define NORETURN
#endif

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long int quot;
  long int rem;
} ldiv_t;

typedef struct {
  long long quot;
  long long rem;
} lldiv_t;


void* malloc (size_t size);
void* calloc (size_t num, size_t size);
void* realloc (void* ptr, size_t size);
void free (void* ptr);
int posix_memalign(void **memptr, size_t alignment, size_t size);



int rand (void);
void srand (unsigned int seed);

int atexit (void (*func)(void));
NORETURN
void exit (int status);
NORETURN
void _Exit (int status);
NORETURN
void abort();

char* getenv (const char* name);
int system (const char* command);
void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*));
void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));
int mblen (const char* pmb, size_t max);
int mbtowc (wchar_t* pwc, const char* pmb, size_t max);
int wctomb (char* pmb, wchar_t wc);
size_t mbstowcs (wchar_t* dest, const char* src, size_t max);
size_t wcstombs (char* dest, const wchar_t* src, size_t max);


int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

ldiv_t ldiv(     long __x,      long __y);
lldiv_t lldiv(long long __x, long long __y);

double atof (const char* str);
int atoi (const char * str);
long int atol ( const char * str );
long long int atoll ( const char * str );

double strtod (const char* str, char** endptr);
float strtof (const char* str, char** endptr);
long double strtold (const char* str, char** endptr);
long int strtol (const char* str, char** endptr, int base);
long long int strtoll (const char* str, char** endptr, int base);
unsigned long int strtoul (const char* str, char** endptr, int base);
unsigned long long int strtoull (const char* str, char** endptr, int base);

#ifdef __cplusplus
}
#endif
