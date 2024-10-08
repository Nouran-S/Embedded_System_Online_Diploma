/*
 * System.c
 *
 *  Created on: Oct 8, 2024
 *      Author: DELL
 */
#include <avr/delay.h>
#include "System.h"

void GPIO_INIT()
{
	// LEDs on Port.D Pins(5, 6, 7) are output ..
	SET_BIT(DDRD_, LED_BLUE);
	SET_BIT(DDRD_, LED_GREEN);
	SET_BIT(DDRD_, LED_RED);

	// LEDs on Port.D Pins(5, 6, 7) are off ..
	CLR_BIT(PORTD_, LED_BLUE);
	CLR_BIT(PORTD_, LED_GREEN);
	CLR_BIT(PORTD_, LED_RED);

	// Push Buttons are Input ..
	CLR_BIT(DDRD_, 2);	// INT0
	CLR_BIT(DDRD_, 3);	// INT1
	CLR_BIT(DDRB_, 2);	// INT2
}

void LED_ON(int led)
{
	SET_BIT(PORTD_, led);
	_delay_ms(1000);
	CLR_BIT(PORTD_, led);
}

void Global_Interrupt_Enable()
{
	SET_BIT(SREG_, 7);
}

void EXTI0_INIT()
{
	// Any logical change on INT0 generates an interrupt request
	SET_BIT(MCUCR_, MCUCR_ISC00);
	CLR_BIT(MCUCR_, MCUCR_ISC01);

	// External Interrupt Request 0 Enable
	SET_BIT(GICR_, GICR_INT0);
}

void EXTI1_INIT()
{
	// The rising edge of INT1 generates an interrupt request
	SET_BIT(MCUCR_, MCUCR_ISC10);
	SET_BIT(MCUCR_, MCUCR_ISC11);

	// External Interrupt Request 1 Enable
	SET_BIT(GICR_, GICR_INT1);
}

void EXTI2_INIT()
{
	// Falling edge on INT2
	CLR_BIT(MCUCSR_, MCUCSR_ISC2);  // Falling edge

	// Enable External Interrupt Request 2
	SET_BIT(GICR_, GICR_INT2);
}

