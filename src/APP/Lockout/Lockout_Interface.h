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
#include"../../MCAL/Timer0/Timer0_Interface.h"
#include"stdint.h"
#include"../../HAL/LCD/LCD_Interface.h"
#define F_CPU 8000000UL

volatile uint16_t timer_interrupts = 0;
volatile uint8_t lockout_active = 0;
volatile uint8_t lockout_ended = 0;
void Timer_ISR();
void lockout_mechanism(uint8_t lockout_active);