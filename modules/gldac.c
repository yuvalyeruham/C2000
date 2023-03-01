/*
 * dac.c
 *
 *  Created on: 25 ????? 2023
 *      Author: yuval yeruham
 */

#include "modules.h"

void configureDAC(void)
{
    //
    // Set VDAC as the DAC reference voltage.
    // Edit here to use ADC VREF as the reference voltage.
    //
    //DAC_setReferenceVoltage(DACA_BASE, DAC_REF_VDAC);
    DAC_setReferenceVoltage(DACA_BASE, DAC_REF_ADC_VREFHI);

    //
    // Enable the DAC output
    //
    DAC_enableOutput(DACA_BASE);

    //
    // Set the DAC shadow output to 0
    //
    DAC_setShadowValue(DACA_BASE, 0);

    //
    // Delay for buffered DAC to power up
    //
    DEVICE_DELAY_US(10);
}


