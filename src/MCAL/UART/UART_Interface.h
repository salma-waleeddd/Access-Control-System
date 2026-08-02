#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

#include <stdint.h>

#include "../../COMMON/Definition.h"
#include "../../COMMON/Bitmath.h"
#include "../Atmega32regmap.h"

#include "UART_Private.h"
#include "UART_Config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
    1- Mode Select -> Asynch / Synch 
    2- Stop Bit not -> 1Stop / 2 Stop 
    3- Parity Check status -> even / odd / disable 
    4- 
*/

/*Initialization API*/
void UART_Init(Uart_Config_t Uart_Config);

/* Polling (Blocking)API*/
void UART_SendBytePolling(uint16_t Data);
uint16_t UART_ReceiveBytePolling();
void UART_SendStringPolling(uint8_t* String); // Characters 
void UART_ReceiveStringPolling(uint8_t* Buffer, uint8_t Terminator);
void UART_SendBufferPolling(uint8_t * Buffer , uint16_t Length);//Raw Data 




/*Interrupt API*/
void UART_SendByteInterrupt(uint16_t Data);

void UART_EnableRXInterrupt();//Done
void UART_EnableTXInterrupt();//Done
void UART_EnableREInterrupt();//Done

void UART_DisableRXInterrupt();//Done
void UART_DisableTXInterrupt();//Done
void UART_DisableREInterrupt();//Done

void UART_SetRXCallback(void (*PF)(uint16_t));// almost Done
void UART_SetTXCallback(void (*PF)(void));// almost Done
void UART_SetRECallback(void (*PF)(void));// almost Done

/* Driver Control API */
void UART_EnableRX();//Done
void UART_EnableTX();//Done
void UART_DisableRX();//Done
void UART_DisableTX();//Done









#endif