#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H
#include <stdint.h>


/*UCSRA */
#define Uart_RXC  7 
#define Uart_TXC  6
#define Uart_UDRE 5
#define Uart_FE   4 
#define Uart_DOR  3
#define Uart_PE   2 
#define Uart_U2X  1 
#define Uart_MPCM 0 

#define Uart_NormalSpeed  0 
#define Uart_DoubleSpeed  1 

/*UCSRB */
#define Uart_RXCIE  7 
#define Uart_TXCIE  6
#define Uart_UDRIE  5
#define Uart_RXEN   4 
#define Uart_TXEN   3
#define Uart_UCSZ2  2 
#define Uart_RXB8   1 
#define Uart_TXB8   0 


/*UCSRC */
#define Uart_URSEL  7 
#define Uart_UMSEL  6
#define Uart_UPM1   5
#define Uart_UPM0   4 
#define Uart_USBS   3
#define Uart_UCSZ1  2 
#define Uart_UCSZ0  1 
#define Uart_UCPOL   0 


#define Uart_AsynchronousMode   0
#define Uart_SynchronousMode    1


#define Uart_ParityDisabled 0 
#define Uart_ParityEven     1 
#define Uart_ParityOdd      2

#define Uart_1StopBit       0
#define Uart_2StopBit       1


#define Uart_5BitSize       0
#define Uart_6BitSize       1
#define Uart_7BitSize       2
#define Uart_8BitSize       3
#define Uart_9BitSize       7

#define Uart_EnableRxOnly   0
#define Uart_EnableTxOnly   1 
#define Uart_EnableRxAndTx  2


#define Uart_InterruptDisabled      0  
#define Uart_InterruptRxOnly        1   
#define Uart_InterruptTxOnly        2   
#define Uart_InterruptUdreOnly      3   
#define Uart_InterruptRxTx          4   
#define Uart_InterruptRxUdre        5  
#define Uart_InterruptTxUdre        6   
#define Uart_InterruptAll           7   

typedef struct 
{
    uint8_t ModeSelect ; 
    uint8_t StopBitSelect;
    uint8_t ParitySelect;
    uint8_t SizeCharacterSelect;
    uint8_t SpeedMode;
    uint32_t BaudRate;
    uint8_t InterruptSelect ;
    uint8_t EnbaleSelect ;
}Uart_Config_t;

/* ISR Vectors */
void __vector_13(void) __attribute__((signal,used)); /* RX Complete */
void __vector_14(void) __attribute__((signal,used)); /* UDR Empty */
void __vector_15(void) __attribute__((signal,used)); /* TX Complete */

#endif