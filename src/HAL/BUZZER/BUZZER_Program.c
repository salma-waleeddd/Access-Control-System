#include "BUZZER_Interface.h"
#include "BUZZER_Config.h"

void Buzzer_Init(void)
{
    DIO_InitPin(Buzzer_Group, Buzzer_Pin, Output);
    DIO_WritePin(Buzzer_Group, Buzzer_Pin, Low);
}

void Buzzer_On(void)
{
    DIO_WritePin(Buzzer_Group, Buzzer_Pin, High);
}

void Buzzer_Off(void)
{
    DIO_WritePin(Buzzer_Group, Buzzer_Pin, Low);
}
