#include "batt.h"
#include "max17205.h"
#include "CANopen.h"

#define NCELLS          2U          /* Number of cells */
#if 0
#define FASTCHG_THRSH   250U        /* Threshold below VBUS to enable Fast Charge (mV) */
#define SLOWCHG_THRSH   500U        /* Threshold below VBUS to enable Slow Charge (mV) */
#endif

typedef enum {
	BATTERY_STATE_MACHINE_STATE_NOT_HEATING = 0,
	BATTERY_STATE_MACHINE_STATE_HEATING,
} battery_heating_state_machine_state_t;

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const max17205_regval_t batt_cfg[] = {
    {MAX17205_AD_PACKCFG, MAX17205_SETVAL(MAX17205_AD_PACKCFG,
                                          _VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                                          MAX17205_PACKCFG_BALCFG_40 |
                                          MAX17205_PACKCFG_CHEN)},
    {MAX17205_AD_NRSENSE, MAX17205_RSENSE2REG(10000U)},
    {0,0}
};

static const MAX17205Config max17205config = {
    &I2CD1,
    &i2cconfig,
    batt_cfg
};

static MAX17205Driver max17205dev;

battery_heating_state_machine_state_t current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;


void run_battery_heating_state_machine(void) {
	//Temperature values are in 0.001C increments
	const int16_t avg_temp_1 = max17205ReadTemperature(&max17205dev, MAX17205_AD_AVGTEMP1);
	const int16_t avg_temp_2 = max17205ReadTemperature(&max17205dev, MAX17205_AD_AVGTEMP2);

	const uint16_t total_state_of_charge = OD_battery.presentStateOfCharge;

	const uint16_t pack_1_charge_percent = total_state_of_charge;//FIXME get pack specific numbers?
	const uint16_t pack_2_charge_percent = total_state_of_charge;//FIXME get pack specific numbers?


	switch (current_batery_state_machine_state) {
		case BATTERY_STATE_MACHINE_STATE_HEATING:
			//Assert MOARPWR (active high).
			palSetPad(GPIOB, GPIOB_MOARPWR);
			//Assert HEATER-ON-1 and HEATER-ON-2 (active high).
			palSetPad(GPIOC, GPIOC_HEATER_ON_1);
			palSetPad(GPIOC, GPIOC_HEATER_ON_2);
			//Once they’re greater than 5 °C or the combined pack capacity is < 25%

			if( (avg_temp_1 > 5000 && avg_temp_2 > 5000) || (total_state_of_charge < 25) ) {
				current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
			}
			break;
		case BATTERY_STATE_MACHINE_STATE_NOT_HEATING:
			//Deassert HEATER-ON-1 and HEATER-ON-2
			palClearPad(GPIOC, GPIOC_HEATER_ON_1);
			palClearPad(GPIOC, GPIOC_HEATER_ON_2);
			//Deassert MOARPWR.
			palClearPad(GPIOB, GPIOB_MOARPWR);

			if( (avg_temp_1 < -5000 || avg_temp_2 < -5000) && (pack_1_charge_percent > 25 || pack_2_charge_percent > 25) ) {
				current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_HEATING;
			}
			break;
		default:
			current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
			break;
	}
}


void update_battery_charging_state(void) {
	if( OD_battery.VCell < 3000 || OD_battery.presentStateOfCharge < 20 ) {
		//Disable discharge on both packs
		palSetPad(GPIOA, GPIOA_DCHG_DIS_PK1);
		palSetPad(GPIOB, GPIOB_DCHG_DIS_PK2);
	} else {
		//Enable discharge on both packs
		palClearPad(GPIOA, GPIOA_DCHG_DIS_PK1);
		palClearPad(GPIOB, GPIOB_DCHG_DIS_PK2);
	}


	if( OD_battery.VCell > 4100 ) {
		//Disable charging on both packs
		palSetPad(GPIOA, GPIOA_CHG_DIS_PK1);
		palSetPad(GPIOB, GPIOB_CHG_DIS_PK2);
	} else {
		//Enable charging on both packs
		palClearPad(GPIOA, GPIOA_CHG_DIS_PK1);
		palClearPad(GPIOB, GPIOB_CHG_DIS_PK2);

		if( OD_battery.presentStateOfCharge > 90 ) {
			const int16_t vcell_delta = OD_battery.cell1 - OD_battery.cell2;
			if( vcell_delta < -50 || vcell_delta > 50 ) {
				//TODO command cell  balancing - this appears to be done in hardware based on config registers???
			}
		}
	}
}


/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x400);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    max17205ObjectInit(&max17205dev);
    max17205Start(&max17205dev, &max17205config);

    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(1000);

        /* Record pack and cell voltages to object dictionary */
        OD_battery.cell1 = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGCELL1);
        OD_battery.cell2 = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGCELL2);
        OD_battery.VCell = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGVCELL);

#if 0
        /* TODO: Fast charge removed from Battery v2? */
        if (OD_battery.VCell >= OD_battery.VBUS - FASTCHG_THRSH) {
            /*palSetLine(LINE_FASTCHG);*/
        } else if (OD_battery.VCell >= OD_battery.VBUS - SLOWCHG_THRSH) {
            /*palClearLine(LINE_FASTCHG);*/
        } else {
            /*palClearLine(LINE_FASTCHG);*/
        }
#endif

        /* capacity */
        OD_battery.fullCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_FULLCAP);
        OD_battery.availableCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_AVCAP);
        OD_battery.mixCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_MIXCAP);

        /* state of charge */
        OD_battery.timeToEmpty = max17205ReadTime(&max17205dev, MAX17205_AD_TTE);
        OD_battery.timeToFull = max17205ReadTime(&max17205dev, MAX17205_AD_TTF);
        OD_battery.availableStateOfCharge = max17205ReadPercentage(&max17205dev, MAX17205_AD_AVSOC);
        OD_battery.presentStateOfCharge = max17205ReadPercentage(&max17205dev, MAX17205_AD_VFSOC);

        /* other info */
        OD_battery.cycles = max17205ReadRaw(&max17205dev, MAX17205_AD_CYCLES);

        run_battery_heating_state_machine();
        update_battery_charging_state();

        /* Toggle LED */
        palToggleLine(LINE_LED);
    }

    max17205Stop(&max17205dev);

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
