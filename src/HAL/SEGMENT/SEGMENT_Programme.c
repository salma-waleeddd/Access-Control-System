#include"SEGMENT_Interface.h"

// uint8_t number[10]={zero, one,two,three,four,five,six,seven,eight,nine},//number in  7 segmen

void Segment_Init(uint8_t GroupName)
{
    DIO_InitGroup(GroupName,Output);
}

void DisplayNumber(uint8_t GroupName, uint8_t Number)
{
  while(1){
     for(int count=0;count<=10;count++){
        // for(int loop=0;loop<10;loop++){
        // PORTA_Reg=Number[count];//tens
        // PORTD_Reg=Number[loop];//ones
        DIO_WriteGroup(GroupName,High);
        _delay_ms(1000);
    //    }
        }
     }
}

void DisplayRang(uint8_t GroupName,uint8_t Start , uint8_t End )
{
    while(1){
        for( uint8_t i= Start;i < End;i++)
        {
          DisplayNumber(GroupName,i);
          _delay_ms(1000);
        }  
    }
    //Display Range with 1 sec waiting 
}