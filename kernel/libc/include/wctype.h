#pragma once

#include "stdint.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int wctrans_t;
typedef int wctype_t;

int iswalnum (wint_t c);
int iswalpha (wint_t c);
int iswblank (wint_t c);
int iswcntrl (wint_t c);
int iswdigit (wint_t c);
int iswgraph (wint_t c);
int iswlower (wint_t c);
int iswprint (wint_t c);
int iswpunct (wint_t c);
int iswspace (wint_t c);
int iswupper (wint_t c);
int iswxdigit (wint_t c);
wint_t towlower (wint_t c);
wint_t towupper (wint_t c);

int iswctype(wint_t c, wctype_t desc);
wctype_t wctype (const char* property);
wint_t towctrans(wint_t c, wctrans_t desc);
wctrans_t wctrans (const char* property);

int fwprintf (FILE* stream, const wchar_t* format, ...);
int fwscanf (FILE* stream, const wchar_t* format, ...);
int swprintf (wchar_t* ws, size_t len, const wchar_t* format, ...);
int vfwprintf (FILE* stream, const wchar_t* format, va_list arg);
int vswprintf (wchar_t * ws, size_t len, const wchar_t * format, va_list arg );
int swscanf (const wchar_t* ws, const wchar_t* format, ...);
int vfwscanf (FILE* stream, const wchar_t* format, va_list arg);
int vswscanf (const wchar_t* ws, const wchar_t* format, va_list arg);
wint_t fgetwc (FILE * stream);
wchar_t* fgetws (wchar_t* ws, int num, FILE* stream);
wint_t fputwc (wchar_t wc, FILE * stream);
int fputws (const wchar_t* ws, FILE* stream);
int fwide (FILE* stream, int mode);
wint_t getwc (FILE* stream);
wint_t putwc (wchar_t wc, FILE* stream);
wint_t ungetwc (wint_t wc, FILE* stream);

double wcstod (const wchar_t* str, wchar_t** endptr);
float wcstof (const wchar_t* str, wchar_t** endptr);
long double wcstold (const wchar_t* str, wchar_t** endptr);
long int wcstol (const wchar_t* str, wchar_t** endptr, int base);
long long int wcstoll (const wchar_t* str, wchar_t** endptr, int base);
unsigned long int wcstoul (const wchar_t* str, wchar_t** endptr, int base);
unsigned long long int wcstoull (const wchar_t* str, wchar_t** endptr, int base);
wchar_t* wcscpy (wchar_t* destination, const wchar_t* source);
wchar_t* wcsncpy (wchar_t* destination, const wchar_t* source, size_t num);
wchar_t* wcscat (wchar_t* destination, const wchar_t* source);
wchar_t* wcsncat (wchar_t* destination, const wchar_t* source, size_t num);
int wcscmp (const wchar_t* wcs1, const wchar_t* wcs2);
int wcscoll (const wchar_t* wcs1, const wchar_t* wcs2);
int wcsncmp (const wchar_t* wcs1, const wchar_t* wcs2, size_t num);
size_t wcsxfrm (wchar_t* destination, const wchar_t* source, size_t num);
size_t wcscspn (const wchar_t* wcs1, const wchar_t* wcs2);
size_t wcslen (const wchar_t* wcs);
size_t wcsspn (const wchar_t* wcs1, const wchar_t* wcs2);
wchar_t* wcstok (wchar_t* wcs, const wchar_t* delimiters);
int wmemcmp (const wchar_t* ptr1, const wchar_t* ptr2, size_t num);
size_t wcsftime (wchar_t* ptr, size_t maxsize, const wchar_t* format,
                 const struct tm* timeptr);
wint_t btowc (int c);
int wctob (wint_t wc);
int mbsinit (const mbstate_t* ps);
size_t mbrlen (const char* pmb, size_t max, mbstate_t* ps);
size_t mbrtowc (wchar_t* pwc, const char* pmb, size_t max, mbstate_t* ps);
size_t wcrtomb (char* pmb, wchar_t wc, mbstate_t* ps);
size_t mbsrtowcs (wchar_t* dest, const char** src, size_t max, mbstate_t* ps);
size_t wcsrtombs (char* dest, const wchar_t** src, size_t max, mbstate_t* ps);
wint_t getwchar (void);
int vwscanf ( const wchar_t * format, va_list arg );
int wscanf (const wchar_t* format, ...);
wint_t putwchar (wchar_t wc);
int vwprintf (const wchar_t* format, va_list arg);
int wprintf (const wchar_t* format, ...);



#ifdef __cplusplus
}
#endif
