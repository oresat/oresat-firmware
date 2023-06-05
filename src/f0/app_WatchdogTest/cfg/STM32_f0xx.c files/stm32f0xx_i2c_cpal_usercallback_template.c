/**
  ******************************************************************************
  * @file    stm32f0xx_i2c_cpal_usercallback.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    13-October-2021
  * @brief   This file provides all the CPAL UserCallback functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_i2c_cpal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*------------------------------------------------------------------------------
                     CPAL User Callbacks implementations 
------------------------------------------------------------------------------*/


/*=========== Timeout UserCallback ===========*/


/**
  * @brief  User callback that manages the Timeout error
  * @param  pDevInitStruct
  * @retval None.
  */
uint32_t CPAL_TIMEOUT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
 
  return CPAL_PASS;
}


/*=========== Transfer UserCallback ===========*/


/**
  * @brief  Manages the End of Tx transfer event
  * @param  pDevInitStruct 
  * @retval None
  */
/*void CPAL_I2C_TXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages the End of Rx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_RXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages Tx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_TX_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages Rx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_RX_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages the End of DMA Tx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMATXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages the Half of DMA Tx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMATXHT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages Error of DMA Tx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMATXTE_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages the End of DMA Rx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMARXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages the Half of DMA Rx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMARXHT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  Manages Error of DMA Rx transfer event
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DMARXTE_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/*=========== Error UserCallback ===========*/


/**
  * @brief  User callback that manages the I2C device errors
  * @note   Make sure that the define USE_SINGLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional
  * @param  pDevInitStruct
  * @param  DeviceError
  * @retval None
  */
/*void CPAL_I2C_ERR_UserCallback(CPAL_DevTypeDef pDevInstance, uint32_t DeviceError)
{

}*/


/**
  * @brief  User callback that manages BERR I2C device errors
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional
  * @param  pDevInstance
  * @retval None
  */
/*void CPAL_I2C_BERR_UserCallback(CPAL_DevTypeDef pDevInstance)
{

}*/


/**
  * @brief  User callback that manages ARLO I2C device errors
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional
  * @param  pDevInstance
  * @retval None
  */
/*void CPAL_I2C_ARLO_UserCallback(CPAL_DevTypeDef pDevInstance)
{

}*/


/**
  * @brief  User callback that manages OVR I2C device errors
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional
  * @param  pDevInstance
  * @retval None
  */
/*void CPAL_I2C_OVR_UserCallback(CPAL_DevTypeDef pDevInstance)
{

}*/


/**
  * @brief  User callback that manages AF I2C device errors.
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional
  * @param  pDevInstance
  * @retval None
  */
/*void CPAL_I2C_AF_UserCallback(CPAL_DevTypeDef pDevInstance)
{

}*/


/*=========== Addressing Mode UserCallback ===========*/


/**
  * @brief  User callback that manage General Call Addressing mode
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_GENCALL_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


/**
  * @brief  User callback that manage Dual Address Addressing mode
  * @param  pDevInitStruct
  * @retval None
  */
/*void CPAL_I2C_DUALF_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{

}*/


