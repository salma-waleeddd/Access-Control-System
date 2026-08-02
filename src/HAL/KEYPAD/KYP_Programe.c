#include"KYP_Interface.h"

static uint8_t keypad[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
void KPD_Init(){
    //colum are 3
    // DIO_InitPin(Dio_GroupB,Dio_Pin4,Output);
    // DIO_InitPin(Dio_GroupB,Dio_Pin5,Output);
    // DIO_InitPin(Dio_GroupB,Dio_Pin6,Output);
    // //Init value for coloum 
    // DIO_WritePin(Dio_GroupD,Dio_Pin0,High); 
    // DIO_WritePin(Dio_GroupD,Dio_Pin1,High);
    // DIO_WritePin(Dio_GroupD,Dio_Pin2,High);

    // //row are 4
    // DIO_InitPin(Dio_GroupB,Dio_Pin0,Input);
    // DIO_InitPin(Dio_GroupB,Dio_Pin1,Input);
    // DIO_InitPin(Dio_GroupB,Dio_Pin2,Input);
    // DIO_InitPin(Dio_GroupB,Dio_Pin3,Input);

    // DIO_WritePin(Dio_GroupB,Dio_Pin0,High);
    // DIO_WritePin(Dio_GroupB,Dio_Pin1,High);
    // DIO_WritePin(Dio_GroupB,Dio_Pin2,High);
    // DIO_WritePin(Dio_GroupB,Dio_Pin3,High);

    KPD_ROW_PINS1_init;  
    KPD_ROW_PINS2_init; 
    KPD_ROW_PINS3_init;  
    KPD_COLUM_PINS1_init;
    KPD_COLUM_PINS2_init;
    KPD_COLUM_PINS3_init;
    KPD_COLUM_PINS4_init;

    KPD_ROW_PINS1_write; 
    KPD_ROW_PINS2_write; 
    KPD_ROW_PINS3_write; 
    KPD_COLUM_PINS1_write;
    KPD_COLUM_PINS2_write;
    KPD_COLUM_PINS3_write;
    KPD_COLUM_PINS4_write;

}
#define Pressed 0 
#define Not_Pressed 0xFF

uint8_t KPD_GetButtonValue()
{
    uint8_t Result= 0 ;
    for(uint8_t C = 0 ;C <3;C++)
    {
        DIO_WritePin(Dio_GroupD,C,Low);
        for(uint8_t R = 0 ;R<4;R++)
        {
            DIO_ReadPin(Dio_GroupB,R,&Result);
            if(Result==Pressed)
            {
                DIO_WritePin(Dio_GroupB,R,High);
                _delay_ms(100);
                return keypad[R][C];
            }
        }
        DIO_WritePin(Dio_GroupD,C,High);
    }
  return Not_Pressed;
}