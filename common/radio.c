/**
 * @file    radio.c
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @{
 */
#include "ch.h"
#include "hal.h"
#include "radio.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

static radio_config_t *config = NULL;

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

void radio_init(void)
{
    /* Initialize radio systems */
    for (int i = 0; config->radio_devices[i].devp != NULL; i++) {
        ax5043ObjectInit(config->radio_devices[i].devp);
    }
    for (int i = 0; config->synth_devices[i].devp != NULL; i++) {
        si41xxObjectInit(config->synth_devices[i].devp);
    }
}

void radio_start(radio_config_t *radio_config)
{
    config = radio_config;

    /* Start radio systems */
    for (int i = 0; config->radio_devices[i].devp != NULL; i++) {
        ax5043Start(config->radio_devices[i].devp, config->radio_devices[i].cfgp);
    }
    for (int i = 0; config->synth_devices[i].devp != NULL; i++) {
        si41xxStart(config->synth_devices[i].devp, config->synth_devices[i].cfgp);
    }
}

void radio_stop(void)
{
    for (int i = 0; config->radio_devices[i].devp != NULL; i++) {
        ax5043Stop(config->radio_devices[i].devp);
    }
}

/** @} */
