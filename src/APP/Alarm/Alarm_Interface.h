#ifndef _ALARM_INTERFACE_H
#define _ALARM_INTERFACE_H

#include <stdint.h>
#include "Alarm_Config.h"

void Alarm_Init(void);

// Short buzzer
void Alarm_ShortBeep(void);

// warning LED on
void Alarm_LockoutAlert(uint16_t Seconds);

#endif
