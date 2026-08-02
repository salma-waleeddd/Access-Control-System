#include <util/delay.h>
#include "Alarm_Interface.h"
#include "Alarm_Private.h"
#include "../../HAL/BUZZER/BUZZER_Interface.h"
#include "../../HAL/LED/LED_Interface.h"

void Alarm_Init(void)
{
    Buzzer_Init();
    Led_Init(Alarm_WarnLed_Group, Alarm_WarnLed_Pin);
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

    Led_on(Alarm_WarnLed_Group, Alarm_WarnLed_Pin, SourceConnection);
    Alarm_ShortBeep();
    _delay_ms(150);
    Alarm_ShortBeep();

    for(i = 0; i < Seconds; i++)
    {
        _delay_ms(1000);
    }

    Led_off(Alarm_WarnLed_Group, Alarm_WarnLed_Pin, SourceConnection);
}
