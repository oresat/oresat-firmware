#include "ch.h"
#include "hal.h"
#include "deployer.h"

bool deploy_heli(void)
{
    palSetLine(LINE_FIRE_HELI_1);
    palSetLine(LINE_FIRE_HELI_2);
    chThdSleepMilliseconds(1000);
    palClearLine(LINE_FIRE_HELI_1);
    palClearLine(LINE_FIRE_HELI_2);
}

bool deploy_turn(void)
{
    palSetLine(LINE_FIRE_TURN_1);
    palSetLine(LINE_FIRE_TURN_2);
    chThdSleepMilliseconds(1000);
    palClearLine(LINE_FIRE_TURN_1);
    palClearLine(LINE_FIRE_TURN_2);
}
