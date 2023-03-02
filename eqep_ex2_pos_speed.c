//
// Included Files
//
#include "modules.h"
#include "socket.h"

//
// Defines
//
#define SAMPLES 3
#define BUFSIZE 1300


//
// Global variables
//
bool     m_state = false;
uint32_t targetCount = SAMPLES;
uint8_t  Val[BUFSIZE];
int      pointer = 0;

//
// Constants
//
const uint8_t Mac[6] = { 0xBE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
const uint8_t IP[4] = { 10, 1, 0, 67}; //ip address
const uint8_t GW[4] = { 10, 1, 0, 1}; //gateway address
const uint8_t SUB[4] = { 255, 255, 255, 0}; //sub mask
const uint8_t IPDest[4] = { 10, 1, 0, 181}; //ip address
uint8_t res[6] = { 0,0,0,0,0,0 }; //ip address

//
// Function Prototypes
//
__interrupt void EQEPCompare(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    //pins configurations
    //
    initGPIOpins();

    //
    //SPI Initialization
    //
    configureSpiGPIOs();
    configureSPI();

    //
    //W5500 init
    //
    setSn_TXBUF_SIZE(0,16);
    int s = getSn_TxMAX(0);

    WIZCHIP_WRITE_BUF(SHAR, (uint8_t*)&Mac[0], 6);
    WIZCHIP_READ_BUF(SHAR, res, 6);

    WIZCHIP_WRITE_BUF(GAR, (uint8_t*)&GW[0], 4);
    WIZCHIP_READ_BUF(GAR, res, 4);

    //setSUBR(SUB);
    WIZCHIP_WRITE_BUF(SUBR, (uint8_t*)&SUB[0], 4);
    WIZCHIP_READ_BUF(SUBR, res, 4);

    WIZCHIP_WRITE_BUF(SIPR, (uint8_t*)&IP[0], 4);
    WIZCHIP_READ_BUF(SIPR, res, 4);

    int8_t err = socket(0, Sn_MR_TCP, 13000, 0);
    int8_t err2 = connect( 0, (uint8_t*)&IPDest[0], 13000);

    //
    // Setup eQEP1, configuring the unit timer and quadrature capture units
    //
    initEQEP1();
    initEQEP2();
    //initEPWM();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    //ISRs for EQEP
    //
    Interrupt_register(INT_EQEP1 ,&EQEPCompare);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    EQEP_enableInterrupt(EQEP1_BASE, EQEP_INT_POS_COMP_MATCH);
    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_EQEP1);



    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    uint8_t sock=0;
    while(1)
    {
        if(m_state)
        {
            m_state = false;
            send(sock, (uint8_t *) &Val[0], BUFSIZE);
        }
    }
}

//
// EQEP ISR function
//

__interrupt void EQEPCompare(void)
{
    int32_t val = EQEP_GetCounts();

    Val[pointer + 0] = (val & 0xFF);
    Val[pointer + 1] = ((val>>8) & 0xFF);
    Val[pointer + 2] = ((val>>16) & 0xFF);
    Val[pointer + 3] = ((val>>24) & 0xFF);
    pointer+=4;

    if(pointer==BUFSIZE)
    {
        pointer = 0;
        m_state = true;
    }

    targetCount += SAMPLES;
    EQEP_SetCompareValue(targetCount);

    HWREGH(EQEP1_BASE + EQEP_O_QCLR) = EQEP_INT_POS_COMP_MATCH;
    HWREGH(EQEP1_BASE + EQEP_O_QCLR) = EQEP_INT_GLOBAL;
    HWREGH(PIECTRL_BASE + PIE_O_ACK) = INTERRUPT_ACK_GROUP5;
}
