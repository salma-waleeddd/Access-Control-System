
#include "Timer0_Interface.h"


static uint8_t StaticPWMOutputMode = 0;
static void (*Timer0_OVFCallBack)(void)=Null;
static void (*Timer0_CTCCallBack)(void)=Null;
void TIMER0_Init(Timer0_Config_t Config)
{
    TCCR0_Reg = ClearRegister ; 
    if(Config.TimerMode==Timer0_NormalMode)
    {
        // Select the Normal Mode from TCCR0 
        ClearBit(TCCR0_Reg,Timer0_WGM00);
        ClearBit(TCCR0_Reg,Timer0_WGM01);
        //Update the Preload value 
        TCNT0_Reg=Config.PreloadValue;
        // Enable the Interrupt for OverFlow 
        SetBit(TIMSK_Reg,Timer0_TOIE0);
        
    }
    else if (Config.TimerMode==Timer0_CTCMode)
    {
        // Select the CTC Mode from TCCR0 
        ClearBit(TCCR0_Reg,Timer0_WGM00);
        SetBit(TCCR0_Reg,Timer0_WGM01);
        // Update the Compare  value 
        OCR0_Reg=Config.CompareMatchValue;
        // Enable the Interrupt for CompareMatch 
        SetBit(TIMSK_Reg,Timer0_OCIE0);
    }
    else if (Config.TimerMode==Timer0_FastPWM)
    {
        SetBit(TCCR0_Reg,Timer0_WGM00);
        SetBit(TCCR0_Reg,Timer0_WGM01);
        if(Config.PWMOutputMode==Timer0_OC0NinInverting)
        {
            ClearBit(TCCR0_Reg,Timer0_COM00);
            SetBit(TCCR0_Reg,Timer0_COM01);
            StaticPWMOutputMode = Timer0_OC0NinInverting ;
        }
        else if (Config.PWMOutputMode==Timer0_OC0Inverting)
        {
            SetBit(TCCR0_Reg,Timer0_COM00);
            SetBit(TCCR0_Reg,Timer0_COM01);
            StaticPWMOutputMode = Timer0_OC0Inverting ;
        }
        OCR0_Reg = ClearRegister ; 
    }
    else if (Config.TimerMode==Timer0_PhaseCorrectPWM)
    {
        SetBit(TCCR0_Reg,Timer0_WGM00);
        ClearBit(TCCR0_Reg,Timer0_WGM01);
        if(Config.PWMOutputMode==Timer0_OC0NinInverting)
        {
            ClearBit(TCCR0_Reg,Timer0_COM00);
            SetBit(TCCR0_Reg,Timer0_COM01);
            StaticPWMOutputMode = Timer0_OC0NinInverting ;
        }
        else if(Config.PWMOutputMode==Timer0_OC0Inverting)
        {
            SetBit(TCCR0_Reg,Timer0_COM00);
            SetBit(TCCR0_Reg,Timer0_COM01);
            StaticPWMOutputMode = Timer0_OC0Inverting ;
        }
        OCR0_Reg = ClearRegister;
    }

}

void TIMER0_Start(uint8_t ClockSelectValue)
{
    if (ClockSelectValue!=Timer0_Disable)
    {
      TCCR0_Reg = (TCCR0_Reg &~ClockSelectMask)|ClockSelectValue;
    }
}
void TIMER0_Stop(void)
{   
    TCCR0_Reg = (TCCR0_Reg &~ClockSelectMask)|Timer0_Disable;
}

void TIMER0_SetPreload(uint8_t PreloadValue)
{
    TCNT0_Reg=PreloadValue;
}
void TIMER0_SetCompare(uint8_t CompareValue)
{
    OCR0_Reg=CompareValue;
}

void TIMER0_SetCallBackFunction(uint8_t TimerInterruptType, void (*PF)(void))
{
    if(TimerInterruptType==Timer0_OverFlowInterrupt)
    {
      if(PF!=Null)
      {
        Timer0_OVFCallBack=PF;
      }  
    }
    else if (TimerInterruptType==Timer0_CompareMatchInterrupt)
    {
        if(PF!=Null)
        {
            Timer0_CTCCallBack=PF;
        }
    }
}


void TIMER0_SetPWMDutyCycle(uint8_t DutyCyclePercentage )
{
    if(DutyCyclePercentage<=Timer0_MaxDutyCycle)
    {
        uint8_t LocalCompareValue = 0;
        if(StaticPWMOutputMode==Timer0_OC0NinInverting)
        {
            // 2^n*(DutyCycle)
            LocalCompareValue = (uint8_t)(((uint32_t)DutyCyclePercentage*Timer0_MaxPWM)/Timer0_MaxDutyCycle) ;
        }
        else if (StaticPWMOutputMode==Timer0_OC0Inverting)
        {
            // CompareValue = 2^n *(1-DutyCycle)
            // CompareValue = 2^n - 2^n*(DutyCycle)
            LocalCompareValue = Timer0_MaxPWM - (uint8_t)((Timer0_MaxPWM*(uint32_t)DutyCyclePercentage)/Timer0_MaxDutyCycle) ; 
        }
        OCR0_Reg = LocalCompareValue ; // Solve the Bug 
    }

}

//Compare Match 
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
    Timer0_CTCCallBack();
}
//OverFlow 
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
    Timer0_OVFCallBack();
}