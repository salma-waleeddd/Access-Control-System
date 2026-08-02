#include <util/delay.h>
#include "Alarm_Interface.h"
#include "Alarm_Private.h"
#include "../../HAL/BUZZER/BUZZER_Interface.h"

void Alarm_Init(void)
{
    Buzzer_Init();
}

void Alarm_ShortBeep(void)
{
    Buzzer_On();
    _delay_ms(Alarm_ShortBeepMs);
    Buzzer_Off();
}

void Alarm_LockoutAlert(uint16_t Seconds)
{
    uint16_t i;

    Alarm_ShortBeep();
    _delay_ms(150);
    Alarm_ShortBeep();

    for(i = 0; i < Seconds; i++)
    {
        _delay_ms(1000);
    }
}
