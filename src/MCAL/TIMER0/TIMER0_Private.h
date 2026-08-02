#ifndef _TIMER0_PRIVATE_H
#define _TIMER0_PRIVATE_H


#define Timer0_FOC0     7 
#define Timer0_WGM00    6 
#define Timer0_WGM01    3 

#define Timer0_COM01    5
#define Timer0_COM00    4


#define Timer0_CS02     2
#define Timer0_CS01     1
#define Timer0_CS00     0  


#define Timer0_NormalMode           0 
#define Timer0_CTCMode              1
#define Timer0_FastPWM              2
#define Timer0_PhaseCorrectPWM      3

#define Timer0_OC0DisConnect  0 
#define Timer0_OC0Toggle      1
#define Timer0_OC0Clear       2 
#define Timer0_OC0Set         3 

#define Timer0_OC0NinInverting   4
#define Timer0_OC0Inverting      5


// Reg = (Reg&~Mask)|PrescallerValue

#define Timer0_Disable            0   
#define Timer0_Prescaller1        1 
#define Timer0_Prescaller8        2
#define Timer0_Prescaller64       3 
#define Timer0_Prescaller256      4
#define Timer0_Prescaller1024     5 

#define Timer0_ExternalFalling      6
#define Timer0_ExternalRising       7 

#define ClockSelectMask 0x07 


#define Timer0_OCIE0     1
#define Timer0_TOIE0     0




#define Timer0_OverFlowInterrupt     0 
#define Timer0_CompareMatchInterrupt 1 


// //Compare Match 
// void __vector_10(void)   __attribute__((signal));
// //OverFlow 
// void __vector_11(void)   __attribute__((signal));


typedef struct
{
    uint8_t TimerMode ;
    uint8_t PreloadValue;
    uint8_t CompareMatchValue;
    uint8_t PWMOutputMode;
    uint8_t DutyCycleInitValue;
}Timer0_Config_t ;



#define Timer0_MaxPWM         255UL
#define Timer0_MaxDutyCycle   100

#endif
