#ifndef HEADERS_PSFB_VARIABLES_H_
#define HEADERS_PSFB_VARIABLES_H_

#include "Initialization_Defines.h"

//volatile struct EPWM_REGS *ePWM[];
unsigned int PWMxA_Width;
unsigned int PWMxB_Width;
float Width_A;
float Width_B;
unsigned int Phase_Shift = Phase_Shift_Max;
// System Status Check Conditions
extern bool Initial_Condition;
bool PSFB_Overload       = false;
bool PSFB_Overcurrent    = false;
bool Input_Under_Voltage = false;
bool Output_Overvoltage  = false;
bool Output_Overcurrent  = false;
bool Input_Undervoltage  = false;

PI PSFB_Volt;
PI PSFB_Curr;

unsigned int V_Filtered  = 0;
unsigned int V_Input     = 0;
unsigned int I_Out       = 0;

int Present_Input        = 0;                                               // Acquire Present ADCINA2 Input
int Present_Output       = 0;  // Compute Present ADCINA2 Output                                             // Update ADCINA2 Output
int Previous_Output      = 0;                                                  // Load Present ADCINA2 Output into Previous ADCINA2 Output

volatile struct EPWM_REGS *ePWM[] = {
                                      &EPwm1Regs,         // ePWM[0] not defined since there is no EPwm0regs in TMS320F28377S
                                      &EPwm1Regs,
                                      &EPwm2Regs,
                                      &EPwm3Regs,
                                      &EPwm4Regs,
                                      &EPwm5Regs,
                                      &EPwm6Regs,
                                      &EPwm7Regs,
                                      &EPwm8Regs,
};

#endif /* HEADERS_PSFB_VARIABLES_H_ */
