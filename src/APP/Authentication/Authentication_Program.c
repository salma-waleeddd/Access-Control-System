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
/*Authentication

- User enters password using Keypad.
- Password is displayed as '*'.
- Password is compared with EEPROM stored password.
- Correct password grants access.
- Incorrect password increments failure counter.
*/
#include"Authentication_Interface.h"

uint8_t Authentication(uint8_t *password){
    // uint8_t password[3]={'1','2','3'},    //must be char
    static uint8_t enteredpassword[3]={'0'};             //entered passsword
    static uint8_t digits=0;                             //digits that are entered from the loop
    uint8_t match=1;
    uint8_t BTN=0;  //button
     /*i think those should be in the int main but at the same time*/

     //===========================================================
     BTN=KPD_GetButtonValue();
     if(BTN!=0){
      if(BTN!=0xFF){
        if(digits<3){
         enteredpassword[digits]=BTN;
         _delay_ms(100);
         LCD_WriteData('*',LCD_8bitMode);
         digits++;
        }
         if(BTN=='#'){
         LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
         for(digits=0;digits<3;digits++){
           if(enteredpassword[digits]!=password[digits]){
            match=0;
           }
         }
          if(match==0){
           match=1;
           digits=0;
           BTN=0;
           LCD_Go_To_XY(0,1);
           LCD_WriteString("wrong password",LCD_8bitMode);
           _delay_ms(1000);
           LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
           LCD_Go_To_XY(0,1);
           LCD_WriteString("enter pasword:",LCD_8bitMode);
           LCD_Go_To_XY(1,0);
          //  ==============================================================================
           //resolved: erased local "trying" counter, now uses the lockout increment counter
           Lockout_IncrementCounter();
           if(Lockout_IsActive()){ //resolved: was "i think i should put return", now returns 2 (locked out)
            lockout_ended=0;
            timer_interrupts=0;
            return 2;
           }
          //=============================================================================
           }
         else if(match==1){
           LCD_Go_To_XY(0,1);
           LCD_WriteString("enter",LCD_8bitMode);
           _delay_ms(1000);
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
            digits=0;
            Lockout_ResetCounter();
            return 1;
         }
        }
     }
   }
    else{
      BTN=0xFF;
    }
    return 0;
}