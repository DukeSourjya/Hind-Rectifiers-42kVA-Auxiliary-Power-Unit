// Start of File
#include "F28x_Project.h"             // Device Header File and Examples
#include "Common_Variables.h"
#include "PSFB_Variables.h"

void PSFB_Voltage_Control_Loop(unsigned int* PWMA, unsigned int* PWMB, unsigned int* Phase);
void PSFB_Current_Control_Loop(unsigned int* PWMA, unsigned int* PWMB, unsigned int* Phase);

void PSFB_EPWM()
{
    PWMxA_Width = PWMxA_Start;
    PWMxB_Width = PWMxB_Start;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = DISABLE;                 // Disable TBCLK within the ePWM.
    EDIS;

    // TBPRD(5000)___________________________________________________________________________
    //                     /\                  /\                  /\                  /\
    //                    /  \                /  \                /  \                /  \
    //                   /    \              /    \              /    \              /    \
    // CMPA(2700)_______/______\____________/______\____________/______\____________/______\_____
    //                 /|      |\          /|      |\          /|      |\          /|      |\
    // CMPB(2300)_____/_|______|_\________/_|______|_\________/_|______|_\________/_|______|_\___
    //               /| |      | |\      /| |      | |\      /| |      | |\      /| |      | |\
    //              / | |      | | \    / | |      | | \    / | |      | | \    / | |      | | \
    //             /  | |      | |  \  /  | |      | |  \  /  | |      | |  \  /  | |      | |  \
    //            /   | |      | |   \/   | |      | |   \/   | |      | |   \/   | |      | |   \
    // EPWM1A--->     | |______| |        | |______| |        | |______| |        | |______| |
    //                | |      | |        | |      | |        | |      | |        | |      | |
    //                | |      | |        | |      | |        | |      | |        | |      | |
    //             ___|_|      |_|________|_|      |_|________|_|      |_|________|_|      |_|__
    //                | |      | |        | |      | |        | |      | |        | |      | |
    // EPWM1B--->_____| |      | |________| |      | |________| |      | |________| |      | |___
    //                | |      | |        | |      | |        | |      | |        | |      | |
    //                | |      | |        | |      | |        | |      | |        | |      | |
    //                |_|______|_|        |_|______|_|        |_|______|_|        |_|______|_|
    //                | |      |            |      |            |      |            |      |
    //             -->| |<--
    //             Dead-Band
    //               (4us)

    // Configure EPWM1A & EPWM1B
    EALLOW;
    // Time Base Control Register
    (*ePWM[PSFB_Fix]).TBCTL.bit.SYNCOSEL   = TB_CTR_ZERO;         // Sync EPWM1 to Down-stream (CTR = ZRO)
    (*ePWM[PSFB_Fix]).TBCTL.bit.PHSEN      = TB_DISABLE;          // Disable Phase Offset Register
    (*ePWM[PSFB_Fix]).TBCTL.bit.PRDLD      = TB_IMMEDIATE;        // Set Immediate Load
    // Time Base Period Register
    (*ePWM[PSFB_Fix]).TBPRD                = PSFB_Carrier_Period; // Set Time Period to 5000
    // Time Base Control Register
    (*ePWM[PSFB_Fix]).TBCTL.bit.PHSDIR     = TB_UP;               // Count Up After The Synchronization Event
    // Time Base Phase Offset Register
    (*ePWM[PSFB_Fix]).TBPHS.bit.TBPHS      = RESET;               // Disable Phase Offset
    // Time Base Counter Register
    (*ePWM[PSFB_Fix]).TBCTR                = RESET;               // Enable Time Base Counter
    // Time Base Control Register
    (*ePWM[PSFB_Fix]).TBCTL.bit.HSPCLKDIV  = TB_DIV1;             // Divide Clock By 1
    (*ePWM[PSFB_Fix]).TBCTL.bit.CLKDIV     = TB_DIV1;             // Divide Clock By 1
    (*ePWM[PSFB_Fix]).TBCTL.bit.CTRMODE    = TB_COUNT_UPDOWN;     // Up-Down Count Mode
    // Counter Compare Control Register
    (*ePWM[PSFB_Fix]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;         // Load On CTR = ZRO
    (*ePWM[PSFB_Fix]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;         // Load On CTR = ZRO
    // Counter Compare A
    (*ePWM[PSFB_Fix]).CMPA.bit.CMPA        = PWMxA_Start;         // Load Counter Compare A
    // Counter Compare B
    (*ePWM[PSFB_Fix]).CMPB.bit.CMPB        = PWMxB_Start;         // Load Counter Compare A
    // Action Qualifier Control Register For Output A
    (*ePWM[PSFB_Fix]).AQCTLA.bit.CAU       = AQ_SET;              // Set at CTR = CMPA (Up Direction)
    (*ePWM[PSFB_Fix]).AQCTLA.bit.CAD       = AQ_CLEAR;            // Clear at CTR = CMPA (Down Direction)
    // Action Qualifier Control Register For Output B
    (*ePWM[PSFB_Fix]).AQCTLB.bit.CBU       = AQ_CLEAR;            // Clear at CTR = CMPB (Up Direction)
    (*ePWM[PSFB_Fix]).AQCTLB.bit.CBD       = AQ_SET;              // Set at CTR = CMPB (Down Direction)
    // Event Trigger Selection Register
    (*ePWM[PSFB_Fix]).ETSEL.bit.INTEN      = ET_CTR_ZERO;         // Enable EPWM1 Interrupt Generation
    (*ePWM[PSFB_Fix]).ETSEL.bit.INTSEL     = ET_CTR_PRDZERO;      // Enable Event when CTR = ZRO or CTR = PRD
    //***Note:
    // The Instruction Written Below Seems To Be Unnecessary
    // Check It's Utilty And If Not Required Then Delete It
    (*ePWM[PSFB_Fix]).ETSEL.bit.INTSEL     = ET_CTRU_CMPB;        // Enable Event when CTR = CMPB
    // Event Trigger Pre-Scale Register
    (*ePWM[PSFB_Fix]).ETPS.bit.INTPRD      = ET_1ST;              // Generate Interrupt on First Event
    EDIS;

    EALLOW;
    // Configure EPWM2A & EPWM2B
    (*ePWM[PSFB_Var]).TBCTL.bit.SYNCOSEL   = TB_SYNC_IN;          // Sync "flow through" mode
    (*ePWM[PSFB_Var]).TBCTL.bit.PHSEN      = TB_ENABLE;           // Enable Phase Offset Register
    (*ePWM[PSFB_Var]).TBCTL.bit.PRDLD      = TB_IMMEDIATE;        // Set Immediate Load
    // Time Base Period Register
    (*ePWM[PSFB_Var]).TBPRD                = PSFB_Carrier_Period; // Set Time Period to 5000
    // Time Base Control Register
    (*ePWM[PSFB_Var]).TBCTL.bit.PHSDIR     = TB_UP;               // Count Up After The Synchronization Event
    // Time Base Counter Register
    (*ePWM[PSFB_Var]).TBCTR                = RESET;               // Enable Time Base Counter
    // Time Base Control Register
    (*ePWM[PSFB_Var]).TBCTL.bit.HSPCLKDIV  = TB_DIV1;             // Divide Clock By 1
    (*ePWM[PSFB_Var]).TBCTL.bit.CLKDIV     = TB_DIV1;             // Divide Clock By 1
    (*ePWM[PSFB_Var]).TBCTL.bit.CTRMODE    = TB_COUNT_UPDOWN;     // Up-Down Count Mode
    // Time Base Phase Shift Register
    (*ePWM[PSFB_Var]).TBPHS.bit.TBPHS      = Phase_Shift_Max;     // Enable Phase Offset
    // Counter Compare Control Register
    (*ePWM[PSFB_Var]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;         // Load On CTR = ZRO
    (*ePWM[PSFB_Var]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;         // Load On CTR = ZRO
    // Counter Compare A
    (*ePWM[PSFB_Var]).CMPA.bit.CMPA        = PWMxA_Start;         // Load Counter Compare A
    // Counter Compare B
    (*ePWM[PSFB_Var]).CMPB.bit.CMPB        = PWMxB_Start;         // Load Counter Compare A
    // Action Qualifier Control Register For Output A
    (*ePWM[PSFB_Var]).AQCTLA.bit.CAU       = AQ_SET;              // Set at CTR = CMPA (Up Direction)
    (*ePWM[PSFB_Var]).AQCTLA.bit.CAD       = AQ_CLEAR;            // Clear at CTR = CMPA (Down Direction)
    // Action Qualifier Control Register For Output B
    (*ePWM[PSFB_Var]).AQCTLB.bit.CBU       = AQ_CLEAR;            // Clear at CTR = CMPB (Up Direction)
    (*ePWM[PSFB_Var]).AQCTLB.bit.CBD       = AQ_SET;              // Set at CTR = CMPB (Down Direction)
    // Event Trigger Selection Register
    (*ePWM[PSFB_Var]).ETSEL.bit.INTEN      = ET_CTR_ZERO;         // Enable EPWM1 Interrupt Generation
    (*ePWM[PSFB_Var]).ETSEL.bit.INTSEL     = ET_CTR_PRDZERO;      // Enable Event when CTR = ZRO or CTR = PRD
    //***Note:
    // The Instruction Written Below Seems To Be Unnecessary
    // Check It's Utilty And If Not Required Then Delete It
    (*ePWM[PSFB_Var]).ETSEL.bit.INTSEL     = ET_CTRU_CMPB;        // Enable Event when CTR = CMPB
    // Event Trigger Pre-Scale Register
    (*ePWM[PSFB_Var]).ETPS.bit.INTPRD      = ET_1ST;              // Generate Interrupt on First Event
    EDIS;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC       = ENABLE;              // Enable TBCLK within the ePWM.
    EDIS;
}

__interrupt void PSFB_EPWM_Compare_ISR()
{
//    PSFB_Close_Loop();
    if(Initial_Condition == true)
    {
        // Duty Cycle Increment for Soft Start
        Width_A = Width_A - PWM_Duty_Increment_Step;            // EPWM Top Switch Soft Start
        Width_B = Width_B + PWM_Duty_Increment_Step;            // EPWM Bottom Switch Soft Start

        PWMxA_Width = (unsigned int)(Width_A);
        PWMxB_Width = (unsigned int)(Width_B);

        // Saturate Phase Shift to its Maximum Value to Avoid Voltage Overshoot During Startup
        Phase_Shift = Phase_Shift_Max;                                  // Update Value of Phase_Shift
        // System Condition Check
        Initial_Condition = (PWMxA_Width > Half_Period_A) ? true : false;
    }

    // Counter Compare A
    (*ePWM[PSFB_Fix]).CMPA.bit.CMPA   = PWMxA_Width;           // Load Counter Compare A
    // Counter Compare B
    (*ePWM[PSFB_Fix]).CMPB.bit.CMPB   = PWMxB_Width;           // Load Counter Compare B

    // Counter Compare A
    (*ePWM[PSFB_Var]).CMPA.bit.CMPA   = PWMxA_Width;           // Load Counter Compare A
    // Counter Compare B
    (*ePWM[PSFB_Var]).CMPB.bit.CMPB   = PWMxB_Width;           // Load Counter Compare B

    // Time Base Phase Offset Register
    (*ePWM[PSFB_Var]).TBPHS.bit.TBPHS = Phase_Shift;           // Enable Phase Offset

    // EPWM1 Interrupt Acknowledgment
    PieCtrlRegs.PIEACK.bit.ACK3       = AKNOWLEDGE_INT;  // Acknowledge EPWM1 Interrupt
    // Event Trigger Clear Register
    (*ePWM[PSFB_Fix]).ETCLR.bit.INT   = FLAG_CLEAR;            // Clear Flag Bit
    (*ePWM[PSFB_Var]).ETCLR.bit.INT   = FLAG_CLEAR;            // Clear Flag Bit
}

void PSFB_Close_Loop()
{
    //                  _________
    //                 |         |
    //   Voltage       | Voltage |
    //   Feedback ---->|   Loop  |------,
    //  Parameters     |         |      |       _________
    //                 |_________|      |      |         |
    //                                  '----->|         |
    //                                         |   >=    |---->Dominant Control Loop
    //                  _________       ,----->|         |
    //                 |         |      |      |_________|
    //   Current       | Current |      |
    //   Feedback ---->|  Loop   |------'
    //  Parameters     |         |
    //                 |_________|

    if(Output_Overcurrent == true)
        PSFB_Current_Control_Loop(&PWMxA_Width, &PWMxB_Width, &Phase_Shift);
    else
        PSFB_Voltage_Control_Loop(&PWMxA_Width, &PWMxB_Width, &Phase_Shift);
}

void PSFB_Param_Init()
{
    Width_A                     = Half_Period_A;
    Width_B                     = Half_Period_B;
    PSFB_Volt.Ref               = Vref_PSFB_Feedback_Loop;
    PSFB_Volt.Kp                = Kp_Voltage_Feedback_Loop;
    PSFB_Volt.Ki                = Ki_Voltage_Feedback_Loop;
    PSFB_Volt.Ref_Fwd           = Vref_PSFB_Feedforward_Loop;
    PSFB_Volt.Kp_Fwd            = Kp_Voltage_Feedforward_Loop;
    PSFB_Volt.PI_Max            = Phase_Shift_Max;
    PSFB_Volt.PI_Min            = Phase_Shift_Min;
    PSFB_Curr.Ref               = Iref_PSFB_Feedback_Loop;
    PSFB_Curr.Kp                = Kp_Current_Feedback_Loop;
    PSFB_Curr.Ki                = Ki_Current_Feedback_Loop;
    PSFB_Curr.PI_Max            = PI_Current_Max;
    PSFB_Curr.PI_Min            = PI_Current_Min;
}

void PSFB_Voltage_Loop_Reset()
{
    PSFB_Volt.Fbk_Err           = RESET;
    PSFB_Volt.Fbk_Proportional  = RESET;
    PSFB_Volt.Fbk_Prev_Integral = RESET;
    PSFB_Volt.Fbk_Integral      = RESET;
    PSFB_Volt.Fwd_Err           = RESET;
    PSFB_Volt.Fwd_Proportional  = RESET;
}

void PSFB_Current_Loop_Reset()
{
    PSFB_Curr.Fbk_Err           = RESET;
    PSFB_Curr.Fbk_Proportional  = RESET;
    PSFB_Curr.Fbk_Prev_Integral = RESET;
    PSFB_Curr.Fbk_Integral      = RESET;
}

// PSFB Voltage Control Loop (PI)
void PSFB_Voltage_Control_Loop(unsigned int* PWMA, unsigned int* PWMB, unsigned int* Phase)
{
    PSFB_Current_Loop_Reset();
//
//                                                                                                      _________
//                                                                                                      |         |
//               _________          __________                                                          |         |                                                |         |
//              |         |        |          |                                                         |  2500   |---,     _________     _________
//  V_Input---->|-        |        |    P     |                                                         |         |   |    |         |   |  5000_  |
//              |         |------->|          |-------------------------------------,                   |_________|   `--->|+        |   |     /   |
//          ,-->|+        |        |  Kp=0.1  |                                     |                                      |         |---|   _/    |--->V_out
//          |   |_________|        |__________|                                     |      _________     _________    ,--->|-        |   |  0      |
//          |                                                                       |     |         |   |   2500_ |   |    |_________|   |_________|
//          |                                                                        `--->|+        |   |      /  |   |
//  V_ref-->|                                                                             |         |---|    _/   |---'
//          |    _________          __________                                       ,--->|+        |   |-2500    |
//          |   |         |        |          |                         _________    |    |_________|   |_________|
//          `-->|+        |        |    P     |                        |         |   |
//              |         |---+--->|          |----------------------->|+        |   |
//  V_feedback->|-        |   |    |  Kp=0.1  |                        |         |---'
//              |_________|   |    |__________|                   ,--->|+        |
//                            |     __________      __________    |    |_________|
//                            |    |          |    |          |   |
//                            |    |    I     |    |     1    |   |
//                            `--->|          |--->|    ---   |---'
//                                 | Ki=0.0 5 |    |     s    |
//                                 |__________|    |__________|

    // Generate Error Signal From DC Bus Voltage
    PSFB_Volt.Fbk_Err           = PSFB_Volt.Ref - AdcbResultRegs.ADCRESULT0;                                                         // Calculate Error Signal (From DC Bus Voltage Feedback)
    // Evaluation of Proportional Path
    PSFB_Volt.Fbk_Proportional  = PSFB_Volt.Kp * PSFB_Volt.Fbk_Err;                                                      // Calculate P (From DC Bus Voltage Feedback)
    // Evaluation of Integral Path
    PSFB_Volt.Fbk_Integral      = PSFB_Volt.Fbk_Prev_Integral + PSFB_Volt.Ki * PSFB_Volt.Fbk_Err;         // Calculate I (From DC Bus Voltage Feedback)
    PSFB_Volt.Fbk_Prev_Integral = PSFB_Volt.Fbk_Integral;                                                                              // Update Previous Value of I
//    // Generate Error Signal From System Input
//    PSFB_Volt.Fwd_Err           = PSFB_Volt.Ref_Fwd - AdcdResultRegs.ADCRESULT1;                                                         // Calculate Error Signal (From Input Voltage Feedforward)
//    // Evaluation of Proportional Path
//    PSFB_Volt.Fwd_Proportional  = PSFB_Volt.Kp_Fwd * PSFB_Volt.Fwd_Err;                                                // Calculate P (From Input Voltage Feedforward)
    // Calculate PI Value
    PSFB_Volt.PI_Out            = PSFB_Volt.Fbk_Proportional + PSFB_Volt.Fbk_Integral; // Calculate Final PI Output
//    PSFB_Volt.PI_Out            = PSFB_Volt.PI_Out + PSFB_Volt.Fwd_Proportional; // Calculate Final PI Output

    PSFB_Volt.PI_Out            = (PSFB_Volt.PI_Out >= Phase_Shift_Ninety) ? Phase_Shift_Ninety : PSFB_Volt.PI_Out;                               // PI Upper Value Clamp
    PSFB_Volt.PI_Out            = (PSFB_Volt.PI_Out <= Phase_Shift_Ninety_Negative) ? Phase_Shift_Ninety_Negative : PSFB_Volt.PI_Out;
    PSFB_Volt.PI_Out            = (unsigned int)(Phase_Shift_Ninety - PSFB_Volt.PI_Out);
    PSFB_Volt.PI_Out            = (PSFB_Volt.PI_Out >= Phase_Shift_Max) ? Phase_Shift_Max : PSFB_Volt.PI_Out;                               // PI Upper Value Clamp
    PSFB_Volt.PI_Out            = (PSFB_Volt.PI_Out <= Phase_Shift_Min) ? Phase_Shift_Min : PSFB_Volt.PI_Out;

    *Phase                      = PSFB_Volt.PI_Out;                                                                    // Calculate Phase Shift
    *PWMA                       = Half_Period_A;                              // Load Counter Compare A
    *PWMB                       = Half_Period_B;                                                                                                // Load Counter Compare B
}

void PSFB_Current_Control_Loop(unsigned int* PWMA, unsigned int* PWMB, unsigned int* Phase)
{
    PSFB_Voltage_Loop_Reset();

//                _________                 _________
//               |         |   |\          |         |                        _________
// I_feedback--->|+        |   | \         |    P    |                       |         |
//               |         |---|  \---+--->|         |---------------------->|+        |
//      I_ref--->|-        |   |  /   |    | Kp=0.001|                       |         |--->I_out
//               |_________|   | /    |    |_________|                  ,--->|+        |
//                             |/     |     _________      _________    |    |_________|
//                            Unity   |    |         |    |         |   |
//                           Scaling  |    |    I    |    |    1    |   |
//                                    `--->|         |--->|   ---   |---'
//                                         | Ki=0.005|    |    s    |
//                                         |_________|    |_________|

    // Generate Error Signal From DC Bus Current
    PSFB_Curr.Fbk_Err           = AdcbResultRegs.ADCRESULT2 - PSFB_Curr.Ref;                                                      // Calculate Error Signal (From DC Bus Current Feedback)
    // Evaluation of Proportional Path
    PSFB_Curr.Fbk_Proportional  = PSFB_Curr.Kp * PSFB_Curr.Fbk_Err;                                              // Calculate P (From DC Bus Current Fbk)
    // Evaluation of Integral Path
    PSFB_Curr.Fbk_Integral      = PSFB_Curr.Fbk_Prev_Integral + PSFB_Curr.Ki * PSFB_Curr.Fbk_Err; // Calculate I (From DC Bus Current Feedback)
    PSFB_Curr.Fbk_Prev_Integral = PSFB_Curr.Fbk_Integral;                                                           // Update Previous I
    PSFB_Curr.PI_Out            = PSFB_Curr.Fbk_Proportional + PSFB_Curr.Fbk_Integral;                              // Calculate Final PI (From DC Bus Current Feedback)
    // PI Output Clamp
    PSFB_Curr.PI_Out            = (PSFB_Curr.PI_Out >= PSFB_Curr.PI_Max) ? PSFB_Curr.PI_Max : PSFB_Curr.PI_Out;                       // PI Upper Value Clamp
    PSFB_Curr.PI_Out            = (PSFB_Curr.PI_Out <= PSFB_Curr.PI_Min) ? PSFB_Curr.PI_Min : PSFB_Curr.PI_Out;                       // PI Lower Value Clamp
    // Scale the PI Output to PWM Width
    PSFB_Curr.PI_Out            = PSFB_Curr.PI_Out * Half_Period_B;                                                                   // PI Output Scaling
    // Update Phaseshift
    *Phase                      = Phase_Shift_Max;
    // Update Pulse Width Output
    *PWMA                       = (unsigned int)(Half_Period_A + PSFB_Curr.PI_Out);                                                                   // Load Counter Compare A
    *PWMB                       = (unsigned int)(Half_Period_B - PSFB_Curr.PI_Out);
}
