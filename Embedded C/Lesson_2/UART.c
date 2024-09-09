#include "UART.h"

#define UART0DR *((volatile unsigned int * const) ((unsigned int *)0x101f1000))

void UART_Send_STR(unsigned char * str_tx)
{
     while (*str_tx != '\0')
     {
          UART0DR = *str_tx;
          str_tx++;
     }
     
}