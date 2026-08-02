#ifndef _ADMIN_INTERFACE_H
#define _ADMIN_INTERFACE_H

#include <stdint.h>
#include "Admin_Config.h"

// Loads the user table from EEPROM
void Admin_Init(void);

uint8_t Admin_Count(void);

// eturns the matching user's index
uint8_t Admin_Authenticate(const char *Pin);

// shows the admin menu
void Admin_RunMenu(void);

#endif
