#ifndef HEADERS_INITIALIZATION_DEFINES_H_
#define HEADERS_INITIALIZATION_DEFINES_H_

//
// Status
#define RESET                           0
#define UNITY                           1
#define DISABLE                         0
#define ENABLE                          1
#define AKNOWLEDGE_INT                  1
#define FLAG_CLEAR                      1

//
// PSFB EPWM Channel Select
#define PSFB_Fix                        7
#define PSFB_Var                        8
// Essential EPWM Parameters
#define PSFB_Carrier_Period          5000
#define Half_Period_A                2700               // Half_Period_A = 0.54 * Period
#define Half_Period_B                2300              // Half_Period_B = 0.46 * Period
#define PWMxA_Start                  5000
#define PWMxB_Start                     0
#define PWM_Duty_Increment_Step         0.0001
// Voltage Control Loop Parameters
#define Phase_Shift_Max              5000
#define Phase_Shift_Ninety           2500
#define Phase_Shift_Ninety_Negative -2500
#define Phase_Shift_Min                 0              // Define Variables Used to Clamp Phase Shift Value
// Voltage Control Loop Main Parameters
#define Vref_PSFB_Feedback_Loop      3100
#define Vref_PSFB_Feedforward_Loop   2700
// Voltage Control Loop Feedback Path Parameters
//#define Kp_Voltage_Feedback_Loop        0.0001
//#define Ki_Voltage_Feedback_Loop        0.000001
#define Kp_Voltage_Feedback_Loop        2.2
#define Ki_Voltage_Feedback_Loop        0.0003
// Voltage Control Loop Feedforward Path Parameters
#define Kp_Voltage_Feedforward_Loop     0.1
#define PI_Voltage_Max                  1                     // Define Variables to Determine PI Output Clamp
#define PI_Voltage_Min                  0
// Current Control Loop Parameters
#define Iref_PSFB_Feedback_Loop      2500                           // Define Variables to Acquire Current Feedback
#define Kp_Current_Feedback_Loop        1.5
#define Ki_Current_Feedback_Loop        0.0000001
#define PI_Current_Max                  1
#define PI_Current_Min                  0

//
// Low Pass Filter Parameters
#define Low_Pass_Filter_Sampling_Time   0.1
//
//
#define V_Supply_Minimum              500
#define I_DCLink_Maximum             5000

//
// Inverter EPWM Channel Select
#define R_Phase                         1
#define Y_Phase                         2
#define B_Phase                         3
// Inverter EPWM Parameter Settings
#define System_Frequency        100000000                      // System Frequency = 100MHz
#define Carrier_Frequency            4000                      // Carrier Wave Frequency = 4KHz
#define Inverter_Soft_Start_Time       10                      // (In us)
//#define Inverter_Carrier_Period   System_Frequency/(2*Carrier_Frequency)
#define Inverter_Carrier_Period     12500
#define Inverter_Deadband             500
// Inverter Parameter Scaling
#define Unity_Scaling                   0.000488281
#define ADC_Offset                      2048
#define Modulating_Wave_Offset          0                               // Uncomment When Using Duke's Space Vector Code
#define Modulating_Wave_Scale       12500           // Uncomment When Using Duke's Space Vector Code
// Inverter PI Loop Parameters
#define Vout_Pi_Max                     1
#define Vout_Pi_Min                     0
// Inverter Theta Generator Parameters
#define Frequency_x_Time_Max            1
#define Frequency_x_Time_Min            0
#define Frequency_x_Time_Step           0.0063
#define Inverter_Soft_Start_Step        0.01
//
#define V_Kp_Magnitude                  0.1
#define V_Ki_Magnitude                  0.005
#define V_Kp_Phase                      0.1
#define V_Ki_Phase                      0.005                      // Define Kp & Ki Values (For Voltage Phase PI)
//
// CPU Timer Interrupts
#define ACQ_PRD                        99
#define CPU_Timer_0_Sampling_Time   10000
#define CPU_Timer_1_Sampling_Time    5000

#endif /* HEADERS_INITIALIZATION_DEFINES_H_ */
