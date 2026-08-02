#ifndef _EEPROM_INTERFACE_H
#define _EEPROM_INTERFACE_H

#include<stdint.h>
#include"../Atmega32regmap.h"
#include"../../COMMON/Bitmath.h"
#include"../../COMMON/Definition.h"
#include"EEPROM_Private.h"

void EEPROM_Init(uint8_t eppromMode);
void EEPROM_WriteData(uint8_t address,uint8_t *data);
void EEPROM_ReadData(uint8_t address,uint8_t *data);

#endif
