#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void FILE;
typedef __builtin_va_list va_list;
typedef long fpos_t;

#define NULL nullptr
#define EOF -1

int fclose ( FILE * stream );
FILE * fopen ( const char * filename, const char * mode );
int fflush ( FILE * stream );

void setbuf ( FILE * stream, char * buffer );
int setvbuf ( FILE * stream, char * buffer, int mode, size_t size );
int fprintf ( FILE * stream, const char * format, ... );
int fscanf ( FILE * stream, const char * format, ... );
int vsprintf (char * s, const char * format, va_list arg );
char * fgets ( char * str, int num, FILE * stream );
int fputs ( const char * str, FILE * stream );
int fputc ( int character, FILE * stream );
int snprintf ( char * s, size_t n, const char * format, ... );
int sprintf ( char * str, const char * format, ... );
int sscanf ( const char * s, const char * format, ...);
int vfprintf ( FILE * stream, const char * format, va_list arg );
int vfscanf ( FILE * stream, const char * format, va_list arg );
int vsscanf ( const char * s, const char * format, va_list arg );
int vsnprintf (char * s, size_t n, const char * format, va_list arg );
int fgetc ( FILE * stream );
int getc ( FILE * stream );
int putc ( int character, FILE * stream );
int ungetc ( int character, FILE * stream );
size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
int fgetpos ( FILE * stream, fpos_t * pos );
int fseek ( FILE * stream, long int offset, int origin );
int fsetpos ( FILE * stream, const fpos_t * pos );
long int ftell ( FILE * stream );
void rewind ( FILE * stream );
void clearerr ( FILE * stream );
int feof ( FILE * stream );
int ferror ( FILE * stream );
void perror ( const char * str );
FILE * freopen ( const char * filename, const char * mode, FILE * stream );
int remove ( const char * filename );
int rename ( const char * oldname, const char * newname );
FILE * tmpfile ( void );
char * tmpnam ( char * str );
int getchar ( void );
int scanf ( const char * format, ... );
int vscanf ( const char * format, va_list arg );
int printf ( const char * format, ... );
int putchar ( int character );
int puts ( const char * str );
int vprintf ( const char * format, va_list arg );


#ifdef __cplusplus
}
#endif
