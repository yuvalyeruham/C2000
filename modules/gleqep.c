/*
 * eqep.c
 *
 *  Created on: 23 january 2023
 *      Author: yuval yeruham
 */

#include "modules.h"

//
// Function to configure eQEP1.
//
void initEQEP(uint32_t eqepModule_)
{
    //
    // Configure the decoder for quadrature count mode
    //
    EQEP_setDecoderConfig(eqepModule_, (EQEP_CONFIG_2X_RESOLUTION |
                                       EQEP_CONFIG_QUADRATURE |
                                       EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(eqepModule_, EQEP_EMULATIONMODE_RUNFREE);

    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(eqepModule_, EQEP_POSITION_RESET_IDX,
                                  0xFFFFFFFF);

    //
    // Enable the unit timer, setting the frequency to 100 Hz
    //
    EQEP_enableUnitTimer(eqepModule_, (DEVICE_SYSCLK_FREQ / 131072));

    //
    // Configure the position counter to be latched on a unit time out
    //
    EQEP_setLatchMode(eqepModule_, EQEP_LATCH_UNIT_TIME_OUT);

    //
    // Configure and enable the edge-capture unit. The capture clock divider is
    // SYSCLKOUT/64. The unit-position event divider is QCLK/32.
    //
    EQEP_setCaptureConfig(eqepModule_, EQEP_CAPTURE_CLK_DIV_32, EQEP_UNIT_POS_EVNT_DIV_16);
    EQEP_enableCapture(eqepModule_);

    //Enable interrupt
    EQEP_clearInterruptStatus(eqepModule_, EQEP_INT_POS_COMP_MATCH);
    EQEP_clearInterruptStatus(eqepModule_, EQEP_INT_GLOBAL);
    EQEP_enableCompare(eqepModule_);

    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(eqepModule_);
}

void EQEP_SetCompareValue(uint32_t value_)
{
    HWREG(EQEP1_BASE + EQEP_O_QPOSCMP) = value_;
}

uint32_t EQEP_GetCounts(void)
{
    return HWREG(EQEP1_BASE + EQEP_O_QPOSCNT);
}

uint32_t EQEP_GetCOmpareValue(void)
{
    return HWREG(EQEP1_BASE + EQEP_O_QPOSCMP);
}
