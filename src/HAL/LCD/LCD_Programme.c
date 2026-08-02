#include"LCD_Interface.h"
#include<util/delay.h>

void LCD_WriteData(uint8_t Data,uint8_t ModeType){
if(ModeType==LCD_8bitMode){
DIO_WritePin(LCD_RSGroup,LCD_RSPin,High);
DIO_WritePin(LCD_RWGroup,LCD_RWPin,Low);
DIO_WriteGroup(LCD_DataGroup,Data);
DIO_WritePin(LCD_EGroup,LCD_EPin,High);
_delay_ms(1);
DIO_WritePin(LCD_EGroup,LCD_EPin,Low);
    }
    else if(ModeType==LCD_4bitMode){
        //we will write it
    }
}

void LCD_Instruction(uint8_t Instruction,uint8_t ModeType){
if(ModeType==LCD_8bitMode){
DIO_WritePin(LCD_RSGroup,LCD_RSPin,Low);
DIO_WritePin(LCD_RWGroup,LCD_RWPin,Low);
DIO_WriteGroup(LCD_DataGroup,Instruction);
DIO_WritePin(LCD_EGroup,LCD_EPin,High);
_delay_ms(1);
DIO_WritePin(LCD_EGroup,LCD_EPin,Low);
    }
    else if(ModeType==LCD_4bitMode){}
}

void LCD_Init(uint8_t ModeType){
switch (ModeType)
{
case LCD_4bitMode:
    break;
case LCD_8bitMode:
    DIO_InitPin(LCD_RSGroup,LCD_RSPin,Output);
    DIO_InitPin(LCD_RWGroup,LCD_RWPin,Output);
    DIO_InitPin(LCD_EGroup,LCD_EPin,Output);
    DIO_InitGroup(LCD_DataGroup,0xFF);
    _delay_ms(35);
    LCD_Instruction(LCD_8bitMode2Line5x8f,LCD_8bitMode);
    _delay_ms(1);
    LCD_Instruction(LCD_CursorON,LCD_8bitMode);
    _delay_ms(1);
    LCD_Instruction(LCD_ClearScreen,LCD_8bitMode);
    _delay_ms(2);
    LCD_Instruction(entrymodeI_D,LCD_8bitMode);
    _delay_ms(1);
    break;
}
}

void LCD_WriteString(uint8_t *String,uint8_t ModleType){
    if(String!=Null){
    uint8_t charcter=0;
    while(String[charcter]!=Null){
        LCD_WriteData(String[charcter],LCD_8bitMode);
        charcter++;
    }
}
}

void LCD_Go_To_XY(uint8_t x,uint8_t y){
    uint8_t DataAdress=0;//ddram adress
    switch (x)
    {
    case 0:
        DataAdress=0x00+y;
        break;
    case 1:
        DataAdress=0x40+y;
        break;    
    }
    LCD_Instruction((0x80|DataAdress),LCD_8bitMode);
}

void LCD_Number(uint8_t num ,uint8_t ModleType){
    uint8_t x=0;
    while(1){
    x=num%10;
    x+=48;
    LCD_WriteData(x,ModleType);
    x=num/10;
} 
}