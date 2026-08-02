#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#include"../../MCAL/DIO/DIO_Interface.h"
#include"LCD_Private.h"
#include"LCD_Config.h"

void LCD_Init(uint8_t ModeType);
void LCD_WriteData(uint8_t Data,uint8_t ModeType);
void LCD_Instruction(uint8_t Instruction,uint8_t ModeType);
void LCD_WriteString(uint8_t *String,uint8_t ModleType);
void LCD_Go_To_XY(uint8_t x,uint8_t y);
void LCD_Number(uint8_t ,uint8_t ModleType);



#endif