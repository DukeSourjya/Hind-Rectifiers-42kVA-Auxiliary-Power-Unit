#ifndef HEADERS_COMMON_VARIABLES_H_
#define HEADERS_COMMON_VARIABLES_H_


struct PI_Loop {
                 float PI_Out;                      // Define Variables to Introduce Phase Shift Between the Two Inverters in First Stage
                 float PI_Max;
                 float PI_Min;
                 float Ref;
                 float Ref_Fwd;
                 float Fbk_Err;
                 float Fbk_Proportional;
                 float Fbk_Integral;
                 float Fbk_Prev_Integral;
                 float Kp;
                 float Ki;
                 float Kp_Fwd;
                 float Fwd_Err;
                 float Fwd_Proportional;
};

typedef struct PI_Loop PI;

struct Transformation {
                        float R_Phase_Value;
                        float Y_Phase_Value;
                        float B_Phase_Value;
                        float Alpha;
                        float Beta;
                        float Theta;
                        float Sin_Theta;
                        float Cos_Theta;
                        float Direct;
                        float Quadrature;
};

typedef struct Transformation Transform;

struct Space_Vector {
                      float Modulation_Index;
                      float Magnitude;
                      float Gamma;
                      float Sector;
                      float Angle_Vector_1;
                      float Angle_Vector_2;
                      float Sin_Theta_Vector_1;
                      float Sin_Theta_Vector_2;
                      float Time_Vector_0;
                      float Time_Vector_1;
                      float Time_Vector_2;
                      float Time_R_Phase;
                      float Time_Y_Phase;
                      float Time_B_Phase;
};

typedef struct Space_Vector SVM;

#endif /* HEADERS_COMMON_VARIABLES_H_ */
