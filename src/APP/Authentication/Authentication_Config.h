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
#ifndef AUTHENTICATION_CONFIG_H_
#define AUTHENTICATION_CONFIG_H_

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../Admin/Admin_Config.h"

#define Authentication_GreenLedGroup    Dio_GroupD
#define Authentication_GreenLedPin      Dio_Pin0
#define Authentication_DoorOpenSeconds  5
#define Authentication_AdminPassword    "0000"

#endif
