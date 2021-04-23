/**
 * @file    cop.h
 * @brief   Communications Operation Procedures (COP) support library.
 *
 * @addtogroup CCSDS
 * @{
 */
#ifndef _COP_H_
#define _COP_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "frame_buf.h"
#include "uslp.h"

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

/**
 * @name    Communications Operation Procedure Directives
 * @{
 */
typedef enum {
    COP_DIR_INIT_NO_CLCW,
    COP_DIR_INIT_CLCW,
    COP_DIR_INIT_UNLOCK,
    COP_DIR_INIT_SET_VR,
    COP_DIR_TERMINATE,
    COP_DIR_RESUME,
    COP_DIR_SET_VS,
    COP_DIR_SET_FOP_WINDOW,
    COP_DIR_SET_T1_INITAL,
    COP_DIR_SET_TX_LIMIT,
    COP_DIR_SET_TIMEOUT
} cop_dir_t;
/** @} */

/**
 * @name    Communications Operation Procedure Notifications
 * @{
 */
typedef enum {
    COP_NOTIFY_NONE,
    COP_NOTIFY_ACCEPT,
    COP_NOTIFY_REJECT,
    COP_NOTIFY_RESP_SUCCESS,
    COP_NOTIFY_RESP_FAILURE,
    COP_NOTIFY_ALERT,
    COP_NOTIFY_SUSPEND
} cop_notify_t;
/** @} */

/**
 * @name    Communications Operation Procedure Alert Codes
 * @{
 */
typedef enum {
    COP_ALERT_NONE,
    COP_ALERT_LIMIT,
    COP_ALERT_T1,
    COP_ALERT_LOCKOUT,
    COP_ALERT_SYNC,
    COP_ALERT_NR,
    COP_ALERT_CLCW,
    COP_ALERT_LLIF,
    COP_ALERT_TERM
} cop_alert_t;
/** @} */

/**
 * @name    Communications Operation Procedures and Notifications
 * @{
 */
typedef cop_notify_t (*cop_fop_t)(cop_dir_t directive, void *arg);
typedef void (*cop_farm_t)(void);
typedef void (*cop_notify_cb_t)(cop_notify_t notification, cop_alert_t reason);
/** @} */

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

#endif /* _COP_H_ */
/** @} */
