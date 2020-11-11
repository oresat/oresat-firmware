/**
 * @file    uslp.h
 * @brief   Unified Space Data Link Protocol (USLP) support library.
 *
 * @addtogroup USLP
 * @{
 */
#ifndef _USLP_H_
#define _USLP_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(USLP_USE_SDLS) && USLP_USE_SDLS == 1
#include "sdls.h"
#endif

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/**
 * @name    Transfer Frame Primary Header
 * @{
 */
/**
 * @brief   Identification Fields
 * @{
 */
/** Transfer Frame Version Number */
#define USLP_TFPH_ID_TFVN_Pos               (28U)
#define USLP_TFPH_ID_TFVN_Msk               (0xFU << USLP_TFPH_ID_TFVN_Pos)
#define USLP_TFPH_ID_TFVN                   USLP_TFPH_ID_TFVN_Msk
#define USLP_TFVN                           (0xCU)
/** Spacecraft Identifier */
#define USLP_TFPH_ID_SCID_Pos               (12U)
#define USLP_TFPH_ID_SCID_Msk               (0xFFFFU << USLP_TFPH_ID_SCID_Pos)
#define USLP_TFPH_ID_SCID                   USLP_TFPH_ID_SCID_Msk
/** Master Channel Identifier */
#define USLP_TFPH_ID_MCID_Pos               (12U)
#define USLP_TFPH_ID_MCID_Msk               (0xFFFFFU << USLP_TFPH_ID_MCID_Pos)
#define USLP_TFPH_ID_MCID                   USLP_TFPH_ID_MCID_Msk
/** Source or Destination Identifier */
#define USLP_TFPH_ID_SRC_DST_Pos            (11U)
#define USLP_TFPH_ID_SRC_DST_Msk            (0x1U << USLP_TFPH_ID_SRC_DST_Pos)
#define USLP_TFPH_ID_SRC_DST                USLP_TFPH_ID_SRC_DST_Msk
/** Virtual Channel Identifier */
#define USLP_TFPH_ID_VCID_Pos               (5U)
#define USLP_TFPH_ID_VCID_Msk               (0x3FU << USLP_TFPH_ID_VCID_Pos)
#define USLP_TFPH_ID_VCID                   USLP_TFPH_ID_VCID_Msk
/** Multiplexer Access Point Identifier */
#define USLP_TFPH_ID_MAPID_Pos              (1U)
#define USLP_TFPH_ID_MAPID_Msk              (0xFU << USLP_TFPH_ID_MAPID_Pos)
#define USLP_TFPH_ID_MAPID                  USLP_TFPH_ID_MAPID_Msk
/** End of Frame Primary Header Flag */
#define USLP_TFPH_ID_EOFPH_Pos              (0U)
#define USLP_TFPH_ID_EOFPH_Msk              (0x1U << USLP_TFPH_ID_EOFPH_Pos)
#define USLP_TFPH_ID_EOFPH                  USLP_TFPH_ID_EOFPH_Msk
/** @} */
/**
 * @brief   Additional TFPH flags and fields
 * @{
 */
/** Bypass/Sequence Control Flag        */
#define USLP_TFPH_MISC_BYPASS_SEQ_CTRL_Pos  (7U)
#define USLP_TFPH_MISC_BYPASS_SEQ_CTRL_Msk  (0x1U << USLP_TFPH_MISC_BYPASS_SEQ_CTRL_Pos)
#define USLP_TFPH_MISC_BYPASS_SEQ_CTRL      USLP_TFPH_MISC_BYPASS_SEQ_CTRL_Msk
/** Protocol Control Command Flag       */
#define USLP_TFPH_MISC_PROTO_CTRL_CMD_Pos   (6U)
#define USLP_TFPH_MISC_PROTO_CTRL_CMD_Msk   (0x1U << USLP_TFPH_MISC_PROTO_CTRL_CMD_Pos)
#define USLP_TFPH_MISC_PROTO_CTRL_CMD       USLP_TFPH_MISC_PROTO_CTRL_CMD_Msk
/** Operational Control Field Flag      */
#define USLP_TFPH_MISC_OCF_Pos              (3U)
#define USLP_TFPH_MISC_OCF_Msk              (0x1U << USLP_TFPH_MISC_OCF_Pos)
#define USLP_TFPH_MISC_OCF                  USLP_TFPH_MISC_OCF_Msk
/** VC Frame Count Length               */
#define USLP_TFPH_MISC_VC_FRM_CNT_LEN_Pos   (0U)
#define USLP_TFPH_MISC_VC_FRM_CNT_LEN_Msk   (0x7U << USLP_TFPH_MISC_VC_FRM_CNT_LEN_Pos)
#define USLP_TFPH_MISC_VC_FRM_CNT_LEN       USLP_TFPH_MISC_VC_FRM_CNT_LEN_Msk
/** @} */
/** @} */

