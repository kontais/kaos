#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    char __wchb[4];
  } __value;            /* Value so far.  */
} mbstate_t;

wchar_t* wcschr (const wchar_t* ws, wchar_t wc);
wchar_t* wcspbrk (const wchar_t* wcs1, const wchar_t* wcs2);
wchar_t* wcsrchr (const wchar_t* ws, wchar_t wc);
wchar_t* wcsstr (const wchar_t* wcs1, const wchar_t* wcs2);
wchar_t* wmemchr (const wchar_t* ptr, wchar_t wc, size_t num);


#ifdef __cplusplus
}
#endif
