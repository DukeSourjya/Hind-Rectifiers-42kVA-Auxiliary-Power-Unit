// Start of File
#include "F28x_Project.h"                                       // Device Header File and Examples
#include "math.h"
#include "Maths_Constants.h"
#include "Common_Variables.h"
#include "Inverter_Variables.h"

void Space_Vector_Modulation(unsigned int* Switching_Time_Rphase, unsigned int* Switching_Time_Yphase, unsigned int* Switching_Time_Bphase);
void Inverter_Voltage_Control_Loop();

void Inverter_EPWM()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Disable TBCLK within the ePWM.
    EDIS;

    EALLOW;
    // Generate EPWM4A and EPWM4B
    // Time Base Period Register
    (*ePWM[R_Phase]).TBPRD = Inverter_Carrier_Period; // Time Period
    // Time Base Control Register
    (*ePWM[R_Phase]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Up-Down Count Mode
    (*ePWM[R_Phase]).TBCTL.bit.CLKDIV = TB_DIV1;                  // Divide by 1
    (*ePWM[R_Phase]).TBCTL.bit.HSPCLKDIV = TB_DIV1;               // Divide by 1
    // Action Qualifier Control Register For Output A
    (*ePWM[R_Phase]).AQCTLA.bit.CAD = AQ_SET; // Set at Down Count when CTR = CMPA
    (*ePWM[R_Phase]).AQCTLA.bit.CAU = AQ_CLEAR; // Clear at Up Count when CTR = CMPA
    // Dead-Band Generator Control Register
    (*ePWM[R_Phase]).DBCTL.bit.OUT_MODE = DBB_ENABLE;        // Enable Dead-Band
    (*ePWM[R_Phase]).DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active High Complementary
    // Dead-Band Generator Falling Edge Delay Count Register
    (*ePWM[R_Phase]).DBFED.all = Inverter_Deadband; // FED = 400 3.33 uS Dead-Band
    // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    (*ePWM[R_Phase]).DBRED.all = Inverter_Deadband; // RED = 400 3.33 uS Dead-Band
    // Counter Compare Control Register
    (*ePWM[R_Phase]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;     // Load on CTR = PRD
    // Event Trigger Selection Register
    (*ePWM[R_Phase]).ETSEL.bit.INTEN = ET_CTR_ZERO; // Enable EPWM Interrupt Generation
    (*ePWM[R_Phase]).ETSEL.bit.INTSEL = ET_CTR_PRDZERO; // Enable Event when CTR = ZRO or CTR = PRD
    // Event Trigger Pre-Scale Register
    (*ePWM[R_Phase]).ETPS.bit.INTPRD = ET_1ST; // Generate Interrupt On First Event
    EDIS;

    EALLOW;
    //Generate EPWM5A and EPWM5B
    // Time Base Period Register
    (*ePWM[Y_Phase]).TBPRD = Inverter_Carrier_Period; // Time Period 12500
    // Time Base Control Register
    (*ePWM[Y_Phase]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Up-Down Count Mode
    (*ePWM[Y_Phase]).TBCTL.bit.CLKDIV = TB_DIV1;                  // Divide by 1
    (*ePWM[Y_Phase]).TBCTL.bit.HSPCLKDIV = TB_DIV1;               // Divide by 1
    // Action Qualifier Control Register For Output A
    (*ePWM[Y_Phase]).AQCTLA.bit.CAD = AQ_SET; // Set at Down Count when CTR = CMPA
    (*ePWM[Y_Phase]).AQCTLA.bit.CAU = AQ_CLEAR; // Clear at Up Count when CTR = CMPA
    // Dead-Band Generator Control Register
    (*ePWM[Y_Phase]).DBCTL.bit.OUT_MODE = DBB_ENABLE;        // Enable Dead-Band
    (*ePWM[Y_Phase]).DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active High Complementary
    // Dead-Band Generator Falling Edge Delay Count Register
    (*ePWM[Y_Phase]).DBFED.all = Inverter_Deadband; // FED = 400 3.33 uS Dead Band
    // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    (*ePWM[Y_Phase]).DBRED.all = Inverter_Deadband; // RED = 400 3.33 uS Dead Band
    // Counter Compare Control Register
    (*ePWM[Y_Phase]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;     // Load on CTR = PRD
    // Event Trigger Selection Register
    (*ePWM[Y_Phase]).ETSEL.bit.INTEN = ET_CTR_ZERO; // Enable EPWM Interrupt Generation
    (*ePWM[Y_Phase]).ETSEL.bit.INTSEL = ET_CTR_PRDZERO; // Enable Event when CTR = ZRO or CTR = PRD
    // Event Trigger Pre-Scale Register
    (*ePWM[Y_Phase]).ETPS.bit.INTPRD = ET_1ST; // Generate Interrupt on First Event
    EDIS;

    EALLOW;
    //Generate EPWM6A and EPWM6B
    // Time Base Period Register
    (*ePWM[B_Phase]).TBPRD = Inverter_Carrier_Period; // Time Period 12500
    // Time Base Control Register
    (*ePWM[B_Phase]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Up-Down Count Mode
    (*ePWM[B_Phase]).TBCTL.bit.CLKDIV = TB_DIV1;            // Divide by 2^0 = 1
    (*ePWM[B_Phase]).TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Divide by 2^0 = 1
    // Action Qualifier Control Register For Output A
    (*ePWM[B_Phase]).AQCTLA.bit.CAD = AQ_SET; // Set at Down Count when CTR = CMPA
    (*ePWM[B_Phase]).AQCTLA.bit.CAU = AQ_CLEAR; // Clear at Up Count when CTR = CMPA
    // Dead-Band Generator Control Register
    (*ePWM[B_Phase]).DBCTL.bit.OUT_MODE = DBB_ENABLE;        // Enable Dead-Band
    (*ePWM[B_Phase]).DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active High Complementary
    // Dead-Band Generator Falling Edge Delay Count Register
    (*ePWM[B_Phase]).DBFED.all = Inverter_Deadband; // FED = 400 3.33 uS Dead Band
    // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    (*ePWM[B_Phase]).DBRED.all = Inverter_Deadband; // RED = 400 3.33 uS Dead Band
    // Counter Compare Control Register
    (*ePWM[B_Phase]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;     // Load on CTR = PRD
    // Event Trigger Selection Register
    (*ePWM[B_Phase]).ETSEL.bit.INTEN = ET_CTR_ZERO; // Enable EPWM Interrupt Generation
    (*ePWM[B_Phase]).ETSEL.bit.INTSEL = ET_CTR_PRDZERO; // Enable Event when CTR = ZRO or CTR = PRD
    // Event Trigger Pre-Scale Register
    (*ePWM[B_Phase]).ETPS.bit.INTPRD = ET_1ST; // Generate Interrupt on First Event
    EDIS;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;      // Disable TBCLK within the ePWM.
    EDIS;
}

// Interrupt for EPWM4
__interrupt void Inverter_EPWM_Compare_ISR()
{
    Space_Vector_Modulation(&R_Phase_Width, &Y_Phase_Width, &B_Phase_Width);

    EALLOW;
    // Counter Compare A
    (*ePWM[R_Phase]).CMPA.bit.CMPA = (R_Phase_Width * Modulating_Wave_Scale) + Modulating_Wave_Offset;         // Load Counter Compare A Register
    (*ePWM[Y_Phase]).CMPA.bit.CMPA = (Y_Phase_Width * Modulating_Wave_Scale) + Modulating_Wave_Offset;         // Load Counter Compare A Register
    (*ePWM[B_Phase]).CMPA.bit.CMPA = (B_Phase_Width * Modulating_Wave_Scale) + Modulating_Wave_Offset;         // Load Counter Compare A Register
    // Event Trigger Clear Register
    (*ePWM[R_Phase]).ETCLR.bit.INT = (*ePWM[R_Phase]).ETFLG.bit.INT; // Clear Flag Bit
    // Interrupt Acknowledgment
    PieCtrlRegs.PIEACK.bit.ACK3 = Flag_Clear;     // Acknowledge EPWM4 Interrupt
    EDIS;
}

void Space_Vector_Modulation(unsigned int* Switching_Time_Rphase, unsigned int* Switching_Time_Yphase, unsigned int* Switching_Time_Bphase)
{
    // Iterate frequency * time
    // Generate Sawtooth Signal Equivalent to f*t (Where F = 50Hertz)
    Frequency_x_Time = (Frequency_x_Time < (Frequency_x_Time_Max / Frequency_Factor)) ? (Frequency_x_Time + Frequency_x_Time_Step) : Frequency_x_Time_Min;
    if (Inverter_Initial_Condition == true)
    {
        Frequency_Factor = Frequency_Factor + Inverter_Soft_Start_Step;
        Inv_SVM.Direct = Inv_SVM.Direct + Inverter_Soft_Start_Step;
        Inv_SVM.Quadrature = 0;
        Inverter_Initial_Condition = (Frequency_Factor <= 1) ? true : false;
        Frequency_Factor = (Inverter_Initial_Condition == false) ? 1 : Frequency_Factor;
    }
    else
    {
        Inv_SVM.Direct      = 0.95;
        Inv_SVM.Quadrature  = 0;
//        Inverter_Voltage_Control_Loop();
    }

    Inv_SVM.Theta = Two_Pi * Frequency_x_Time * Frequency_Factor;

    // Generate Sine Wave and Cosine Wave
    Inv_SVM.Sin_Theta = sin(Inv_SVM.Theta);
    Inv_SVM.Cos_Theta = cos(Inv_SVM.Theta);

    // Inverse park Transform
    Inv_SVM.Alpha = (Inv_SVM.Direct     * Inv_SVM.Cos_Theta) - (Inv_SVM.Quadrature * Inv_SVM.Sin_Theta);
    Inv_SVM.Beta  = (Inv_SVM.Quadrature * Inv_SVM.Cos_Theta) + (Inv_SVM.Direct     * Inv_SVM.Sin_Theta);

    // Magnitude and Angle
    Inv_PWM.Magnitude = abs(sqrt((Inv_SVM.Alpha * Inv_SVM.Alpha)+ (Inv_SVM.Beta * Inv_SVM.Beta)));
    Inv_PWM.Gamma = atan2(Inv_SVM.Beta, Inv_SVM.Alpha);

    // Sector Determination
    if ((Inv_PWM.Gamma > Zero) && (Inv_PWM.Gamma <= Sixty))
        Inv_PWM.Sector = 1;
    else if ((Inv_PWM.Gamma > Sixty) && (Inv_PWM.Gamma <= One_Twenty))
        Inv_PWM.Sector = 2;
    else if ((Inv_PWM.Gamma > One_Twenty) && (Inv_PWM.Gamma <= One_Eighty))
        Inv_PWM.Sector = 3;
    else if ((Inv_PWM.Gamma > Minus_One_Eighty)
            && (Inv_PWM.Gamma <= Minus_One_Twenty))
        Inv_PWM.Sector = 4;
    else if ((Inv_PWM.Gamma > Minus_One_Twenty)
            && (Inv_PWM.Gamma <= Minus_Sixty))
        Inv_PWM.Sector = 5;
    else if ((Inv_PWM.Gamma > Minus_Sixty) && (Inv_PWM.Gamma <= Zero))
        Inv_PWM.Sector = 6;
    else
        Inv_PWM.Sector = Inv_PWM.Sector;

    Inv_PWM.Angle_Vector_1     = Pi_By_Three   - (Inv_PWM.Gamma - ((Inv_PWM.Sector - 1) * Pi_By_Three));
    Inv_PWM.Angle_Vector_2     = Inv_PWM.Gamma - ((Inv_PWM.Sector - 1) * Pi_By_Three);
    Inv_PWM.Sin_Theta_Vector_1 = sin(Inv_PWM.Angle_Vector_1);
    Inv_PWM.Sin_Theta_Vector_2 = sin(Inv_PWM.Angle_Vector_2);

//    Inv_PWM.Modulation_Index = Root_Three * Inv_PWM.Magnitude * Vdc;

    Inv_PWM.Time_Vector_1 = Inv_PWM.Modulation_Index * Inv_PWM.Sin_Theta_Vector_1;
    Inv_PWM.Time_Vector_2 = Inv_PWM.Modulation_Index * Inv_PWM.Sin_Theta_Vector_2;
    Inv_PWM.Time_Vector_0 = Half * (1 - (Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2));

    // Switching States Evaluation
    switch (Sector)
    {
    case 1:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_0;
        break;
    case 2:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_0;
        break;
    case 3:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        break;
    case 4:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        break;
    case 5:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        break;
    case 6:
        Inv_PWM.Time_R_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_2 + Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_Y_Phase = Inv_PWM.Time_Vector_0;
        Inv_PWM.Time_B_Phase = Inv_PWM.Time_Vector_1 + Inv_PWM.Time_Vector_0;
        break;
    default:
        break;
    }

    *Switching_Time_Rphase = Inv_PWM.Time_R_Phase;
    *Switching_Time_Yphase = Inv_PWM.Time_Y_Phase;
    *Switching_Time_Bphase = Inv_PWM.Time_B_Phase;
}

// Inverter Voltage Control Loop (PI)
void Inverter_Voltage_Control_Loop()
{

    //                                             _________     _________
    //                                            |         |   |         |
    //                                V_ref (1)-->|+        |   |    P    |
    // Theta--------------------------,           |         |-->|         |--,
    //                                |       ,-->|-        |   |  Kp=0.1 |  |
    //              _________     ____V____   |   |_________|   |_________|  |    _________     _________
    //             |         |   |         |  |                              |   |         |   |         |
    // VfbRphase-->|R   Alpha|-->|Alpha   D|--'                              `-->|D   Alpha|-->|Alpha   R|-->VoutRphase
    //             |         |   |         |                                     |         |   |        Y|-->VoutYphase
    // VfbYphase-->|Y    Beta|-->|Beta    Q|--,                              ,-->|Q    Beta|-->|Beta    B|-->VoutBphase
    //             |_________|   |_________|  |    _________     _________   |   |_________|   |_________|
    //                                        |   |         |   |         |  |
    //                                        `-->|-        |   |    P    |  |
    //                                            |         |-->|         |--'
    //                            Phase_ref (0)-->|+        |   | Kp=0.05 |
    //                                            |_________|   |_________|

    Inv_Volt_Feed.R_Phase_Value = Unity_Scaling * (AdcaResultRegs.ADCRESULT0 - ADC_Offset); // Scale it within Unity and Remove Offset
    Inv_Volt_Feed.Y_Phase_Value = Unity_Scaling * (AdcaResultRegs.ADCRESULT1 - ADC_Offset); // Scale it within Unity and Remove Offset
    Inv_Volt_Feed.B_Phase_Value = Unity_Scaling * (AdcaResultRegs.ADCRESULT2 - ADC_Offset); // Scale it within Unity and Remove Offset
    // Clarke Transformation
    Inv_Volt_Feed.Alpha = Inv_Volt_Feed.R_Phase_Value;          // Compute Alpha
    Inv_Volt_Feed.Beta = (One_By_Root_Three * Inv_Volt_Feed.R_Phase_Value) + (Two_By_Root_Three * Inv_Volt_Feed.Y_Phase_Value); // Compute Beta
    // Park Transformation
    Inv_Volt_Feed.Sin_Theta = sin(Inv_SVM.Theta);     // Calculate Sine of Theta
    Inv_Volt_Feed.Cos_Theta = cos(Inv_SVM.Theta);      // Calculate Cos of Theta
    Inv_Volt_Feed.Direct = fabs((Inv_Volt_Feed.Alpha * Inv_Volt_Feed.Cos_Theta) + (Inv_Volt_Feed.Beta * Inv_Volt_Feed.Sin_Theta)); // Compute D
    Inv_Volt_Feed.Quadrature = fabs(-(Inv_Volt_Feed.Alpha * Inv_Volt_Feed.Sin_Theta) + (Inv_Volt_Feed.Beta * Inv_Volt_Feed.Cos_Theta)); // Compute Q

    // Magnitude Control Looop
    // Evaluate Error (Magnitude)
    Inv_Volt.Fbk_Err = Inv_Volt.Ref - Inv_Volt_Feed.Direct; // Calculate Error Input
    // Evaluation of Proportional Path (Magnitude)
    Inv_Volt.Fbk_Proportional = Inv_Volt.Kp * Inv_Volt.Fbk_Err;   // Calculate P
    // Evaluation of Integral Path (Magnitude)
    Inv_Volt.Fbk_Integral = Inv_Volt.Fbk_Prev_Integral + Inv_Volt.Ki * Inv_Volt.Fbk_Err;                     // Calculate I
            // Integral Path Clamp (Magnitude)
    Inv_Volt.Fbk_Integral = (Inv_Volt.Fbk_Integral > Vout_Pi_Max) ? Vout_Pi_Max : Inv_Volt.Fbk_Integral;    // Upper Limit Clamp
    Inv_Volt.Fbk_Integral = (Inv_Volt.Fbk_Integral < Vout_Pi_Min) ? Vout_Pi_Min : Inv_Volt.Fbk_Integral;    // Lower Limit Clamp
    // Store Value for Next Cycle
    Inv_Volt.Fbk_Prev_Integral = Inv_Volt.Fbk_Integral; // Update Previous Value of I
    // PI Output (Magnitude)
    Inv_Volt.PI_Out = Inv_Volt.Fbk_Proportional + Inv_Volt.Fbk_Integral; // PI with Both Proportional & Integral Paths
    // PI Output Clamp (Magnitude)
    Inv_Volt.PI_Out = (Inv_Volt.PI_Out > Vout_Pi_Max) ? Vout_Pi_Max : Inv_Volt.PI_Out; // Upper Limit Clamp
    Inv_Volt.PI_Out = (Inv_Volt.PI_Out < Vout_Pi_Min) ? Vout_Pi_Min : Inv_Volt.PI_Out; // Lower Limit Clamp

    // Phase Control Loop
    // Evaluate Error (Phase)
    Inv_Phase.Fbk_Err = Inv_Phase.Ref - Inv_Volt_Feed.Quadrature; // Calculate Error Input
    // Evaluation of Proportional Path (Phase)
    Inv_Phase.Fbk_Proportional = Inv_Phase.Kp * Inv_Phase.Fbk_Err; // Calculate P
    // Evaluation of Integral Path (Phase)
    Inv_Phase.Fbk_Integral = Inv_Phase.Fbk_Prev_Integral + Inv_Phase.Ki * Inv_Phase.Fbk_Err;                   // Calculate I
    Inv_Phase.Fbk_Prev_Integral = Inv_Phase.Fbk_Integral;   // Update Previous I
    // PI Output (Phase)
    Inv_Phase.PI_Out = Inv_Phase.Fbk_Proportional + Inv_Phase.Fbk_Integral; // PI with Both Proportional & Integral Paths
    // PI Output Clamp (Phase)
    Inv_Phase.PI_Out = (Inv_Phase.PI_Out > Vout_Pi_Max) ? Vout_Pi_Max : Inv_Phase.PI_Out; // Upper Limit Clamp
    Inv_Phase.PI_Out = (Inv_Phase.PI_Out < Vout_Pi_Min) ? Vout_Pi_Min : Inv_Phase.PI_Out; // Lower Limit Clamp

    // Feed PI Outputs
    Inv_SVM.Direct = Inv_Volt.PI_Out;                                  // Load D
    Inv_SVM.Quadrature = Inv_Phase.PI_Out;                             // Load Q
}

void Inverter_Param_Init()
{
    Inv_Volt.Ref     = UNITY;
    Inv_Volt.Kp      = V_Kp_Magnitude;
    Inv_Volt.Ki      = V_Ki_Magnitude;
    Inv_Volt.PI_Max  = Vout_Pi_Max;
    Inv_Volt.PI_Min  = Vout_Pi_Min;

    Inv_Phase.Ref    = RESET;
    Inv_Phase.Kp     = V_Kp_Phase;
    Inv_Phase.Ki     = V_Ki_Phase;
    Inv_Phase.PI_Max = Vout_Pi_Max;
    Inv_Phase.PI_Min = Vout_Pi_Min;
}

void Inverter_Voltage_Loop_Reset()
{
    Inv_Volt.Fbk_Err            = RESET;
    Inv_Volt.Fbk_Proportional   = RESET;
    Inv_Volt.Fbk_Integral       = RESET;
    Inv_Volt.Fbk_Prev_Integral  = RESET;
    Inv_Volt.PI_Out             = RESET;

    Inv_Phase.Fbk_Err           = RESET;
    Inv_Phase.Fbk_Proportional  = RESET;
    Inv_Phase.Fbk_Integral      = RESET;
    Inv_Phase.Fbk_Prev_Integral = RESET;
    Inv_Phase.PI_Out            = RESET;

}

// End of File