/**
 * @name    Transfer Frame Data Field Header
 * @{
 */
/** Transfer Frame Data Zone (TFDZ) Contruction Rules */
#define USLP_TFDF_HDR_TFDZ_RULES_Pos        (5U)
#define USLP_TFDF_HDR_TFDZ_RULES_Msk        (0x7U << USLP_TFDF_HDR_TFDZ_RULES_Pos)
#define USLP_TFDF_HDR_TFDZ_RULES            USLP_TFDF_HDR_TFDZ_RULES_Msk
#define USLP_TFDZ_RULES_MULTI_FRAME         (0x0U)
#define USLP_TFDZ_RULES_START_MAPA_SDU      (0x1U)
#define USLP_TFDZ_RULES_CONT_MAPA_SDU       (0x2U)
#define USLP_TFDZ_RULES_OCTET_STREAM        (0x3U)
#define USLP_TFDZ_RULES_START_SEG           (0x4U)
#define USLP_TFDZ_RULES_CONT_SEG            (0x5U)
#define USLP_TFDZ_RULES_LAST_SEG            (0x6U)
#define USLP_TFDZ_RULES_NO_SEG              (0x7U)
/** USLP Protocol Identifier */
#define USLP_TFDF_HDR_UPID_Pos              (0U)
#define USLP_TFDF_HDR_UPID_Msk              (0x1FU << USLP_TFDF_HDR_UPID_Pos)
#define USLP_TFDF_HDR_UPID                  USLP_TFDF_HDR_UPID_Msk
/** @} */

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
#define USLP_USE_SDLS                       0
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

/**
 * @name    USLP Protocol Identifier (UPID)
 * @{
 */
typedef enum {
    UPID_SPP_ENCAPS = 0x00U,    /** Space Packets or Encapsulation Packets   */
    UPID_COP_1      = 0x01U,    /** COP-1 Control Commands                   */
    UPID_COP_P      = 0x02U,    /** COP-P Control Commands                   */
    UPID_SDLS       = 0x03U,    /** SDLS Control Commands                    */
    UPID_USER_DEF   = 0x04U,    /** User-defined Octet Stream                */
    UPID_MAPA_SDU   = 0x05U,    /** Mission-specific information-1 MAPA_SDU  */
    UPID_PROX_1     = 0x07U,    /** Proximity-1 SPDU                         */
    UPID_IDLE       = 0x1FU     /** Idle Data                                */
} uslp_pid_t;
/** @} */

/**
 * @name    Packet Version Number (PVN)
 * TODO: Move to CCSDS header?
 * @{
 */
typedef enum {
    PVN_SPACE       = 0x0U,     /** Space Packet                             */
    PVN_ENCAPS      = 0x7U      /** Encapsuation Packet                      */
} ccsds_pvn_t;
/** @} */

/**
 * @name    USLP Service Data Unit Type
 * @{
 */
typedef enum {
    SDU_MAP_PKT,                /** MAPP_SDU                                 */
    SDU_MAP_ACCESS,             /** MAPA_SDU                                 */
    SDU_MAP_OCTET_STREAM        /** MAP Octet Stream SDU                     */
} uslp_sdu_t;
/** @} */

/**
 * @name    USLP Communications Operation Procedure in Effect
 * @{
 */
typedef enum {
    COP_NONE,                   /** No COP in effect                         */
    COP_COP_1,                  /** COP-1 in effect                          */
    COP_COP_P                   /** COP-P in effect                          */
} uslp_cop_t;
/** @} */

/**
 * @name    USLP Packet Definition
 * @{
 */
