#include"KYP_Interface.h"

static uint8_t keypad[4][3]={
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

void KPD_Init(){
    KPD_ROW_PINS1_init;
    KPD_ROW_PINS2_init;
    KPD_ROW_PINS3_init;
    KPD_ROW_PINS4_init;
    KPD_COLUM_PINS1_init;
    KPD_COLUM_PINS2_init;
    KPD_COLUM_PINS3_init;

    KPD_ROW_PINS1_write;
    KPD_ROW_PINS2_write;
    KPD_ROW_PINS3_write;
    KPD_ROW_PINS4_write;
    KPD_COLUM_PINS1_write;
    KPD_COLUM_PINS2_write;
    KPD_COLUM_PINS3_write;
}
#define Pressed 0
#define Not_Pressed 0xFF

uint8_t KPD_GetButtonValue()
{
    uint8_t Result= 0 ;
    for(uint8_t R = 0 ;R<4;R++)
    {
        DIO_WritePin(Dio_GroupB,Dio_Pin4+R,Low);
        for(uint8_t C = 0 ;C <3;C++)
        {
            DIO_ReadPin(Dio_GroupD,Dio_Pin2+C,&Result);
            if(Result==Pressed)
            {
                _delay_ms(20); //debounce
                DIO_ReadPin(Dio_GroupD,Dio_Pin2+C,&Result);
                if(Result==Pressed)
                {
                    while(Result==Pressed)
                    {
                        DIO_ReadPin(Dio_GroupD,Dio_Pin2+C,&Result); //wait for release
                    }
                    DIO_WritePin(Dio_GroupB,Dio_Pin4+R,High);
                    return keypad[R][C];
                }
            }
        }
        DIO_WritePin(Dio_GroupB,Dio_Pin4+R,High);
    }
  return Not_Pressed;
}
