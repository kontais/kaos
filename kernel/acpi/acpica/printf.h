#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(const char *fmt, ...);
void tfp_sprintf(char* s,const char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),const char *fmt, va_list va);

#define printf tfp_printf 
#define sprintf tfp_sprintf 


#ifdef __cplusplus
}
#endif

#endif
