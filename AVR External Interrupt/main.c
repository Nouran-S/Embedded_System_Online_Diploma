/*
 * main.c
 *
 *  Created on: Aug 24, 2024
 *      Author: Nouran S.
 */
#include <avr/interrupt.h>
#include "System.h"

int main()
{
	GPIO_INIT();
	Global_Interrupt_Enable();
	EXTI0_INIT();
	EXTI1_INIT();
	EXTI2_INIT();

	while(1)
	{

	}
}

ISR(INT0_vect)
{
	// Any Change
	LED_ON(LED_BLUE);
}

ISR(INT1_vect)
{
	// Rising Edge
	LED_ON(LED_GREEN);
}

ISR(INT2_vect)
{
	// Falling Edge
	LED_ON(LED_RED);
}









