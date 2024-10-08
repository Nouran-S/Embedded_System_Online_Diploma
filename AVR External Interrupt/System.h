/*
 * System.h
 *
 *  Created on: Oct 8, 2024
 *      Author: DELL
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h>

// GPIO Registers
#define DDRB_  *(volatile uint8_t *)(0x37)
#define DDRD_  *(volatile uint8_t *)(0x31)
#define PORTD_ *(volatile uint8_t *)(0x32)

// INT Registers
#define MCUCR_		 *(volatile uint8_t *)(0x55)
#define MCUCR_ISC00 	0
#define MCUCR_ISC01 	1
#define MCUCR_ISC10 	2
#define MCUCR_ISC11 	3

#define MCUCSR_		 *(volatile uint8_t *)(0x54)
#define MCUCSR_ISC2		6

#define GICR_		 *(volatile uint8_t *)(0x5B)
#define GICR_INT0		6
#define GICR_INT1		7
#define GICR_INT2		5

#define GIFR_	     *(volatile uint8_t *)(0x5A)
#define GIFR_INTF2		5

// The AVR Status Register
#define SREG_ *(volatile uint8_t *)(0x5F)

// BIT Math
#define SET_BIT(reg, pin) (reg |=  (1<<pin))
#define CLR_BIT(reg, pin) (reg &= ~(1<<pin))

// LEDs
#define LED_BLUE  5
#define LED_GREEN 6
#define LED_RED   7

// APIs
void GPIO_INIT();
void LED_ON(int led);
void Global_Interrupt_Enable();
void EXTI0_INIT();
void EXTI1_INIT();
void EXTI2_INIT();

#endif /* SYSTEM_H_ */
