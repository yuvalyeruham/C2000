/*
 * epwm.c
 *
 *  Created on: 23 ????? 2023
 *      Author: yuval yeruham
 */
#include "modules.h"

//
// Function to configure ePWM1 to generate a 5 kHz signal.
//
void initEPWM(void)
{
    //
    // Disable the ePWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set phase shift to 0 and clear the time base counter
    //
    EPWM_setPhaseShift(EPWM1_BASE, 0);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    EPWM_disableCounterCompareShadowLoadMode(EPWM1_BASE,
                                             EPWM_COUNTER_COMPARE_A);
    EPWM_disableCounterCompareShadowLoadMode(EPWM1_BASE,
                                             EPWM_COUNTER_COMPARE_B);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PRD_VAL/2);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_B, 0);

    //
    // Set action qualifier behavior on compare A events
    // - EPWM1A --> 1 when CTR = CMPA and increasing
    // - EPWM1A --> 0 when CTR = CMPA and decreasing
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Set action qualifier behavior on compare B events
    // - EPWM1B --> 1 when CTR = PRD and increasing
    // - EPWM1B --> 0 when CTR = 0 and decreasing
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Enable interrupt when the counter is equal to PRD
    //
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_PERIOD);
    EPWM_enableInterrupt(EPWM1_BASE);

    //
    // Interrupt on first event
    //
    EPWM_setInterruptEventCount(EPWM1_BASE, 1);

    //
    // Set the time base clock prescaler to /2
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_2,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    EPWM_setPeriodLoadMode(EPWM1_BASE, EPWM_PERIOD_DIRECT_LOAD);
    EPWM_setTimeBasePeriod(EPWM1_BASE, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

