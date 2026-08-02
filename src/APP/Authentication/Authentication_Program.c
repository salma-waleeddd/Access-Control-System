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
#include<string.h>
#include"Authentication_Interface.h"

static void Authentication_DelaySeconds(uint16_t Seconds){
    uint16_t i;
    for(i=0;i<Seconds;i++){
        _delay_ms(1000);
    }
}

void Authentication_Init(){
    Led_Init(Authentication_GreenLedGroup,Authentication_GreenLedPin);
}

static void Authentication_GreenLedOn(void){
    Led_on(Authentication_GreenLedGroup,Authentication_GreenLedPin,SourceConnection);
}
static void Authentication_GreenLedOff(void){
    Led_off(Authentication_GreenLedGroup,Authentication_GreenLedPin,SourceConnection);
}

uint8_t Authentication(){
    static char enteredpassword[Admin_PinLen+1];          //entered PIN
    static uint8_t digits=0;                              //digits that are entered from the loop
    uint8_t BTN=0;  //button

     //===========================================================
     BTN=KPD_GetButtonValue();
     if(BTN!=0){
      if(BTN!=0xFF){
         if(BTN=='#'){
         LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
         enteredpassword[digits]='\0';
         digits=0;

         if(Admin_Authenticate(enteredpassword)!=Admin_InvalidId){
           LCD_Go_To_XY(0,1);
           LCD_WriteString("enter",LCD_8bitMode);
           _delay_ms(1000);
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
            LCD_WriteString("Opening Door",LCD_8bitMode);
            Authentication_GreenLedOn();
            Authentication_DelaySeconds(Authentication_DoorOpenSeconds);
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
            LCD_WriteString("Closing Door",LCD_8bitMode);
            Authentication_GreenLedOff();
           _delay_ms(1000);
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
            LCD_WriteString("enter pasword:",LCD_8bitMode);
            LCD_Go_To_XY(1,0);
            Lockout_ResetCounter();
            return 1;
         }
         else if(strcmp(enteredpassword,Authentication_AdminPassword)==0){
            Admin_RunMenu();
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
            LCD_WriteString("enter pasword:",LCD_8bitMode);
            LCD_Go_To_XY(1,0);
            Lockout_ResetCounter();
            return 3;
         }
         else{
           BTN=0;
           LCD_Go_To_XY(0,1);
           LCD_WriteString("wrong password",LCD_8bitMode);
           _delay_ms(1000);
           LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
           LCD_Go_To_XY(0,1);
           LCD_WriteString("enter pasword:",LCD_8bitMode);
           LCD_Go_To_XY(1,0);
           Lockout_IncrementCounter();
           if(Lockout_IsActive()){
            lockout_ended=0;
            timer_interrupts=0;
            return 2;
           }
         }
        }
        else if(digits<Admin_PinLen){
         enteredpassword[digits]=(char)BTN;
         _delay_ms(100);
         LCD_WriteData('*',LCD_8bitMode);
         digits++;
        }
     }
   }
    else{
      BTN=0xFF;
    }
    return 0;
}