/**
 * @file    max17205.h
 * @brief   MAX17205 Power Monitor.
 *
 * @addtogroup MAX17205
 * @ingroup ORESAT
 * @{
 */
#ifndef _MAX17205_H_
#define _MAX17205_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   MAX17205 Driver version string.
 */
#define MAX17205_VERSION                    "1.0.0"

/**
 * @brief   MAX17205 Driver version major number.
 */
#define MAX17205_MAJOR                      1

/**
 * @brief   MAX17205 Driver version minor number.
 */
#define MAX17205_MINOR                      0

/**
 * @brief   MAX17205 Driver version patch number.
 */
#define MAX17205_PATCH                      0
/** @} */

/**
 * @name    MAX17205 Register Addresses
 * TODO: Enumerate remaining register addresses
 * @{
 */
#define MAX17205_AD_STATUS                  0x0000U
#define MAX17205_AD_COMMAND                 0x0060U
#define MAX17205_AD_CONFIG                  0x001DU
#define MAX17205_AD_CONFIG2                 0x00BBU
/** @} */

/* TODO: Define fields and values for all registers */
/**
 * @name    MAX17205 Status register fields
 * @{
 */
#define MAX17205_STATUS_POR_Pos             (1U)
#define MAX17205_STATUS_POR_Msk             (0x1U << MAX17205_STATUS_POR_Pos)
#define MAX17205_STATUS_POR                 MAX17205_STATUS_POR_Msk
#define MAX17205_STATUS_IMN_Pos             (2U)
#define MAX17205_STATUS_IMN_Msk             (0x1U << MAX17205_STATUS_IMN_Pos)
#define MAX17205_STATUS_IMN                 MAX17205_STATUS_IMN_Msk
#define MAX17205_STATUS_BST_Pos             (4U)
#define MAX17205_STATUS_BST_Msk             (0x1U << MAX17205_STATUS_BST_Pos)
#define MAX17205_STATUS_BST                 MAX17205_STATUS_BST_Msk
#define MAX17205_STATUS_IMX_Pos             (6U)
#define MAX17205_STATUS_IMX_Msk             (0x1U << MAX17205_STATUS_IMX_Pos)
#define MAX17205_STATUS_IMX                 MAX17205_STATUS_IMX_Msk
#define MAX17205_STATUS_DSOCI_Pos           (7U)
#define MAX17205_STATUS_DSOCI_Msk           (0x1U << MAX17205_STATUS_DSOCI_Pos)
#define MAX17205_STATUS_DSOCI               MAX17205_STATUS_DSOCI_Msk
#define MAX17205_STATUS_VMN_Pos             (8U)
#define MAX17205_STATUS_VMN_Msk             (0x1U << MAX17205_STATUS_VMN_Pos)
#define MAX17205_STATUS_VMN                 MAX17205_STATUS_VMN_Msk
#define MAX17205_STATUS_TMN_Pos             (9U)
#define MAX17205_STATUS_TMN_Msk             (0x1U << MAX17205_STATUS_TMN_Pos)
#define MAX17205_STATUS_TMN                 MAX17205_STATUS_TMN_Msk
#define MAX17205_STATUS_SMN_Pos             (10U)
#define MAX17205_STATUS_SMN_Msk             (0x1U << MAX17205_STATUS_SMN_Pos)
#define MAX17205_STATUS_SMN                 MAX17205_STATUS_SMN_Msk
#define MAX17205_STATUS_BI_Pos              (11U)
#define MAX17205_STATUS_BI_Msk              (0x1U << MAX17205_STATUS_BI_Pos)
#define MAX17205_STATUS_BI                  MAX17205_STATUS_BI_Msk
#define MAX17205_STATUS_VMX_Pos             (12U)
#define MAX17205_STATUS_VMX_Msk             (0x1U << MAX17205_STATUS_VMX_Pos)
#define MAX17205_STATUS_VMX                 MAX17205_STATUS_VMX_Msk
#define MAX17205_STATUS_TMX_Pos             (13U)
#define MAX17205_STATUS_TMX_Msk             (0x1U << MAX17205_STATUS_TMX_Pos)
#define MAX17205_STATUS_TMX                 MAX17205_STATUS_TMX_Msk
#define MAX17205_STATUS_SMX_Pos             (14U)
#define MAX17205_STATUS_SMX_Msk             (0x1U << MAX17205_STATUS_SMX_Pos)
#define MAX17205_STATUS_SMX                 MAX17205_STATUS_SMX_Msk
#define MAX17205_STATUS_BR_Pos              (15U)
#define MAX17205_STATUS_BR_Msk              (0x1U << MAX17205_STATUS_BR_Pos)
#define MAX17205_STATUS_BR                  MAX17205_STATUS_BR_Msk
/** @} */

