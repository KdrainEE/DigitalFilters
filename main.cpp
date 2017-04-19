#include "mbed.h"
//#include <iostream>
/*
    THIS CODE WORKS. DO NOT CHANGE!!!!!
    Frequency analysis is the same as from the lab. 
    Adding amplitude
    Amplitude functionality passing
*/

//signal in 
AnalogIn AI(PTB0);
//digitized pwm output signal
AnalogOut Aout(PTE30);

//frequency output signals
DigitalOut HP_DO(PTD3);//RED lowpass
DigitalOut BP_DO(PTD2);//GREEN bandpass
DigitalOut LP_DO(PTD0);//BLUE highpass

//amplitude output signals
DigitalOut Amp1(D14);
DigitalOut Amp2(D1);
DigitalOut Amp3(D2);
DigitalOut Amp4(D3);
DigitalOut Amp5(D4);
DigitalOut Amp6(D5);
DigitalOut Amp7(D6);
DigitalOut Amp8(D7);
DigitalOut Amp9(D8);
DigitalOut Amp10(D9);

DigitalOut amplitude_pins[10] = {Amp1, Amp2, Amp3, Amp4, Amp5, 
                Amp6, Amp7, Amp8, Amp9, Amp10};

float AcalcHP;
float AcalcLP;
float AcalcBP_l;
float AcalcBP_u;
float AI_cur;
float AI2;
float AI3;
float AI4;
int loop_count;

int main()
{
    
    while(1)
    {
        AI_cur = AI;
        Aout = AI_cur;
        AcalcLP = 4*((AI+AI2+AI3)/3);//3
        
        if(0.0001<AcalcLP && AcalcLP < 0.06) 
        {
            LP_DO = 1;
        }
        else
        {
            LP_DO = 0;
        }
        
        AcalcBP_l = 6*fabs((AI+AI2)/2);
        AcalcBP_u = 7*((AI+AI2+AI3)/3);
        if(0.19 < AcalcBP_l && AcalcBP_u < 0.21)// 0.18 0.21
        {
            BP_DO = 1;
        }
        else
        {
            BP_DO = 0;
        }
        
        AcalcHP = 3*fabs((AI-AI2));
        
        if(AcalcHP >0.13)
        {
            HP_DO = 1;
        }
        else
        {
            HP_DO = 0;
        }
       float reference_amplitude = 0.0;
       for(int idx = 0; idx < 10; idx++)
       {
            if((idx == 0 && AI_cur > 0.05) != (AI_cur >= reference_amplitude))
            {
                amplitude_pins[idx] = 1;    
            }
            else
            {
                amplitude_pins[idx] = 0;    
            }
            reference_amplitude += 0.1;
        } 
        
        AI4 = AI3;
        AI3 = AI2;
        AI2 = AI;        
    }
}
