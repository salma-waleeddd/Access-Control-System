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
#include "../../HAL/LED/LED_Interface.h"
#include"../Lockout/Lockout_Interface.h"
#include"../Admin/Admin_Interface.h"
#include"Authentication_Config.h"

void Authentication_Init();
uint8_t Authentication();   // 0=no result yet, 1=access granted, 2=locked out, 3=admin menu ran

#endif