/**
 * @name    MAX17205 Command register values
 * TODO: Enumerate remaining commands
 * @{
 */
#define MAX17205_COMMAND_RST                0x000FU
/** @} */

/**
 * @name    MAX17205 Config register fields
 * @{
 */
#define MAX17205_CONFIG_BER_Pos             (0U)
#define MAX17205_CONFIG_BER_Msk             (0x1U << MAX17205_CONFIG_BER_Pos)
#define MAX17205_CONFIG_BER                 MAX17205_CONFIG_BER_Msk
#define MAX17205_CONFIG_BEI_Pos             (1U)
#define MAX17205_CONFIG_BEI_Msk             (0x1U << MAX17205_CONFIG_BEI_Pos)
#define MAX17205_CONFIG_BEI                 MAX17205_CONFIG_BEI_Msk
#define MAX17205_CONFIG_AEN_Pos             (2U)
#define MAX17205_CONFIG_AEN_Msk             (0x1U << MAX17205_CONFIG_AEN_Pos)
#define MAX17205_CONFIG_AEN                 MAX17205_CONFIG_AEN_Msk
#define MAX17205_CONFIG_FTHRM_Pos           (3U)
#define MAX17205_CONFIG_FTHRM_Msk           (0x1U << MAX17205_CONFIG_FTHRM_Pos)
#define MAX17205_CONFIG_FTHRM               MAX17205_CONFIG_FTHRM_Msk
#define MAX17205_CONFIG_ETHRM_Pos           (4U)
#define MAX17205_CONFIG_ETHRM_Msk           (0x1U << MAX17205_CONFIG_ETHRM_Pos)
#define MAX17205_CONFIG_ETHRM               MAX17205_CONFIG_ETHRM_Msk
#define MAX17205_CONFIG_COMMSH_Pos          (6U)
#define MAX17205_CONFIG_COMMSH_Msk          (0x1U << MAX17205_CONFIG_COMMSH_Pos)
#define MAX17205_CONFIG_COMMSH              MAX17205_CONFIG_COMMSH_Msk
#define MAX17205_CONFIG_SHDN_Pos            (7U)
#define MAX17205_CONFIG_SHDN_Msk            (0x1U << MAX17205_CONFIG_SHDN_Pos)
#define MAX17205_CONFIG_SHDN                MAX17205_CONFIG_SHDN_Msk
#define MAX17205_CONFIG_TEX_Pos             (8U)
#define MAX17205_CONFIG_TEX_Msk             (0x1U << MAX17205_CONFIG_TEX_Pos)
#define MAX17205_CONFIG_TEX                 MAX17205_CONFIG_TEX_Msk
#define MAX17205_CONFIG_TEN_Pos             (9U)
#define MAX17205_CONFIG_TEN_Msk             (0x1U << MAX17205_CONFIG_TEN_Pos)
#define MAX17205_CONFIG_TEN                 MAX17205_CONFIG_TEN_Msk
#define MAX17205_CONFIG_AINSH_Pos           (10U)
#define MAX17205_CONFIG_AINSH_Msk           (0x1U << MAX17205_CONFIG_AINSH_Pos)
#define MAX17205_CONFIG_AINSH               MAX17205_CONFIG_AINSH_Msk
#define MAX17205_CONFIG_ALRTP_Pos           (11U)
#define MAX17205_CONFIG_ALRTP_Msk           (0x1U << MAX17205_CONFIG_ALRTP_Pos)
#define MAX17205_CONFIG_ALRTP               MAX17205_CONFIG_ALRTP_Msk
#define MAX17205_CONFIG_VS_Pos              (12U)
#define MAX17205_CONFIG_VS_Msk              (0x1U << MAX17205_CONFIG_VS_Pos)
#define MAX17205_CONFIG_VS                  MAX17205_CONFIG_VS_Msk
#define MAX17205_CONFIG_VS_Pos              (13U)
#define MAX17205_CONFIG_VS_Msk              (0x1U << MAX17205_CONFIG_TS_Pos)
#define MAX17205_CONFIG_TS                  MAX17205_CONFIG_TS_Msk
#define MAX17205_CONFIG_VS_Pos              (14U)
#define MAX17205_CONFIG_VS_Msk              (0x1U << MAX17205_CONFIG_SS_Pos)
#define MAX17205_CONFIG_SS                  MAX17205_CONFIG_SS_Msk
/** @} */

