/*
 * uART.C
 *
 *  Created on: 23 ????? 2023
 *      Author: yuval yeruham
 */

#include "modules.h"

void SetUart()
{

        // GPIO43 is the SCI Rx pin.
        //
        //GPIO_setControllerCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
        GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
        GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

        //
        // GPIO42 is the SCI Tx pin.
        //
        //GPIO_setControllerCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
        GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
        GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

        //
        // Initialize SCIA and its FIFO.
        //
        SCI_performSoftwareReset(SCIA_BASE);

        //
        // Configure SCIA for echoback.
        //
        SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 460800, (SCI_CONFIG_WLEN_8 |
                                                            SCI_CONFIG_STOP_ONE |
                                                            SCI_CONFIG_PAR_NONE));
        SCI_resetChannels(SCIA_BASE);
        SCI_resetRxFIFO(SCIA_BASE);
        SCI_resetTxFIFO(SCIA_BASE);
        SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
        SCI_enableFIFO(SCIA_BASE);
        SCI_enableModule(SCIA_BASE);
        SCI_performSoftwareReset(SCIA_BASE);
}


