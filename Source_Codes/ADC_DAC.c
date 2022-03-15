// Start of File
#include "F28x_Project.h"             // Device Header File and Examples
#include "Initialization_Defines.h"

unsigned int SOC_Select;
unsigned int Channel_Select;
unsigned int Acquisition_Period;
unsigned int Trigger_Select;

// Configuration of Timer 0
void Initialize_CPU_Timer_0()
{
    CpuTimer0Regs.PRD.bit.LSW = CPU_Timer_0_Sampling_Time;              // Set Period to 50us (Use Lower 16bits)
    CpuTimer0Regs.TIM.bit.LSW = ENABLE;                                      // Enable Timer (Lower 16 Bits)
    CpuTimer0Regs.TCR.bit.TIE = ENABLE;                                      // Enable CPU Timer 0 (Send Interrupt Request Timer at Timer = 0)
}

// Configuration of Timer 1
void Initialize_CPU_Timer_1()
{
    EALLOW;
    CpuTimer1Regs.PRD.bit.LSW  = CPU_Timer_1_Sampling_Time;             // Set Period to 50us (Use Lower 16bits)
    CpuTimer1Regs.TCR.bit.TIE  = ENABLE;                                     // Enable CPU Timer 1 (Send Interrupt Request Timer at Timer = 0)
    CpuTimer1Regs.TCR.bit.FREE = ENABLE;                                     // Free Run
    EDIS;
}

// Initialization of ADC B
void Setup_ADC_A(SOC_Select, Channel_Select, Acquisition_Period, Trigger_Select)
{
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = ENABLE;                                  // ADC_B Clock Enable
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;                                  // ADCCLK = Input Clock/4

    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  // Set ADC_B Resolution to 12 Bit & Single Signal Mode

    // AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ  = 1;                                 // All Analog Circuitry Inside Core of ADC_B is Powered Up

    DELAY_US(1000);                                                     // Delay for 1000us (1ms) to Allow ADC to Power Up

    switch(SOC_Select)
    {
        case 0:  AdcaRegs.ADCSOC0CTL.bit.ACQPS    = Acquisition_Period; //Sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC0CTL.bit.CHSEL    = Channel_Select;     //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC0CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 1:  AdcaRegs.ADCSOC1CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC1CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC1CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 2:  AdcaRegs.ADCSOC2CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC2CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC2CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 3:  AdcaRegs.ADCSOC3CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC3CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC3CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 4:  AdcaRegs.ADCSOC4CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC4CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC4CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 5:  AdcaRegs.ADCSOC5CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC5CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC5CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 6:  AdcaRegs.ADCSOC6CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC6CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC6CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 7:  AdcaRegs.ADCSOC7CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC7CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC7CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 8:  AdcaRegs.ADCSOC8CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC8CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC8CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 9:  AdcaRegs.ADCSOC9CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC9CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC9CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 10: AdcaRegs.ADCSOC10CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC10CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC10CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 11: AdcaRegs.ADCSOC11CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC11CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC11CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 12: AdcaRegs.ADCSOC12CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC12CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC12CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 13: AdcaRegs.ADCSOC13CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC13CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC13CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 14: AdcaRegs.ADCSOC14CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC14CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 15: AdcaRegs.ADCSOC15CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcaRegs.ADCSOC15CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        default: break;
    }
    EDIS;
}

// Initialization of ADC B
void Setup_ADC_B(SOC_Select, Channel_Select, Acquisition_Period, Trigger_Select)
{
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_B = ENABLE;                                  // ADC_B Clock Enable
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6;                                  // ADCCLK = Input Clock/4

    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  // Set ADC_B Resolution to 12 Bit & Single Signal Mode

    // AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ  = 1;                                 // All Analog Circuitry Inside Core of ADC_B is Powered Up

    DELAY_US(1000);                                                     // Delay for 1000us (1ms) to Allow ADC to Power Up

    switch(SOC_Select)
    {
        case 0:  AdcbRegs.ADCSOC0CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC0CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC0CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 1:  AdcbRegs.ADCSOC1CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC1CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC1CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 2:  AdcbRegs.ADCSOC2CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC2CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC2CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 3:  AdcbRegs.ADCSOC3CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC3CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC3CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 4:  AdcbRegs.ADCSOC4CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC4CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC4CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 5:  AdcbRegs.ADCSOC5CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC5CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC5CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 6:  AdcbRegs.ADCSOC6CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC6CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC6CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 7:  AdcbRegs.ADCSOC7CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC7CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC7CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 8:  AdcbRegs.ADCSOC8CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC8CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC8CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 9:  AdcbRegs.ADCSOC9CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC9CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC9CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 10: AdcbRegs.ADCSOC10CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC10CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC10CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 11: AdcbRegs.ADCSOC11CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC11CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC11CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 12: AdcbRegs.ADCSOC12CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC12CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC12CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 13: AdcbRegs.ADCSOC13CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC13CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC13CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 14: AdcbRegs.ADCSOC14CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC14CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC14CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 15: AdcbRegs.ADCSOC15CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcbRegs.ADCSOC15CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcbRegs.ADCSOC15CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        default: break;
    }
    EDIS;
}

// Initialization of ADC D
void Setup_ADC_D(SOC_Select, Channel_Select, Acquisition_Period, Trigger_Select)
{
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_D = ENABLE;                                  // ADC_D Clock Enable

    AdcdRegs.ADCCTL2.bit.PRESCALE = 6;                                  // ADCCLK = Input Clock/4

    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  // Set ADC_D Resolution to 12 Bit & Single Signal Mode

    AdcdRegs.ADCCTL1.bit.ADCPWDNZ  = 1;                                 // All Analog Circuitry Inside Core of ADC_D is Powered Up

    DELAY_US(1000);                                                     // Delay for 1000us (1ms) to Allow ADC to Power Up

    switch(SOC_Select)
    {
        case 0:  AdcdRegs.ADCSOC0CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC0CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC0CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 1:  AdcdRegs.ADCSOC1CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC1CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC1CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 2:  AdcdRegs.ADCSOC2CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC2CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC2CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 3:  AdcdRegs.ADCSOC3CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC3CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC3CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 4:  AdcdRegs.ADCSOC4CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC4CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC4CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 5:  AdcdRegs.ADCSOC5CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC5CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC5CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 6:  AdcdRegs.ADCSOC6CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC6CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC6CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 7:  AdcdRegs.ADCSOC7CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC7CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC7CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 8:  AdcdRegs.ADCSOC8CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC8CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC8CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 9:  AdcdRegs.ADCSOC9CTL.bit.ACQPS    = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC9CTL.bit.CHSEL    = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC9CTL.bit.TRIGSEL  = Trigger_Select;
                 break;
        case 10: AdcdRegs.ADCSOC10CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC10CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC10CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 11: AdcdRegs.ADCSOC11CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC11CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC11CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 12: AdcdRegs.ADCSOC12CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC12CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC12CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 13: AdcdRegs.ADCSOC13CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC13CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC13CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 14: AdcdRegs.ADCSOC14CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC14CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC14CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        case 15: AdcdRegs.ADCSOC15CTL.bit.ACQPS   = Acquisition_Period;               //sample window is 100 SYSCLK cycles
                 AdcdRegs.ADCSOC15CTL.bit.CHSEL   = Channel_Select;                   //SOC0 will convert pin A0
                 AdcdRegs.ADCSOC15CTL.bit.TRIGSEL = Trigger_Select;
                 break;
        default: break;
    }
    EDIS;
}
