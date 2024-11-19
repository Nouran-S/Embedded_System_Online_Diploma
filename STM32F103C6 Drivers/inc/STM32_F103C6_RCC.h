/*
 * STM32_F103C6_RCC.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32_F103C6_RCC_H_
#define INC_STM32_F103C6_RCC_H_

// Includes
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

// Macros
#define HSI_RC_CLK		(uint32_t)16000000
#define HSE_RC_CLK		(uint32_t)8000000

// APIs
uint32_t MCAL_RCC_Get_SysCLK_Freq();
uint32_t MCAL_RCC_Get_HCLK_Freq();
uint32_t MCAL_RCC_Get_PCLK1_Freq();
uint32_t MCAL_RCC_Get_PCLK2_Freq();

#endif /* INC_STM32_F103C6_RCC_H_ */
