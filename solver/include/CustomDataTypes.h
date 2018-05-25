#pragma once
#define USE_DOUBLE 0xD00B1E
#define USE_DOUBLE_T 0xD00B1E7
#define USE_FLOAT 0xF10A7
#define USE_VOIDPTR 0x701D
#define USE_MPFR 0xB00B5


#define STRINGIZE_CUSTOM_DATA_TYPE_H(X) #X

#ifndef MYDOUBLE
//-----------------------------------
#    define MYDOUBLE USE_DOUBLE
//-----------------------------------

#    define TEXT_CUSTOM_DATA_TYPE_H(D) "Impicit MYDOUBLE was set to " STRINGIZE_CUSTOM_DATA_TYPE_H(D)
#    pragma message TEXT_CUSTOM_DATA_TYPE_H(MYDOUBLE)
#    undef TEXT_CUSTOM_DATA_TYPE_H
#endif



#if MYDOUBLE == USE_MPFR
#   include <mpfr.h>
typedef mpfr_t mydouble;
#elif MYDOUBLE == USE_DOUBLE
#   include <math.h>
typedef double mydouble;
#   define my_fabs fabs // from <math.h>
#   define my_sqrt sqrt // from <math.h>
#   define my_cbrt cbrt // from <math.h>
#elif MYDOUBLE == USE_DOUBLE_T
#   include <tgmath.h>
    typedef double_t mydouble;
#   define my_fabs fabs // from <tgmath.h>
#   define my_sqrt sqrt // from <tgmath.h>
#   define my_cbrt cbrt // from <tgmath.h>
#elif MYDOUBLE == USE_FLOAT
    typedef float mydouble;
#   define my_fabs fabsf // from <tgmath.h>
#   define my_sqrtf sqrtf // from <tgmath.h>
#   define my_cbrtf cbrtf // from <tgmath.h>
#elif MYDOUBLE == USE_VOIDPTR
    typedef void * mydouble;
#else
#   error "Undefined or unknown MYDOUBLE"
#endif


#undef STRINGIZE_CUSTOM_DATA_TYPE_H
