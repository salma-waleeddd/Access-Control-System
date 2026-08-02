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

void Timer_ISR(){
  static uint16_t Timer_count=0;
  Timer_count++;
  if(Timer_count>=20000){
    lockout_ended=1;
    lockout_active=0;
    Timer_count=0;
  }
}
void lockout_mechanism(uint8_t lockout_active){
if(lockout_active==1){
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
          lockout_active = 0;
          lockout_ended = 0;
          message_shown = 0;
          trying = 0;  // Reset failure counter
          
          // Show "enter password" again
          LCD_Instruction(LCD_ClearScreen, LCD_8bitMode);
          LCD_WriteString("enter password:", LCD_8bitMode);
          LCD_Go_To_XY(1, 0);
      }
       
       continue;  // Skip kpd
  }
}