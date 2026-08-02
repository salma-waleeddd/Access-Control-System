#include "DIO_Interface.h"


// select direction  initpin 
void DIO_InitPin(uint8_t GroupName,uint8_t PinNumber,uint8_t DirState)
{
    if((GroupName>=Dio_GroupA && GroupName<=Dio_GroupD)&& 
      (PinNumber>=Dio_Pin0 && PinNumber<=Dio_Pin7))
        {
            if(DirState==Output)
            {
                switch(GroupName)
                {
                    case Dio_GroupA:SetBit(DDRA_Reg,PinNumber);break;
                    case Dio_GroupB:SetBit(DDRB_Reg,PinNumber);break;
                    case Dio_GroupC:SetBit(DDRC_Reg,PinNumber);break;
                    case Dio_GroupD:SetBit(DDRD_Reg,PinNumber);break;
                }
            }
            else if (DirState==Input)
            {
                switch(GroupName)
                {
                    case Dio_GroupA:ClearBit(DDRA_Reg,PinNumber);break;
                    case Dio_GroupB:ClearBit(DDRB_Reg,PinNumber);break;
                    case Dio_GroupC:ClearBit(DDRC_Reg,PinNumber);break;
                    case Dio_GroupD:ClearBit(DDRD_Reg,PinNumber);break;
                }
            }
        }
    
}

// select direction  initDio_Group 
void DIO_InitGroup(uint8_t GroupName,uint8_t DirState)
{
    // if(Dio_GroupName>=Dio_GroupA&&Dio_GroupName<=Dio_GroupD)
    // {
        switch(GroupName)
        {
            case Dio_GroupA: DDRA_Reg = DirState;break;
            case Dio_GroupB: DDRB_Reg = DirState;break;
            case Dio_GroupC: DDRC_Reg = DirState;break;
            case Dio_GroupD: DDRD_Reg = DirState;break;
            default : break;
        }
    // }
}

// outputvalue    writepin  
void DIO_WritePin(uint8_t GroupName,uint8_t PinNumber,uint8_t OutputValue)
{
    if(GroupName<=Dio_GroupD && PinNumber<=Dio_Pin7)
    {
        if(OutputValue==High)
        {
            switch(GroupName)
            {
               case Dio_GroupA:SetBit(PORTA_Reg,PinNumber);break;                    
               case Dio_GroupB:SetBit(PORTB_Reg,PinNumber);break;                    
               case Dio_GroupC:SetBit(PORTC_Reg,PinNumber);break;                    
               case Dio_GroupD:SetBit(PORTD_Reg,PinNumber);break;                        
            }
        }
        else if (OutputValue==Low)
        {
            switch(GroupName)
            {
               case Dio_GroupA:ClearBit(PORTA_Reg,PinNumber);break;                    
               case Dio_GroupB:ClearBit(PORTB_Reg,PinNumber);break;                    
               case Dio_GroupC:ClearBit(PORTC_Reg,PinNumber);break;                    
               case Dio_GroupD:ClearBit(PORTD_Reg,PinNumber);break;                        
            }
        }
    }
}

// outputvalue    writeDio_Group   
void DIO_WriteGroup(uint8_t GroupName,uint8_t OutputValue)
{
    switch(GroupName)
    {
        case Dio_GroupA:PORTA_Reg=OutputValue;break;                    
        case Dio_GroupB:PORTB_Reg=OutputValue;break;                    
        case Dio_GroupC:PORTC_Reg=OutputValue;break;                    
        case Dio_GroupD:PORTD_Reg=OutputValue;break;  
        default : break;
    }
}

// read  readpin 
// uint8_t DIO_ReadPin(uint8_t Dio_GroupName,uint8_t PinNumber);
void DIO_ReadPin(uint8_t GroupName,uint8_t PinNumber,uint8_t *PinState)
{
    if (PinState!=Null)
    {
        if (GroupName<=Dio_GroupD && PinNumber<=Dio_Pin7)
        {
            switch(GroupName)
            {
                case Dio_GroupA: *PinState = ReadBit(PINA_Reg,PinNumber);break;
                case Dio_GroupB: *PinState = ReadBit(PINB_Reg,PinNumber);break;
                case Dio_GroupC: *PinState = ReadBit(PINC_Reg,PinNumber);break;
                case Dio_GroupD: *PinState = ReadBit(PIND_Reg,PinNumber);break;
                
            }
        }
    }
}
// read  readDio_Group  
void DIO_ReadGroup(uint8_t GroupName,uint8_t * InputStates)
{
    if(InputStates!=Null)
    {
        switch(GroupName)
        {
                case Dio_GroupA: *InputStates = PINA_Reg;break;
                case Dio_GroupB: *InputStates = PINB_Reg;break;
                case Dio_GroupC: *InputStates = PINC_Reg;break;
                case Dio_GroupD: *InputStates = PIND_Reg;break;
                
        }
    }
}


void DIO_TogglePin(uint8_t GroupName,uint8_t PinNumber)
{
    if(GroupName<=Dio_GroupD && PinNumber<=Dio_Pin7)
    {
        switch(GroupName)
        {
            case Dio_GroupA:ToggleBit(PORTA_Reg,PinNumber);break;                    
            case Dio_GroupB:ToggleBit(PORTB_Reg,PinNumber);break;                    
            case Dio_GroupC:ToggleBit(PORTC_Reg,PinNumber);break;                    
            case Dio_GroupD:ToggleBit(PORTD_Reg,PinNumber);break;                        
        }
    }
}