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
#ifndef LOCKOUT_INTERFACE_H_
#define LOCKOUT_INTERFACE_H_

#include"../../MCAL/Timer0/Timer0_Interface.h"
#include"stdint.h"
#include"../../HAL/LCD/LCD_Interface.h"
#include"../../HAL/LED/LED_Interface.h"
#include"../../LIB/STD_TYPES.h"
#include"../Alarm/Alarm_Interface.h"
#include"Lockout_Config.h"
#define F_CPU 8000000UL

#define MAX_FAILED_ATTEMPTS    3

extern volatile uint16_t timer_interrupts;
extern volatile uint8_t lockout_ended;

void Timer_ISR();
uint8_t lockout_mechanism(void);

void Lockout_Init(void);
void Lockout_IncrementCounter(void);
void Lockout_ResetCounter(void);          // after a successful login, the failedattemps counter resets to zero
void Lockout_Start(void);                 // when system is locked
void Lockout_Stop(void);                  // unlocks the lockout state
uint8_t Lockout_IsActive(void);           // returns the lockout_start
uint8_t Lockout_GetCounter(void);

#endif
