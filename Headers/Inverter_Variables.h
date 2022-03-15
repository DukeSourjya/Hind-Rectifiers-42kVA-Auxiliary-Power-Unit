#ifndef HEADERS_INVERTER_VARIABLES_H_
#define HEADERS_INVERTER_VARIABLES_H_

#include "Initialization_Defines.h"

bool Inverter_Initial_Condition = true;
bool Flag_Clear = true;

float Frequency_Factor = 0.000000001;          // Uncomment to Enable Soft Start
float Frequency_x_Time = Frequency_x_Time_Min;        // Define Frequency x Time

unsigned int R_Phase_Width = 0;
unsigned int Y_Phase_Width = 0;
unsigned int B_Phase_Width = 0;
unsigned int Sector = 1;
unsigned int V_Rphase = 0;
unsigned int V_Yphase = 0; // Load Inverter Output Y Phase into Corresponding Variable
unsigned int V_Bphase = 0;

PI Inv_Volt;
PI Inv_Phase;

Transform Inv_Volt_Feed;
Transform Inv_Volt_Out;
Transform Inv_SVM;

SVM Inv_PWM;

extern volatile struct EPWM_REGS *ePWM[];


#endif /* HEADERS_INVERTER_VARIABLES_H_ */
