/**
 * @file    ax25.h
 * @brief   AX.25 protocol support library.
 *
 * @addtogroup AX25
 * @{
 */
#ifndef _AX25_H_
#define _AX25_H_

#include "pdu.h"

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/**
 * @brief   AX.25 Frames
 * @{
 */
/**
 * @name    AX.25 address fields
 * @{
 */
#define AX25_ADDR_EXT_Pos                   (0U)
#define AX25_ADDR_EXT_Msk                   (0x1U << AX25_ADDR_EXT_Pos)
#define AX25_ADDR_EXT                       AX25_ADDR_EXT_Msk
#define AX25_ADDR_CHAR_Pos                  (1U)
#define AX25_ADDR_CHAR_Msk                  (0xFEU << AX25_ADDR_CHAR_Pos)
#define AX25_ADDR_CHAR                      AX25_ADDR_CHAR_Msk
/** @} */

/**
 * @name    AX.25 SSID fields
 * @{
 */
#define AX25_SSID_EXT_Pos                   (0U)
#define AX25_SSID_EXT_Msk                   (0x1U << AX25_SSID_EXT_Pos)
#define AX25_SSID_EXT                       AX25_SSID_EXT_Msk
#define AX25_SSID_VAL_Pos                   (1U)
#define AX25_SSID_VAL_Msk                   (0xFU << AX25_SSID_VAL_Pos)
#define AX25_SSID_VAL                       AX25_SSID_VAL_Msk
#define AX25_SSID_RESERVED_Pos              (5U)
#define AX25_SSID_RESERVED_Msk              (0x3U << AX25_SSID_RESERVED_Pos)
#define AX25_SSID_RESERVED                  AX25_SSID_RESERVED_Msk
#define AX25_SSID_CMD_RESP_Pos              (7U)
#define AX25_SSID_CMD_RESP_Msk              (0x1U << AX25_SSID_CMD_RESP_Pos)
#define AX25_SSID_CMD_RESP                  AX25_SSID_CMD_RESP_Msk
#define AX25_SSID(ssid)                     (((ssid << AX25_SSID_VAL_Pos) & AX25_SSID_VAL_Msk) | AX25_SSID_RESERVED)
/** @} */

/**
 * @name    AX.25 Control field
 * @{
 */
#define AX25_CTRL_IFRAME                    (0x00U)
#define AX25_CTRL_SFRAME                    (0x01U)
#define AX25_CTRL_UFRAME                    (0x03U)
#define AX25_CTRL_SEND_SEQ_Pos              (1U)
#define AX25_CTRL_SEND_SEQ_Msk              (0x7U << AX25_CTRL_SEND_SEQ_Pos)
#define AX25_CTRL_SEND_SEQ                  AX25_CTRL_SEND_SEQ_Msk
#define AX25_CTRL_SUP_Pos                   (2U)
#define AX25_CTRL_SUP_Msk                   (0x3U << AX25_CTRL_SUP_Pos)
#define AX25_CTRL_SUP                       AX25_CTRL_SUP_Msk
#define AX25_SUP_RR                         (0x0U)
#define AX25_SUP_RNR                        (0x1U)
#define AX25_SUP_REJ                        (0x2U)
#define AX25_SUP_SREJ                       (0x3U)
#define AX25_CTRL_U_FLD_Pos                 (2U)
#define AX25_CTRL_U_FLD_Msk                 (0x3BU << AX25_CTRL_U_FLD_Pos)
#define AX25_CTRL_U_FLD                     AX25_CTRL_U_FLD_Msk
#define AX25_UFRAME_UI                      (0x00U)
#define AX25_UFRAME_DM                      (0x03U)
#define AX25_UFRAME_SABM                    (0x0BU)
#define AX25_UFRAME_DISC                    (0x10U)
#define AX25_UFRAME_UA                      (0x18U)
#define AX25_UFRAME_SABME                   (0x1BU)
#define AX25_UFRAME_FRMR                    (0x21U)
#define AX25_UFRAME_XID                     (0x2BU)
#define AX25_UFRAME_TEST                    (0x38U)
#define AX25_CTRL_POLL_FINAL_Pos            (4U)
#define AX25_CTRL_POLL_FINAL_Msk            (0x1U << AX25_CTRL_POLL_FINAL_Pos)
#define AX25_CTRL_POLL_FINAL                AX25_CTRL_POLL_FINAL_Msk
#define AX25_CTRL_RECV_SEQ_Pos              (5U)
#define AX25_CTRL_RECV_SEQ_Msk              (0x7U << AX25_CTRL_RECV_SEQ_Pos)
#define AX25_CTRL_RECV_SEQ                  AX25_CTRL_RECV_SEQ_Msk
/** @} */

/**
 * @name    AX.25 PID values
 * @{
 */
#define AX25_PID_NONE                       (0xF0U)
/** @} */

/** @} */

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
 * @name    AX.25 Link Descriptor
 * @{
 */
typedef struct {
    char            dest[6];
    uint8_t         dest_ssid;
    char            src[6];
    uint8_t         src_ssid;
    uint8_t         control;
    void            (*phy_send)(const void *pdu, size_t len, const void *phy_arg);
    const void      *phy_arg;
} ax25_link_t;
/** @} */

typedef struct __attribute__((packed)) {
    uint8_t         pid;
    uint8_t         data[];
} ax25_info_t;

/**
 * @name    AX.25 frame data structure.
 * @{
 */
typedef struct __attribute__((packed)) {
    char            dest[6];
    uint8_t         dest_ssid;
    char            src[6];
    uint8_t         src_ssid;
    uint8_t         control;
    uint8_t         data[];
} ax25_frame_t;
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
void ax25_send(pdu_t *pdu, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _AX25_H_ */

/** @} */
