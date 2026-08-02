#ifndef _SEGMENT_INTERFACE_H
#define _SEGMENT_INTERFACE_H
#include<stdio.h>
#include"segment_private.h"
#include <util/delay.h>
#include"../../MCAL/DIO/DIO_Interface.h"

void Segment_Init(uint8_t GroupName);
void DisplayNumber(uint8_t GroupName, uint8_t Number);
void DisplayRang(uint8_t GroupName,uint8_t Start , uint8_t End );

//this one is like this
#endif

//add SEGMENT_ later