typedef struct {
    ccsds_pvn_t pvn;            /** Packet Version Number                    */
    size_t      max_pkt_len;    /** Maximum Packet Length                    */
    bool        incomplete;     /** Delivery of incomplete packets required  */
    void        (*pkt_recv)(const void *sdu, size_t len, size_t offset, const void *pkt_arg);
    const void  *pkt_arg;
} uslp_pkt_t;
/** @} */

/**
 * @name    USLP Multiplexer Access Point Definition
 * @{
 */
typedef struct {
    uslp_sdu_t  sdu;            /** Service Data Unit Type                   */
    uslp_pid_t  upid;           /** USLP Protocol Identifier                 */
    const uslp_pkt_t *pkt;      /** Packet definition for SDU_MAP_PKT        */
} uslp_map_t;
/** @} */

/**
 * @name    USLP Virtual Channel Definition
 * @{
 */
typedef struct {
    bool        fixed;          /** (1) Fixed or (0) Variable Length Channel */
    uint64_t    seq_ctrl_len;   /** VC Count Length for Sequence Control QoS */
    uint64_t    expedited_len;  /** VC Count Length for Expedited QoS        */
    uslp_cop_t  cop;            /** COP in Effect                            */
    const uslp_map_t *mapid[16];/** Multiplexer Access Points                */
    size_t      trunc_tf_len;   /** Truncated Transfer Frame Length          */
    bool        ocf;            /** OCF Allowed (Variable) / Required (Fixed)*/
#if USLP_USE_SDLS == 1
    sdls_hdr_t  *sdls_hdr;      /** Pointer to SDLS Header if applicable     */
    sdls_tlr_t  *sdls_tlr;      /** Pointer to SDLS Trailer if applicable    */
    size_t      sdls_hdr_len;   /** SDLS Header Length (octets)              */
    size_t      sdls_tlr_len;   /** SDLS Trailer Length (octets)             */
#endif
} uslp_vc_t;
/** @} */

/**
 * @name    USLP Master Channel Definition
 * @{
 */
typedef struct {
    bool        fixed;          /** (1) Fixed or (0) Variable Length Channel */
    uint16_t    scid;           /** Spacecraft Identifier                    */
    const uslp_vc_t *vcid[63];  /** Virtual Channels                         */
} uslp_mc_t;
/** @} */

/**
 * @name    USLP Physical Channel Definition
 * @{
 */
typedef struct {
    const char  *name;          /** Physical Channel Name                    */
    bool        fixed;          /** (1) Fixed or (0) Variable Length Channel */
    size_t      tf_len;         /** Transfer Frame Length (octets)           */
    bool        insert_zone;    /** Presence of Insert Zone                  */
    size_t      insert_zone_len;/** Insert Zone Length (octets)              */
    bool        fecf;           /** Presence of Frame Error Control Field    */
    size_t      fecf_len;       /** Frame Error Control Field Length (octets)*/
    bool        gen_oid;        /** Generate OID Frame                       */
    void        (*phy_send)(const void *pdu, size_t len, const void *phy_arg);
    const void  *phy_arg;
} uslp_pc_t;
/** @} */

/**
 * @name    USLP Socket Descriptor
 * @{
 */
typedef struct {
    const uslp_pc_t *phy_chan;
    const uslp_mc_t *master_chan;
    uint8_t     vcid;
    uint8_t     mapid;
} uslp_sock_t;
/** @} */

/**
 * @name    USLP Tranfer Frame Primary Header (TFPH)
 * @{
 */
typedef struct __attribute__((packed)) {
    uint32_t    id;              /** Identifier fields                       */
    uint16_t    len;             /** Frame Length                            */
    uint8_t     misc;            /** Additional flags and fields             */
    uint8_t     vc_frm_cnt[];    /** Virtual Channel Frame Count             */
} uslp_tfph_t;
/** @} */

/**
 * @name    USLP Transfer Frame Data Field (TFDF) Header
 * @{
 */
typedef struct __attribute__((packed)) {
    uint8_t     flags;          /** TFDZ Construction Rules and UPID fields  */
    uint16_t    offset;         /** First Header/Last Valid Octet Offset     */
} uslp_tfdf_hdr_t;
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
void uslp_send(const void *pdu, size_t len, const void *arg);
void uslp_recv(const void *pdu, size_t len, size_t offset, const void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _USLP_H_ */

/** @} */
