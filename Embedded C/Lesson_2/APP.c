#include "UART.h"
unsigned char str[100] = "Learn-in-depth: <Nouran>";
void main()
{
     UART_Send_STR(str);
}