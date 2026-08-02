#ifndef _KYP_INTERFACE_H
#define _KYP_INTERFACE_H

#include"KYP_Config.h"
#include <util/delay.h>
#include"../../MCAL/DIO/DIO_Interface.h"

void KPD_Init();
uint8_t KPD_GetButtonValue();

#endif