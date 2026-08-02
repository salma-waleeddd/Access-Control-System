// doxygen style
#include <util/delay.h>
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/SEGMENT/SEGMENT_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/KEYPAD/KYP_Interface.h"
#include"MCAL/Timer0/Timer0_Interface.h"
#include"MCAL/UART/UART_Interface.h"
#include"APP/Authentication/Authentication_Interface.h"

#define F_CPU 8000000UL

void main()
{
    uint8_t password[3]={'1','2','3'};    //must be char
    LCD_Init(LCD_8bitMode);
    KPD_Init();
    Lockout_Init();
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

    LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
    LCD_WriteString("enter pasword:",LCD_8bitMode);
    LCD_Go_To_XY(1,0);
   while(1){
    if(lockout_mechanism()){
      continue;  // Skip kpd
    }
    Authentication(password);
   }
}