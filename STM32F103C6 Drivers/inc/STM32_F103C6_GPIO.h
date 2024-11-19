/*
 * STM32_F103C6_GPIO.h
 *
 *  Created on: Oct 17, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32_F103C6_GPIO_H_
#define INC_STM32_F103C6_GPIO_H_

// Includes:
#include "stm32f103x6.h"

// Configuration Structure:
typedef struct{
	uint16_t GPIO_PinNumber;	// @ref GPIO_Pin_define
	uint8_t GPIO_Mode;			// @ref GPIO_Mode_define
	uint8_t GPIO_Output_Speed; // @ref GPIO_Speed_define
}GPIO_PinConfig_t;

// Macros Configuration References:
//-----------------------------------
// @ref GPIO_Pin_define
#define GPIO_Pin_0							((uint16_t)0x0001)
#define GPIO_Pin_1							((uint16_t)0x0002)
#define GPIO_Pin_2  						((uint16_t)0x0004)
#define GPIO_Pin_3  						((uint16_t)0x0008)
#define GPIO_Pin_4							((uint16_t)0x0010)
#define GPIO_Pin_5							((uint16_t)0x0020)
#define GPIO_Pin_6							((uint16_t)0x0040)
#define GPIO_Pin_7							((uint16_t)0x0080)
#define GPIO_Pin_8							((uint16_t)0x0100)
#define GPIO_Pin_9							((uint16_t)0x0200)
#define GPIO_Pin_10							((uint16_t)0x0400)
#define GPIO_Pin_11							((uint16_t)0x0800)
#define GPIO_Pin_12 						((uint16_t)0x1000)
#define GPIO_Pin_13							((uint16_t)0x2000)
#define GPIO_Pin_14							((uint16_t)0x4000)
#define GPIO_Pin_15							((uint16_t)0x8000)
#define GPIO_Pin_ALL						((uint16_t)0xFFFF)
#define GPIO_Pin_MASK						0x0000FFFFu

/* @ref GPIO_Mode_define
 * 0: Analog mode
 * 1: Floating input (reset state)
 * 2: Input with pull-up
 * 3: Input with pull-down
 * 4: General purpose output push-pull
 * 5: General purpose output Open-drain
 * 6: Alternate function output Push-pull
 * 7: Alternate function output Open-drain
 * 8: Alternate function input
 */
#define GPIO_Mode_Analog					0x00000000u
#define GPIO_Mode_Input_Floating			0x00000001u
#define GPIO_Mode_Input_PullUp	  		  	0x00000002u
#define GPIO_Mode_Input_PullDown			0x00000003u
#define GPIO_Mode_Output_PullUp				0x00000004u
#define GPIO_Mode_Output_PullDown			0x00000005u
#define GPIO_Mode_Output_ALT_PullUp			0x00000006u
#define GPIO_Mode_Output_ALT_PullDown		0x00000007u
#define GPIO_Mode_Input_ALT					0x00000008u

// @ref GPIO_Pin_State
#define GPIO_Pin_Set						1
#define GPIO_Pin_Reset						0

// @ref GPIO_Return_Lock
#define GPIO_Return_Lock_Enable				1
#define GPIO_Return_Lock_Disable			0

/* @ref GPIO_Speed_define
 * 1: Output mode, max speed 10 MHz.
 * 2: Output mode, max speed 2 MHz.
 * 3: Output mode, max speed 50 MHz
 */
#define GPIO_Speed_10MHz					0x00000001u
#define GPIO_Speed_2MHz					    0x00000002u
#define GPIO_Speed_50MHz					0x00000003u

// APIs Supported by "MCAL GPIO DRIVER":
void MCAL_GPIO_INIT(GPIOx_Typedef* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeINIT(GPIOx_Typedef* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIOx_Typedef* GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIOx_Typedef* GPIOx);

void MCAL_GPIO_WritePin(GPIOx_Typedef* GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort(GPIOx_Typedef* GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin(GPIOx_Typedef* GPIOx, uint16_t PinNumber);

void MCAL_GPIO_LockPin(GPIOx_Typedef* GPIOx, uint16_t PinNumber, uint8_t *state);

#endif /* INC_STM32_F103C6_GPIO_H_ */
