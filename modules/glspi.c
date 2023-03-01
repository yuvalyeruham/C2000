/*
 * spi.c
 *
 *  Created on: 26 ????? 2023
 *      Author: yuval yeruham
 */

#include "modules.h"


//*****************************************************************************
//
// configureGPIOs - configure GPIOs for SPIA_SLAVE connected to FSI full duplex.
//
//*****************************************************************************
void configureSpiGPIOs(void)
{
    GPIO_setPadConfig(60, GPIO_PIN_TYPE_STD); // Pullup on GPIO16 (SPISIMOA)
    GPIO_setPadConfig(58, GPIO_PIN_TYPE_STD); // Pullup on GPIO17 (SPIS0MIA)
    GPIO_setPadConfig(59, GPIO_PIN_TYPE_STD); // Pullup on GPIO18 (SPICLKA)
    GPIO_setPadConfig(61, GPIO_PIN_TYPE_STD); // Pullup on GPIO19 (SPISTEA)
    //
    // GPIO18 is the SPICLKA driven by FSITX_CLK.
    //
    GPIO_setPinConfig(GPIO_60_SPICLKA);
    GPIO_setQualificationMode(60, GPIO_QUAL_ASYNC);

    //
    // GPIO16 is the SPISIMOA receiving TXD0.
    //
    GPIO_setPinConfig(GPIO_58_SPISIMOA);
    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);

    //
    // GPIO19 is the SPISTEA receiving TXD1.
    //
    GPIO_setPinConfig(GPIO_61_SPISTEA);
    GPIO_setQualificationMode(61, GPIO_QUAL_ASYNC);

    //
    // GPIO17 is the SPISOMIA writing to RXD0.
    //
    GPIO_setPinConfig(GPIO_59_SPISOMIA);
    GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);
}

//*****************************************************************************
//
// configureSPI - configuration of SPIA to spiMode.
//
//*****************************************************************************
void configureSPI()
{
    SPI_disableModule(SPIA_BASE);

       //
       // SPI configuration.
       //
       SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0, SPI_MODE_CONTROLLER, 8000000, 16);
       SPI_disableLoopback(SPIA_BASE);
       SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);
       SPI_enableHighSpeedMode(SPIA_BASE);
       //
       // FIFO and interrupt configuration
       //
       SPI_enableFIFO(SPIA_BASE);
       SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
       SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
       SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX1, SPI_FIFO_RX1);
       SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF);
       SPI_enableInterrupt(SPIA_BASE, SPI_INT_TXFF);

       //
       // Configuration complete. Enable the module.
       //
       SPI_enableModule(SPIA_BASE);

       //Interrupt_register(INT_SPIA_RX, &spiRxFIFOISR);
       //Interrupt_enable(INT_SPIA_RX);

}
