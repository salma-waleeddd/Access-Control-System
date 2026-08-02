
#include"EEPROM_Interface.h"
void EEPROM_Init(uint8_t eppromMode){
    if(eppromMode==WriteFromEeprom){    //write
        ClearBit(EECR_Reg,EEPROM_EERE);
        SetBit(EECR_Reg,EEPROM_EEWE);
    }
    if(eppromMode==ReadFromEeprom){     //read
        SetBit(EECR_Reg,EEPROM_EERE);
        ClearBit(EECR_Reg,EEPROM_EEWE);    
    }
}


void EEPROM_WriteData(uint8_t address,uint8_t *data){
  while (EECR_Reg & (1 << EEPROM_EEWE));
  while(SPMCR_Reg&(1<<SPMCR_REG_BIT0_IS_SPMEN));
  EEARH_Reg = address >> 8;                         // Set address
  EEARL_Reg = address & 0xFF;        
  EEDR_Reg = *data;                                   // Set data
  SetBit(EECR_Reg,EEPROM_EEMWE);                    // Write Enable (within 4 cycles!)  
  SetBit(EECR_Reg,EEPROM_EEWE);                    // Write Enable (within 4 cycles!)  
  
}

void EEPROM_ReadData(uint8_t address,uint8_t *data){
    while(EECR_Reg&(1<<EEPROM_EERE));
    EEARH_Reg=address>>8;
    EEARL_Reg=address&0xFF;
    SetBit(EECR_Reg,EEPROM_EERE);
    *data=EEDR_Reg;
}
/*
for adress choose from eear9 to eear0
*/