/**
 * @file    radio.h
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @ingroup ORESAT
 * @{
 */
#ifndef _RADIO_H_
#define _RADIO_H_

#include "ax5043.h"
#include "si41xx.h"
#include "pdu.h"

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings.                                                */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Enable SDLS for USLP
 */
#if !defined(USLP_USE_SDLS) || defined(__DOXYGEN__)
#define USLP_USE_SDLS                       TRUE
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

typedef struct {
    SI41XXDriver            *devp;
    SI41XXConfig            *cfgp;
    const char              *name;
} synth_dev_t;

typedef struct {
    AX5043Driver            *devp;
    const AX5043Config      *cfgp;
    const char              *name;
} radio_dev_t;

typedef struct {
    const ax5043_profile_t  *profile;
    const char              *name;
} radio_profile_t;

/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* _RADIO_H_ */

/** @} */