/**
 * @name    MAX17205 Config2 register fields
 * @{
 */
#define MAX17205_CONFIG2_POR_CMD_Pos        (0U)
#define MAX17205_CONFIG2_POR_CMD_Msk        (0x1U << MAX17205_CONFIG2_POR_CMD_Pos)
#define MAX17205_CONFIG2_POR_CMD            MAX17205_CONFIG2_POR_CMD_Msk
#define MAX17205_CONFIG2_TALRTEN_Pos        (6U)
#define MAX17205_CONFIG2_TALRTEN_Msk        (0x1U << MAX17205_CONFIG2_TALRTEN_Pos)
#define MAX17205_CONFIG2_TALRTEN            MAX17205_CONFIG2_TALRTEN_Msk
#define MAX17205_CONFIG2_DSOCEN_Pos         (7U)
#define MAX17205_CONFIG2_DSOCEN_Msk         (0x1U << MAX17205_CONFIG2_DSOCEN_Pos)
#define MAX17205_CONFIG2_DSOCEN             MAX17205_CONFIG2_DSOCEN_Msk
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MAX17205 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MAX17205_USE_I2C) || defined(__DOXYGEN__)
#define MAX17205_USE_I2C                    TRUE
#endif

/**
 * @brief   MAX17205 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MAX17205_SHARED_I2C) || defined(__DOXYGEN__)
#define MAX17205_SHARED_I2C                 FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MAX17205_USE_I2C && !HAL_USE_I2C
#error "MAX17205_USE_I2C requires HAL_USE_I2C"
#endif

#if MAX17205_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MAX17205_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MAX17205 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a MAX17205 driver.
 */
typedef struct MAX17205Driver MAX17205Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MAX17205_UNINIT = 0,                /**< Not initialized.                */
    MAX17205_STOP = 1,                  /**< Stopped.                        */
    MAX17205_READY = 2,                 /**< Ready.                          */
} max17205_state_t;

/**
 * @brief   MAX17205 configuration structure.
 */
typedef struct {
#if (MAX17205_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MAX17205.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MAX17205.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief MAX17205 Slave Address
     */
    i2caddr_t                   saddr;
#endif /* MAX17205_USE_I2C */
} MAX17205Config;

/**
 * @brief   @p MAX17205 specific methods.
 */
#define _max17205_methods_alone

/**
 * @brief   @p MAX17205 specific methods with inherited ones.
 */
#define _max17205_methods                                                   \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p MAX17205 virtual methods table.
 */
struct MAX17205VMT {
    _max17205_methods
};

/**
 * @brief   @p MAX17205Driver specific data.
 */
#define _max17205_data                                                      \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    max17205_state_t              state;                                    \
    /* Current configuration data.*/                                        \
    const MAX17205Config          *config;

/**
 * @brief MAX17205 Power Monitor class.
 */
struct MAX17205Driver {
    /** @brief Virtual Methods Table.*/
    const struct MAX17205VMT     *vmt;
    _max17205_data
};

/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void max17205ObjectInit(MAX17205Driver *devp);
void max17205Start(MAX17205Driver *devp, const MAX17205Config *config);
void max17205Stop(MAX17205Driver *devp);
#ifdef __cplusplus
}
#endif

#endif /* _MAX17205_H_ */

/** @} */
