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
void initEQEP1()
{
    //
    // Configure the decoder for quadrature count mode
    //
    EQEP_setDecoderConfig(EQEP1_BASE, (EQEP_CONFIG_2X_RESOLUTION |
                                       EQEP_CONFIG_QUADRATURE |
                                       EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(EQEP1_BASE, EQEP_EMULATIONMODE_RUNFREE);

    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(EQEP1_BASE, EQEP_POSITION_RESET_IDX,
                                  0xFFFFFFFF);

    //
    // Enable the unit timer, setting the frequency to 100 Hz
    //
    EQEP_enableUnitTimer(EQEP1_BASE, (DEVICE_SYSCLK_FREQ / 131072));

    //
    // Configure the position counter to be latched on a unit time out
    //
    EQEP_setLatchMode(EQEP1_BASE, EQEP_LATCH_UNIT_TIME_OUT);

    //
    // Configure and enable the edge-capture unit. The capture clock divider is
    // SYSCLKOUT/64. The unit-position event divider is QCLK/32.
    //
    EQEP_setCaptureConfig(EQEP1_BASE, EQEP_CAPTURE_CLK_DIV_32, EQEP_UNIT_POS_EVNT_DIV_16);
    EQEP_enableCapture(EQEP1_BASE);

    //Enable interrupt
    EQEP_clearInterruptStatus(EQEP1_BASE, EQEP_INT_POS_COMP_MATCH);
    EQEP_clearInterruptStatus(EQEP1_BASE, EQEP_INT_GLOBAL);
    EQEP_enableCompare(EQEP1_BASE);

    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(EQEP1_BASE);
}

//
// Function to configure eQEP1.
//
void initEQEP2()
{
    //
    // Configure the decoder for quadrature count mode
    //
    EQEP_setDecoderConfig(EQEP2_BASE, (EQEP_CONFIG_2X_RESOLUTION |
                                       EQEP_CONFIG_QUADRATURE |
                                       EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(EQEP2_BASE, EQEP_EMULATIONMODE_RUNFREE);

    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(EQEP2_BASE, EQEP_POSITION_RESET_IDX,
                                  0xFFFFFFFF);

    //
    // Enable the unit timer, setting the frequency to 100 Hz
    //
    EQEP_enableUnitTimer(EQEP2_BASE, (DEVICE_SYSCLK_FREQ / 131072));

    //
    // Configure the position counter to be latched on a unit time out
    //
    EQEP_setLatchMode(EQEP2_BASE, EQEP_LATCH_UNIT_TIME_OUT);

    //
    // Configure and enable the edge-capture unit. The capture clock divider is
    // SYSCLKOUT/64. The unit-position event divider is QCLK/32.
    //
    EQEP_setCaptureConfig(EQEP2_BASE, EQEP_CAPTURE_CLK_DIV_32, EQEP_UNIT_POS_EVNT_DIV_16);
    EQEP_enableCapture(EQEP2_BASE);

    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(EQEP2_BASE);
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
