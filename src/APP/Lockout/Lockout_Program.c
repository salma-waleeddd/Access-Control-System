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
#include"Lockout_Interface.h"

volatile uint16_t timer_interrupts = 0;
volatile uint8_t lockout_ended = 0;

static uint8_t s_failedAttempts = 0;          //static attributes the variable only to Lockout_Program.c
static uint8_t s_lockoutActive = 0;           //static attributes the variable only to Lockout_Program.c
/*******************************************************/

void Lockout_Init(void)   //called once when the system starts//
{
    s_failedAttempts = 0;
    s_lockoutActive = 0;
}
/******************************************************************/

void Lockout_IncrementCounter(void) {
    if(s_failedAttempts < MAX_FAILED_ATTEMPTS) {
        s_failedAttempts++;
    }

    if(s_failedAttempts >= MAX_FAILED_ATTEMPTS) {
        Lockout_Start();
    }
}
/******************************************************************/

void Lockout_ResetCounter(void){     // resets counter to zero
    s_failedAttempts = 0;
}
/******************************************************************/

void Lockout_Start(void) {           // turned on lockout mode
    s_lockoutActive = 1;
}
/******************************************************************/

void Lockout_Stop(void) {         // turned off lockout mode
    s_lockoutActive = 0;
    Lockout_ResetCounter();
}
/******************************************************************/

uint8_t Lockout_IsActive(void) {
    return s_lockoutActive;
}
/******************************************************************/

uint8_t Lockout_GetCounter(void) {
    return s_failedAttempts;
}
/******************************************************************/

void Timer_ISR(){
  static uint16_t Timer_count=0;
  Timer_count++;
  if(Timer_count>=20000){
    lockout_ended=1;
    Lockout_Stop();
    Timer_count=0;
  }
}

uint8_t lockout_mechanism(void){
  if(Lockout_IsActive()==1){
    static uint8_t message_shown = 0;
      if(message_shown == 0)
      {
          LCD_Instruction(LCD_ClearScreen, LCD_8bitMode);
          LCD_Go_To_XY(0, 2);
          LCD_WriteString("YOU SHALL NOT", LCD_8bitMode);
          LCD_Go_To_XY(1, 5);
          LCD_WriteString("ENTER", LCD_8bitMode);
          message_shown = 1;
      }

      // Check if lockout has ended (timer ISR sets this)
      if(lockout_ended == 1)
      {
          lockout_ended = 0;
          message_shown = 0;

          // Show "enter password" again
          LCD_Instruction(LCD_ClearScreen, LCD_8bitMode);
          LCD_WriteString("enter password:", LCD_8bitMode);
          LCD_Go_To_XY(1, 0);
      }

      return 1;  // caller should skip keypad polling while locked out
  }
  return 0;
}
