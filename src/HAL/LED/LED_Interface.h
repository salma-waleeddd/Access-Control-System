#ifndef _LED_INTERFACE_H
#define _LED_INTERFACE_H

#include<stdio.h>
#include"LED_Private.h"
#include"../../MCAL/DIO/DIO_Interface.h"

void Led_Init(uint8_t GroupName , uint8_t PinNumber );
void Led_on(uint8_t GroupName , uint8_t PinNumber , uint8_t ConnectionType);
void Led_off(uint8_t GroupName , uint8_t PinNumber , uint8_t ConnectionType);
void Led_Toggle(uint8_t GroupName , uint8_t PinNumber);

#endif