// Sourjya Mondal

// Start of File
#include "F28x_Project.h"                                            // Device Header File and Examples
#include <stdint.h>                                                  // Include Standard Integer File
#include <stdbool.h>                                                 // Include Standard Boolean File
#include <stdio.h>                                                   // Include Standard Input/Output File
#include <file.h>                                                    // Include Standard Header File
#include "math.h"                                                    // Include Math Header File
#include "Initialization_Defines.h"

void Device_Initialization();
void EPWM_Comparators();
void Disable_Error();
void Parameter_Reset();
// Define CPU Timer 0 Function
void Initialize_CPU_Timer_0();                                          // Define CPU Timer 0 Function
void Initialize_CPU_Timer_1();
//
// Define PFSB Functions
void PSFB_EPWM();                                                    // Define Function Used to Generate PWM for First Stage Converter
void PSFB_Close_Loop();
void PSFB_Param_Init();
void PSFB_Voltage_Loop_Reset();
void PSFB_Current_Loop_Reset();
//
// Define Inverter Functions
void Inverter_EPWM();
void Inverter_Param_Init();
void Inverter_Voltage_Loop_Reset();
void Inverter_Current_Loop_Reset();
//
// Define ADC & DAC Functions for PSFB
void Setup_ADC_A();                                                   // Define ADC Function
void Setup_ADC_B();                                                   // Define ADC Function
void Setup_ADC_C();                                                   // Define ADC Function
void Setup_ADC_D();                                                    // Define ADC Function
//
// Define PSFB Interrupts
__interrupt void PSFB_EPWM_Compare_ISR();                            // Define Interrupt Function for EPWM1 & EPWM2
__interrupt void Inverter_EPWM_Compare_ISR();

//
bool Initial_Condition = true;

void main()
{
    // Initialize System Control (PLL & WatchDog) and enable Peripheral Clocks.
    InitSysCtrl();
    // Initialize GPIO
    InitGpio();
    // Initialize EPWM GPIO
    InitEPwmGpio();

    // Clear all __interrupts and initialize PIE vector table:
    DINT;

    // Initialize the PIE control registers to their default state.
    InitPieCtrl();

    // Disable CPU __interrupts and clear all CPU __interrupt flags:
    IER = 0x0000;                                               // Disable CPU interrupts
    IFR = 0x0000;                                               // Clear all CPU interrupt flags

    // Initialize the PIE vector table with pointers to the shell Interrupt.
    InitPieVectTable();                                         // Call Function to Initialize PIE Vector Table

    Parameter_Reset();
    Device_Initialization();

    PSFB_EPWM();
    PSFB_Param_Init();

    Inverter_EPWM();

    // Step 5. Enable interrupts:
    EINT;                                                       // Enable Global interrupt INTM
    ERTM;                                                       // Enable Global Real Time Interrupt DBGM

    // Infinite Loop
    while(true)
    {
        while(Initial_Condition == false)
        {
            PSFB_Close_Loop();
        }
    }
}

void Device_Initialization()
{
    // Configure CPU Timer 0
    Initialize_CPU_Timer_0();                                   // Call Function to Initialize CPU Timer 0
    Initialize_CPU_Timer_1();                                   // Call Function to Initialize CPU Timer 1

    // Configure the ADC channels
    Setup_ADC_A(SOC_00, ADC_CHANNEL_2, ACQ_PRD, Trig_CPU_Tx01); // ADC for Inverter Output Voltage V_RN
    Setup_ADC_A(SOC_01, ADC_CHANNEL_3, ACQ_PRD, Trig_CPU_Tx01); // ADC for Inverter Output Voltage V_YN
    Setup_ADC_A(SOC_02, ADC_CHANNEL_4, ACQ_PRD, Trig_CPU_Tx01); // ADC for Inverter Output Voltage V_BN
    Setup_ADC_B(SOC_00, ADC_CHANNEL_0, ACQ_PRD, Trig_CPU_Tx00); // ADC for 24V DC Link Voltage
    Setup_ADC_B(SOC_01, ADC_CHANNEL_2, ACQ_PRD, Trig_CPU_Tx00); // ADC for 24V DC Link Current
    Setup_ADC_D(SOC_00, ADC_CHANNEL_0, ACQ_PRD, Trig_CPU_Tx00); // ADC for Supply Voltage

    // Configure Interrupts for EPWM
    EPWM_Comparators();
    // Set Fill Terminal to High
    Disable_Error();
}

void EPWM_Comparators()
{
    // Enable global Interrupts and higher priority real-time debug events
    EALLOW;
    IER |= M_INT1; // Enable Group 1 Interrupt
    IER |= M_INT2; // Enable Group 2 Interrupt
    IER |= M_INT3; // Enable Group 3 Interrupt
    EDIS;

    // Enable PSFB Interrupts
    EALLOW;
    PieVectTable.EPWM7_INT        = &PSFB_EPWM_Compare_ISR;     // Introduce EPWM7 Interrupt for EPWM7
    PieCtrlRegs.PIEIER3.bit.INTx7 = ENABLE;                     // Enable PIE Group 7
    EDIS;

    // Enable Inverter Interrupts
    EALLOW;
    PieVectTable.EPWM1_INT        = &Inverter_EPWM_Compare_ISR; // Introduce EPWM6 Interrupt for EPWM6
    PieCtrlRegs.PIEIER3.bit.INTx1 = ENABLE;                     // Enable PIE Group 6
    EDIS;
}

void Disable_Error()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = GPIO_UNLOCK;              // Select GPIO62 as a GPIO pin
    GpioCtrlRegs.GPADIR.bit.GPIO20  = GPIO_OUTPUT;
    GpioCtrlRegs.GPAPUD.bit.GPIO20  = GPIO_PULLUP;
    GpioDataRegs.GPASET.bit.GPIO20  = GPYSET;
    EDIS;
}

void Parameter_Reset()
{
    PSFB_Voltage_Loop_Reset();
    PSFB_Current_Loop_Reset();
    Inverter_Voltage_Loop_Reset();
//    Inverter_Current_Loop_Reset();
}
// End of File
