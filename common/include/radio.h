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

/**
 * @brief   PDU FIFO Object count
 */
#if !defined(RADIO_PDU_SIZE) || defined(__DOXYGEN__)
#define RADIO_PDU_COUNT                   8U
#endif

/**
 * @brief   PDU FIFO Object maximum size
 */
#if !defined(RADIO_PDU_SIZE) || defined(__DOXYGEN__)
#define RADIO_PDU_SIZE                    512U
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void radio_init(void);
void radio_start(void);

void uhf_send(const void *pdu, size_t len, const void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _RADIO_H_ */

/** @} */
