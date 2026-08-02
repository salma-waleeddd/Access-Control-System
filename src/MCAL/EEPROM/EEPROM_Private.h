#ifndef _EEPROM_PRIVATE_H
#define _EEPROM_PRIVATE_H
//from page 18 to 20
//eeprom address register EEARH AND EEARL
#define EEPROM_EEAR9 9
#define EEPROM_EEAR8 8
#define EEPROM_EEAR7 7
#define EEPROM_EEAR6 6
#define EEPROM_EEAR5 5
#define EEPROM_EEAR4 4
#define EEPROM_EEAR3 3
#define EEPROM_EEAR2 2
#define EEPROM_EEAR1 1
#define EEPROM_EEAR0 0
//eeprom data register eedr use eear reg
#define EEPROM_EEDR7 7
#define EEPROM_EEDR6 6
#define EEPROM_EEDR5 5
#define EEPROM_EEDR4 4
#define EEPROM_EEDR3 3
#define EEPROM_EEDR2 2
#define EEPROM_EEDR1 1
#define EEPROM_EEDR0 0
//eeprom control registr eecr
#define EEPROM_EERIE 3 //interrupt
#define EEPROM_EEMWE 2 //master write
#define EEPROM_EEWE  1 //write
#define EEPROM_EERE  0 //read

//mode
#define ReadFromEeprom  1
#define WriteFromEeprom 2
//i need this in the write eeprom
#define SPMCR_REG_BIT0_IS_SPMEN 0

#endif