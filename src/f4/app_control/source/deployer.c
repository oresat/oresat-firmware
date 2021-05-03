#include "ch.h"
#include "hal.h"
#include "deployer.h"

void deploy_heli(uint32_t duration)
{
    palSetLine(LINE_FIRE_HELI_1);
    palSetLine(LINE_FIRE_HELI_2);
    chThdSleepMilliseconds(duration);
    palClearLine(LINE_FIRE_HELI_1);
    palClearLine(LINE_FIRE_HELI_2);

    return;
}

void deploy_turn(uint32_t duration)
{
    palSetLine(LINE_FIRE_TURN_1);
    palSetLine(LINE_FIRE_TURN_2);
    chThdSleepMilliseconds(duration);
    palClearLine(LINE_FIRE_TURN_1);
    palClearLine(LINE_FIRE_TURN_2);

    return;
}
