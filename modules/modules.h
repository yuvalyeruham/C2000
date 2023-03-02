/*
 * modules.h
 *
 *  Created on: 23 ????? 2023
 *      Author: yuval yeruham
 */

//
// includes
//
#include "stdio.h"
#include "string.h"
#include "driverlib.h"
#include "device.h"
#include "IQmathLib.h"
#include "eqep_ex2_calculation.h"
#include "wizchip_conf.h"
#include "spi.h"

//
// Defines
//
#define TB_CLK    DEVICE_SYSCLK_FREQ / 2    // Time base clock is SYSCLK / 2
//PWM1
#define PWM_CLK   32768       // We want to output at PWM_CLK kHz                                            // (300 rpm)
#define PRD_VAL   (TB_CLK / (PWM_CLK*4))    // Calculate value period value
                                            // for up-down count mode
// .9999 / 4000 converted to IQ26 fixed point format
#define MECH_SCALER     16776
// 2 pole pairs in this example
#define POLE_PAIRS      2
// Angular offset between encoder and Phase A
#define CAL_ANGLE       0
// See Equation 5 in eqep_ex2_calculation.c
#define SPEED_SCALER    ((((uint64_t)32 * DEVICE_SYSCLK_FREQ / 64) * 60) / (24000000))
// Base/max rpm is 6000rpm
#define BASE_RPM        6000

#define RANGE           1000
#define HIGH_SPEED      4095
#define REVERSED_HIGH_SPEED 0

//
// Structures
//
/*typedef struct
{
    float    RPM;
    int32_t  BigRPM;
    int32_t  SmallRPM;
    int32_t  diviation;
    int32_t  MissCounts;
    uint32_t counter;
    uint32_t perv_counter;
    uint32_t    freq;
}SEncoderCalculation;*/


//
// Function Prototypes
//
void initEQEP1();
void initEQEP2();
void initEPWM(void);
void SetUart();
void initGPIOpins();
void configureDAC(void);
void EQEP_SetCompareValue(uint32_t value_);
uint32_t  EQEP_GetCounts(void);
uint32_t EQEP_GetCOmpareValue(void);

void configureSpiGPIOs();
void configureSPI();





