/*! \file util_general.h
  * \defgroup util_general General Utility Functions
  * @{
  */
#ifndef UTIL_GENERAL_H_
#define UTIL_GENERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define                 UNUSED          __attribute__((unused))
#define                 NORETURN        __attribute__((noreturn))
#define                 NELEMS(x)       (sizeof(x) / sizeof(x[0]))

#define _STRINGIFY(line) #line
#define STRINGIFY(line) _STRINGIFY(line)
#define DBG_PREFIX __FILE__  ":" STRINGIFY(__LINE__) ", "

#define max(a,b) \
        ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
        _a > _b ? _a : _b; })

typedef enum gen_status
{
    GEN_OK = 0,
    GEN_NOMINAL,
    GEN_ERROR
} Gen_status;

typedef struct util_status
{
    Gen_status     status;
} Util_status;

#ifdef __cplusplus
}
#endif



#endif


//! @}

