#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H
#include  <stdint.h>
#include "../../COMMON/Bitmath.h"
#include "../../COMMON/Definition.h"
#include "../Atmega32regmap.h"

#include "Timer0_Private.h"
#include "Timer0_Config.h"


void TIMER0_Init(Timer0_Config_t Config);

void TIMER0_Start(uint8_t ClockSelectValue);

void TIMER0_Stop(void);
void TIMER0_SetPreload(uint8_t PreloadValue);
void TIMER0_SetCompare(uint8_t CompareValue);

void TIMER0_SetCallBackFunction(uint8_t TimerInterruptType, void (*PF)(void));

// comparevalue=2^n*DutyCycle
void TIMER0_SetPWMDutyCycle(uint8_t DutyCyclePercentage);
#endif