/*
 * STM32_F103C6_EXTI.h
 *
 *  Created on: Oct 19, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32_F103C6_EXTI_H_
#define INC_STM32_F103C6_EXTI_H_

// Includes:
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

// Configuration Structure:
typedef struct{
	GPIOx_Typedef*	GPIO_Port;			// @ref: GPIO_define
	uint16_t 	   	GPIO_Pin;			// @ref: GPIO_Pin_define
	uint16_t      	EXTI_Line;			// @ref: EXTIx
	uint8_t 	   	IRQ_Number;			// @ref: EXTIx_IRQ
}EXTI_GPIO_Maping_t;

typedef struct{
	EXTI_GPIO_Maping_t EXTI_Pin;		// @ref: EXTIx_Pyx
	uint8_t			   Trigger_Case;	// @ref: EXTI_Trigger_define
	uint8_t			   IRQ_EN;			// @ref: EXTI_IRQ_define
	void (*IRQ_CallBack_ptr)();			// Pointer to the function which will be called once the IRQ happen
}EXTI_PinConfig_t;

// Configuration Enum:
typedef enum{
	PAx,
	PBx,
	PCx,
	PDx,
	PEx,
	PFx,
	PGx,
}EXTI_SRC_Input_t;

// Macros Configuration References:
//-----------------------------------
// @ref EXTIx
#define EXTI0		0
#define EXTI1 		1
#define EXTI2 		2
#define EXTI3 		3
#define EXTI4 		4
#define EXTI5 		5
#define EXTI6 		6
#define EXTI7 		7
#define EXTI8 		8
#define EXTI9 		9
#define EXTI10 		10
#define EXTI11 		11
#define EXTI12 		12
#define EXTI13 		13
#define EXTI14 		14
#define EXTI15		15

// @ref EXTIx_Pyx
// EXTI0
#define EXTI0_PA0		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_0, EXTI0, EXTI0_IRQ}
#define EXTI0_PB0		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_0, EXTI0, EXTI0_IRQ}
#define EXTI0_PC0		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_0, EXTI0, EXTI0_IRQ}
#define EXTI0_PD0		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_0, EXTI0, EXTI0_IRQ}

// EXTI1
#define EXTI1_PA1		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_1, EXTI1, EXTI1_IRQ}
#define EXTI1_PB1		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_1, EXTI1, EXTI1_IRQ}
#define EXTI1_PC1		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_1, EXTI1, EXTI1_IRQ}
#define EXTI1_PD1		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_1, EXTI1, EXTI1_IRQ}

// EXTI2
#define EXTI2_PA2		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_2, EXTI2, EXTI2_IRQ}
#define EXTI2_PB2		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_2, EXTI2, EXTI2_IRQ}
#define EXTI2_PC2		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_2, EXTI2, EXTI2_IRQ}
#define EXTI2_PD2		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_2, EXTI2, EXTI2_IRQ}

// EXTI3
#define EXTI3_PA3		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_3, EXTI3, EXTI3_IRQ}
#define EXTI3_PB3		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_3, EXTI3, EXTI3_IRQ}
#define EXTI3_PC3		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_3, EXTI3, EXTI3_IRQ}
#define EXTI3_PD3		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_3, EXTI3, EXTI3_IRQ}

// EXTI4
#define EXTI4_PA4		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_4, EXTI4, EXTI4_IRQ}
#define EXTI4_PB4		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_4, EXTI4, EXTI4_IRQ}
#define EXTI4_PC4		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_4, EXTI4, EXTI4_IRQ}
#define EXTI4_PD4		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_4, EXTI4, EXTI4_IRQ}

// EXTI5
#define EXTI5_PA5		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_5, EXTI5, EXTI5_IRQ}
#define EXTI5_PB5		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_5, EXTI5, EXTI5_IRQ}
#define EXTI5_PC5		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_5, EXTI5, EXTI5_IRQ}
#define EXTI5_PD5		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_5, EXTI5, EXTI5_IRQ}

// EXTI6
#define EXTI6_PA6		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_6, EXTI6, EXTI6_IRQ}
#define EXTI6_PB6		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_6, EXTI6, EXTI6_IRQ}
#define EXTI6_PC6		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_6, EXTI6, EXTI6_IRQ}
#define EXTI6_PD6		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_6, EXTI6, EXTI6_IRQ}

// EXTI7
#define EXTI7_PA7		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_7, EXTI7, EXTI7_IRQ}
#define EXTI7_PB7		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_7, EXTI7, EXTI7_IRQ}
#define EXTI7_PC7		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_7, EXTI7, EXTI7_IRQ}
#define EXTI7_PD7		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_7, EXTI7, EXTI7_IRQ}

// EXTI8
#define EXTI8_PA8		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_8, EXTI8, EXTI8_IRQ}
#define EXTI8_PB8		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_8, EXTI8, EXTI8_IRQ}
#define EXTI8_PC8		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_8, EXTI8, EXTI8_IRQ}
#define EXTI8_PD8		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_8, EXTI8, EXTI8_IRQ}

// EXTI9
#define EXTI9_PA9		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_9, EXTI9, EXTI9_IRQ}
#define EXTI9_PB9		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_9, EXTI9, EXTI9_IRQ}
#define EXTI9_PC9		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_9, EXTI9, EXTI9_IRQ}
#define EXTI9_PD9		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_9, EXTI9, EXTI9_IRQ}

// EXTI10
#define EXTI10_PA10		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_10, EXTI10, EXTI10_IRQ}
#define EXTI10_PB10		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_10, EXTI10, EXTI10_IRQ}
#define EXTI10_PC10		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_10, EXTI10, EXTI10_IRQ}
#define EXTI10_PD10		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_10, EXTI10, EXTI10_IRQ}

// EXTI11
#define EXTI11_PA11		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_11, EXTI11, EXTI11_IRQ}
#define EXTI11_PB11		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_11, EXTI11, EXTI11_IRQ}
#define EXTI11_PC11		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_11, EXTI11, EXTI11_IRQ}
#define EXTI11_PD11		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_11, EXTI11, EXTI11_IRQ}

// EXTI12
#define EXTI12_PA12		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_12, EXTI12, EXTI12_IRQ}
#define EXTI12_PB12		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_12, EXTI12, EXTI12_IRQ}
#define EXTI12_PC12		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_12, EXTI12, EXTI12_IRQ}
#define EXTI12_PD12		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_12, EXTI12, EXTI12_IRQ}

// EXTI13
#define EXTI13_PA13		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_13, EXTI13, EXTI13_IRQ}
#define EXTI13_PB13		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_13, EXTI13, EXTI13_IRQ}
#define EXTI13_PC13		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_13, EXTI13, EXTI13_IRQ}
#define EXTI13_PD13		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_13, EXTI13, EXTI13_IRQ}

// EXTI14
#define EXTI14_PA14		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_14, EXTI14, EXTI14_IRQ}
#define EXTI14_PB14		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_14, EXTI14, EXTI14_IRQ}
#define EXTI14_PC14		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_14, EXTI14, EXTI14_IRQ}
#define EXTI14_PD14		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_14, EXTI14, EXTI14_IRQ}

// EXTI15
#define EXTI15_PA15		(EXTI_GPIO_Maping_t){GPIOA, GPIO_Pin_15, EXTI15, EXTI15_IRQ}
#define EXTI15_PB15		(EXTI_GPIO_Maping_t){GPIOB, GPIO_Pin_15, EXTI15, EXTI15_IRQ}
#define EXTI15_PC15		(EXTI_GPIO_Maping_t){GPIOC, GPIO_Pin_15, EXTI15, EXTI15_IRQ}
#define EXTI15_PD15		(EXTI_GPIO_Maping_t){GPIOD, GPIO_Pin_15, EXTI15, EXTI15_IRQ}

// @ref: EXTI_Trigger_define
#define EXTI_Trigger_Rising				0
#define EXTI_Trigger_Falling			1
#define EXTI_Trigger_FallingRising		2

// @ref: EXTI_IRQ_define
#define  EXTI_IRQ_Disable					0
#define  EXTI_IRQ_Enable					1


// APIs Supported by "MCAL EXTI DRIVER":
void MCAL_EXTI_DeInit();
void MCAL_EXTI_INIT(EXTI_PinConfig_t* PinCfg);
void MCAL_EXTI_Update(EXTI_PinConfig_t* PinCfg);

#endif /* INC_STM32_F103C6_EXTI_H_ */
