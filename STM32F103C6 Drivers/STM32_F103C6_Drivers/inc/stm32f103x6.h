/*
 * stm32f103xx.h
 *
 *  Created on: Oct 17, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

// Includes:
#include <stdint.h>
#include <stdlib.h>

// Base Addresses For Memories:
#define FLASH_MEMORY_BASE_ADDRESS 						0x08000000UL
#define SYSTEM_MEMORY_BASE_ADDRESS 						0x1FFFF000UL
#define SRAM_MEMORY_BASE_ADDRESS 						0x20000000UL
#define PERIPHERALS_BASE_ADDRESS						0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE_ADDRESS		0xE0000000UL
#define NVIC_BASE_ADDRESS 								0xE000E100UL

// NVIC Registers:
#define NVIC_ISER0			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x00)
#define NVIC_ISER1			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x04)
#define NVIC_ISER2			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x08)
#define NVIC_ICER0			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x80)
#define NVIC_ICER1			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x84)
#define NVIC_ICER2			*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x88)

// Base Addresses For 'AHP' BUS Peripherals:
#define RCC_BASE_ADDRESS 								0x40021000UL

// Base Addresses For 'APB2' BUS Peripherals:
/*
 * GPIO[37 Pins] --> LQFP48 Package
 * A[0:15]		B[0:15]		C[13, 14, 15]		D[0, 2]
 */
#define AFIO_BASE_ADDRESS 								0x40010000UL
#define EXTI_BASE_ADDRESS 								0x40010400UL
#define GPIOA_BASE_ADDRESS 								0x40010800UL
#define GPIOB_BASE_ADDRESS 								0x40010C00UL
#define GPIOC_BASE_ADDRESS 								0x40011000UL
#define GPIOD_BASE_ADDRESS 								0x40011400UL
#define GPIOE_BASE_ADDRESS 								0x40011800UL
#define GPIOF_BASE_ADDRESS 								0x40011C00UL
#define GPIOG_BASE_ADDRESS 								0x40012000UL

// Peripheral Register:	RCC
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
}RCC_Typedef;

// Peripheral Register:	GPIO
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIOx_Typedef;

// Peripheral Register:	AFIO
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t Reserved; // 0x18
	volatile uint32_t MAPR2;
}AFIO_Typedef;

// Peripheral Register:	EXTI
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_Typedef;

// Peripheral Instants:
#define RCC 			((RCC_Typedef *  )RCC_BASE_ADDRESS)

// @ref GPIO_define
#define GPIOA			((GPIOx_Typedef *)GPIOA_BASE_ADDRESS)
#define GPIOB			((GPIOx_Typedef *)GPIOB_BASE_ADDRESS)
#define GPIOC			((GPIOx_Typedef *)GPIOC_BASE_ADDRESS)
#define GPIOD			((GPIOx_Typedef *)GPIOD_BASE_ADDRESS)
#define GPIOE			((GPIOx_Typedef *)GPIOE_BASE_ADDRESS)
#define GPIOF			((GPIOx_Typedef *)GPIOF_BASE_ADDRESS)
#define GPIOG			((GPIOx_Typedef *)GPIOG_BASE_ADDRESS)
#define AFIO			((AFIO_Typedef * )AFIO_BASE_ADDRESS)
#define EXTI			((EXTI_Typedef * )EXTI_BASE_ADDRESS)

// GPIO Clock Enable Macros:
#define RCC_AFIO_CLK_EN()			(RCC->APB2ENR |= (1<<0))
#define RCC_GPIOA_CLK_EN()			(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN()			(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN()			(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN()			(RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_CLK_EN()			(RCC->APB2ENR |= (1<<6))

// NVIC IRQ Enable Macros
#define NVIC_IRQ6_EXT0_Enable()					(NVIC_ISER0 |= (1<<6))
#define NVIC_IRQ7_EXT1_Enable()					(NVIC_ISER0 |= (1<<7))
#define NVIC_IRQ8_EXT2_Enable()					(NVIC_ISER0 |= (1<<8))
#define NVIC_IRQ9_EXT3_Enable()					(NVIC_ISER0 |= (1<<9))
#define NVIC_IRQ10_EXT4_Enable()		    	(NVIC_ISER0 |= (1<<10))
#define NVIC_IRQ23_EXT5_9_Enable()				(NVIC_ISER0 |= (1<<23))
#define NVIC_IRQ40_EXT10_15_Enable()			(NVIC_ISER1 |= (1<<8))	// 40-32 = 8

// NVIC IRQ Disable Macros
#define NVIC_IRQ6_EXT0_Disable()				(NVIC_ICER0 |= (1<<6))
#define NVIC_IRQ7_EXT1_Disable()				(NVIC_ICER0 |= (1<<7))
#define NVIC_IRQ8_EXT2_Disable()				(NVIC_ICER0 |= (1<<8))
#define NVIC_IRQ9_EXT3_Disable()				(NVIC_ICER0 |= (1<<9))
#define NVIC_IRQ10_EXT4_Disable()			    (NVIC_ICER0 |= (1<<10))
#define NVIC_IRQ23_EXT5_9_Disable()				(NVIC_ICER0 |= (1<<23))
#define NVIC_IRQ40_EXT10_15_Disable()			(NVIC_ICER1 |= (1<<8)) // 40-32 = 8

// IVT:
//-------------------------
// @ref EXTIx_IRQ
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40

// Generic Macros:


#endif /* INC_STM32F103X6_H_ */
