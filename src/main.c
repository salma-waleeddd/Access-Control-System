// doxygen style
#include <util/delay.h>
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/SEGMENT/SEGMENT_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/KEYPAD/KYP_Interface.h"
#include"MCAL/Timer0/Timer0_Interface.h"
#include"MCAL/UART/UART_Interface.h"
#include"APP/Authentication/Authentication_Interface.h"
#include"APP/Alarm/Alarm_Interface.h"
#include"APP/Admin/Admin_Interface.h"

#define F_CPU 8000000UL

void main()
{
    LCD_Init(LCD_8bitMode);
    KPD_Init();
    Alarm_Init();
    Lockout_Init();
    Admin_Init();
    Authentication_Init();
    Timer0_Config_t config={
     .TimerMode=Timer0_CTCMode,
     .CompareMatchValue=249,
    };
    TIMER0_Init(config);
    TIMER0_Start(Timer0_Prescaller64);
    TIMER0_SetCallBackFunction(Timer0_CompareMatchInterrupt,Timer_ISR);
    LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
    LCD_WriteString("enter pasword:",LCD_8bitMode);
    LCD_Go_To_XY(1,0);
   while(1){
    if(lockout_mechanism()){
      continue;  // Skip kpd
    }
    Authentication();
   }
}
