// doxygen style 
#include <util/delay.h>
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/SEGMENT/SEGMENT_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/KEYPAD/KYP_Interface.h"
#include"MCAL/Timer0/Timer0_Interface.h"
#include"MCAL/UART/UART_Interface.h"

#define F_CPU 8000000UL

volatile uint16_t timer_interrupts = 0;
volatile uint8_t lockout_active = 0;
volatile uint8_t lockout_ended = 0;
void Timer_ISR(){
  static uint16_t Timer_count=0;
  Timer_count++;
  if(Timer_count>=20000){
    lockout_ended=1;
    lockout_active=0;
    Timer_count=0;
  }
}

void main()
{
    uint8_t password[3]={'1','2','3'},    //must be char 
    enteredpassword[3]={'0'},             //entered passsword
    digits=0,                             //digits that are entered from the loop
    match=1,
    trying=0;                              //if password and entered password matches
    LCD_Init(LCD_8bitMode);
    KPD_Init();
    Timer0_Config_t config={
     .TimerMode=Timer0_CTCMode,
     .CompareMatchValue=249,
    };
    TIMER0_Init(config);
    TIMER0_Start(Timer0_Prescaller64);
    TIMER0_SetCallBackFunction(Timer0_CompareMatchInterrupt,Timer_ISR);

    // Uart_Config_t Config={
    //     .ModeSelect=Uart_AsynchronousMode,
    //     .StopBitSelect=Uart_1StopBit,
    //     .ParitySelect = Uart_ParityDisabled,
    //     .SpeedMode = Uart_NormalSpeed,
    //     .BaudRate = 9600,
    //     .SizeCharacterSelect = 8,
    //     .EnbaleSelect = Uart_EnableTxOnly,
    //     .InterruptSelect = Uart_InterruptDisabled   
    // };
    // UART_Init(Config);
    // UART_SendStringPolling("welcome");
    // UART_SendBytePolling(0x00FF);

    uint8_t BTN=0;  //button 
    LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);             
    LCD_WriteString("enter pasword:",LCD_8bitMode);
    LCD_Go_To_XY(1,0);
   while(1){
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
           if(trying<3){
           trying++;
           }
          //  ==============================================================================
           //here is the look out mechanism see timer video
           else if(trying==3){
            lockout_active=1;
            lockout_ended=0;
            timer_interrupts=0;
          //=============================================================================
           }
           }
         else if(match==1){
           LCD_Go_To_XY(0,1);
           LCD_WriteString("enter",LCD_8bitMode);
           _delay_ms(1000);  
            LCD_Instruction(LCD_ClearScreen,LCD_8bitMode); 
            while(1);
         }
        }
     }
   }
    else{
      BTN=0xFF;
    }
   }
} 