#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef float float_t;
typedef double double_t;

enum
  {
    FP_NAN =
# define FP_NAN 0
      FP_NAN,
    FP_INFINITE =
# define FP_INFINITE 1
      FP_INFINITE,
    FP_ZERO =
# define FP_ZERO 2
      FP_ZERO,
    FP_SUBNORMAL =
# define FP_SUBNORMAL 3
      FP_SUBNORMAL,
    FP_NORMAL =
# define FP_NORMAL 4
      FP_NORMAL
  };
  
#  define signbit(x) \
     (sizeof (x) == sizeof (float)                                            \
      ? __builtin_signbitf (x)                                                        \
      : sizeof (x) == sizeof (double)                                         \
      ? __builtin_signbit (x) : __builtin_signbitl (x))

#  define isfinite(x) __builtin_isfinite (x)
#  define isinf(x) __builtin_isinf_sign (x)
#  define isnan(x) __builtin_isnan (x)
#  define isnormal(x) __builtin_isnormal (x)
# define isgreater(x, y)        __builtin_isgreater(x, y)
# define isgreaterequal(x, y)   __builtin_isgreaterequal(x, y)
# define isless(x, y)           __builtin_isless(x, y)
# define islessequal(x, y)      __builtin_islessequal(x, y)
# define islessgreater(x, y)    __builtin_islessgreater(x, y)
# define isunordered(u, v)      __builtin_isunordered(u, v)
#  define fpclassify(x) __builtin_fpclassify (FP_NAN, FP_INFINITE,            \
     FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)

double fabs  (double x);
float fabsf (float x);
long double fabsl (long double x);

double ceil  (double x);
float ceilf (float x);
long double ceill (long double x);

double floor  (double x);
float floorf (float x);
long double floorl (long double x);

double modf  (double x     , double* intpart);
float modff (float x      , float* intpart);
long double modfl (long double x, long double* intpart);

double fmod  (double numer     , double denom);
float fmodf (float numer      , float denom);
long double fmodl (long double numer, long double denom);

double exp  (double x);
float expf (float x);
long double expl (long double x);

     double frexp  (double x     , int* exp);
      float frexpf (float x      , int* exp);
long double frexpl (long double x, int* exp);

     double ldexp  (double x     , int exp);
      float ldexpf (float x      , int exp);
long double ldexpl (long double x, int exp);

double log  (     double x);
float logf (      float x);
long double logl (long double x);

double log10  (double x);
float log10f (float x);
long double log10l (long double x);

double pow  (double base     , double exponent);
float powf (float base      , float exponent);
long double powl (long double base, long double exponent);

double sqrt  (double x);
float sqrtf (float x);
long double sqrtl (long double x);




double sin  (double x);
float sinf (float x);
long double sinl (long double x);

double asin  (double x);
float asinf (float x);
long double asinl (long double x);

double cos  (double x);
float cosf (float x);
long double cosl (long double x);

double acos  (double x);
float acosf (float x);
long double acosl (long double x);

double tan  (double x);
float tanf (float x);
long double tanl (long double x);

double atan  (double x);
float atanf (float x);
long double atanl (long double x);

double atan2  (double y     , double x);
float atan2f (float y      , float x);
long double atan2l (long double y, long double x);

double sinh  (double x);
float sinhf (float x);
long double sinhl (long double x);

     double asinh  (double x);
      float asinhf (float x);
long double asinhl (long double x);

double cosh  (double x);
float coshf (float x);
long double coshl (long double x);

     double acosh  (double x);
      float acoshf (float x);
long double acoshl (long double x);

double tanh  (double x);
float tanhf (float x);
long double tanhl (long double x);

     double atanh  (double x);
      float atanhf (float x);
long double atanhl (long double x);


     double cbrt  (double x);
      float cbrtf (float x);
long double cbrtl (long double x);

     double copysign  (double x     , double y);
      float copysignf (float x      , float y);
long double copysignl (long double x, long double y);

     double erf  (double x);
      float erff (float x);
long double erfl (long double x);

     double erfc  (double x);
      float erfcf (float x);
long double erfcl (long double x);

     double exp2  (double x);
      float exp2f (float x);
long double exp2l (long double x);

     double expm1  (double x);
      float expm1f (float x);
long double expm1l (long double x);

     double fdim  (double x     , double y);
      float fdimf (float x      , float y);
long double fdiml (long double x, long double y);

     double fma  (double x     , double y     , double z);
      float fmaf (float x      , float y      , float z);
long double fmal (long double x, long double y, long double z);

     double fmax  (double x     , double y);
      float fmaxf (float x      , float y);
long double fmaxl (long double x, long double y);

     double fmin  (double x     , double y);
      float fminf (float x      , float y);
long double fminl (long double x, long double y);

     double hypot  (double x     , double y);
      float hypotf (float x      , float y);
long double hypotl (long double x, long double y);

int ilogb  (double x);
int ilogbf (float x);
int ilogbl (long double x);

     double lgamma  (double x);
      float lgammaf (float x);
long double lgammal (long double x);

long long int llrint  (double x);
long long int llrintf (float x);
long long int llrintl (long double x);

long long int llround  (double x);
long long int llroundf (float x);
long long int llroundl (long double x);

     double log1p  (double x);
      float log1pf (float x);
long double log1pl (long double x);

     double log2  (double x);
      float log2f (float x);
long double log2l (long double x);

     double logb  (double x);
      float logbf (float x);
long double logbl (long double x);

long int lrint  (double x);
long int lrintf (float x);
long int lrintl (long double x);

long int lround  (double x);
long int lroundf (float x);
long int lroundl (long double x);

     double nearbyint  (double x);
      float nearbyintf (float x);
long double nearbyintl (long double x);

     double nextafter  (double x     , double y);
      float nextafterf (float x      , float y);
long double nextafterl (long double x, long double y);

     double nexttoward  (double x     , long double y);
      float nexttowardf (float x      , long double y);
long double nexttowardl (long double x, long double y);

     double remainder  (double numer     , double denom);
      float remainderf (float numer      , float denom);
long double remainderl (long double numer, long double denom);

     double remquo  (double numer     , double denom     , int* quot);
      float remquof (float numer      , float denom      , int* quot);
long double remquol (long double numer, long double denom, int* quot);

     double rint  (double x);
      float rintf (float x);
long double rintl (long double x);

     double round  (double x);
      float roundf (float x);
long double roundl (long double x);

     double scalbln  (double x     , long int n);
      float scalblnf (float x      , long int n);
long double scalblnl (long double x, long int n);

     double scalbn  (double x     , int n);
      float scalbnf (float x      , int n);
long double scalbnl (long double x, int n);

     double tgamma  (     double x);
      float tgammaf (      float x);
long double tgammal (long double x);

     double trunc  (     double x);
      float truncf (      float x);
long double truncl (long double x);

double nan (const char* tagp);
float nanf (const char* tagp);
float nanl (const char* tagp);





#ifdef __cplusplus
}
#endif
