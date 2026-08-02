/**
* @file    
* @author (developer)  
* @author(reviewer)
* @brief  
* @details
* @version
* @date
* @copyright Copyright (c) 2026, Gestell Company
*/
#ifndef AUTHENTICATION_INTERFACE_H_
#define AUTHENTICATION_INTERFACE_H_

#include<stdint.h>
#include "../../HAL/KEYPAD/KYP_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include"../Lockout/Lockout_Interface.h"

uint8_t Authentication(uint8_t *password);

#endif