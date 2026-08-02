#ifndef _DIO_INTERFACE_H
#define _DIO_INTERFACE_H

#include<stdint.h>
#include"../../COMMON/Definition.h"
#include"../../COMMON/Bitmath.h"
#include"../Atmega32regmap.h"
#include"DIO_Private.h"

// select direction  initpin 
void DIO_InitPin(uint8_t GroupName,uint8_t PinNumber,uint8_t DirState);
// outputvalue    writepin  
void DIO_WritePin(uint8_t GroupName,uint8_t PinNumber,uint8_t OutputValue);
// read  readpin 
// uint8_t DIO_ReadPin(uint8_t GroupName,uint8_t PinNumber);
void DIO_ReadPin(uint8_t GroupName,uint8_t PinNumber,uint8_t *PinState);

// select direction  initGroup 
void DIO_InitGroup(uint8_t GroupName,uint8_t DirState);
// outputvalue    writeGroup   
void DIO_WriteGroup(uint8_t GroupName,uint8_t OutputValue);
// read  readGroup  
void DIO_ReadGroup(uint8_t GroupName,uint8_t * InputStates);

void DIO_TogglePin(uint8_t GroupName,uint8_t PinNumber);


#endif