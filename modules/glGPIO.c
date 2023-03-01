/*
 * GPIO.c
 *
 *  Created on: 25 ????? 2023
 *      Author: yuval yeruham
 */

#include "modules.h"

void initGPIOpins(void)
{

    //
    // Initialize GPIO0 to ePWM1A, GPIO1 to ePWM1B.
    // They will be used to simulate incoming eQEP Phase A, Phase B.
    //
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_1_EPWM1B);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);


    //
    // Initialize GPIOs for use as EQEPXA, EQEPXB
    //
    GPIO_setPinConfig(GPIO_20_EQEP1A);
    GPIO_setPadConfig(20, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_21_EQEP1B);
    GPIO_setPadConfig(21, GPIO_PIN_TYPE_STD);




    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);        // Enable pullup on GPIO8
    GPIO_setPinConfig(GPIO_8_GPIO8);                // GPIO8 = GPIO8
    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);    // GPIO8 = output
    GPIO_writePin(8, 1);                            // Load output latch
}

