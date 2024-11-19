/*
 * STM32_F103C6_RCC.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Nouran S.
 */
#include "STM32_F103C6_RCC.h"

// Set and cleared by software to control the division factor of the APB
//	 0xx: HCLK not divided
//	 100: HCLK divided by 2
//	 101: HCLK divided by 4
//	 110: HCLK divided by 8
//	 111: HCLK divided by 16
const uint8_t APB_PreScaler[] = {0, 0, 0, 0, 1, 2, 3, 4};

// Set and cleared by software to control AHB clock division factor.
//	0xxx: SYSCLK not divided
//	1000: SYSCLK divided by 2
//	1001: SYSCLK divided by 4
//	1010: SYSCLK divided by 8
//	1011: SYSCLK divided by 16
//	1100: SYSCLK divided by 64
//	1101: SYSCLK divided by 128
//	1110: SYSCLK divided by 256
//	1111: SYSCLK divided by 512
const uint8_t AHB_PreScaler[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

uint32_t MCAL_RCC_Get_SysCLK_Freq()
{
	// Bits 3:2 SWS[1:0]: System clock switch status
	switch ((RCC->CFGR >> 2) & 0b11 )
	{
	case 0: // HSI oscillator used as system clock
		return HSI_RC_CLK;
		break;
	case 1: // HSE oscillator used as system clock
		return HSE_RC_CLK;
		break;
	case 2: // PLL used as system clock
		return 16000000;	// To Do ..
		break;
	default: // Not applicable
		break;
	}
}

uint32_t MCAL_RCC_Get_HCLK_Freq()
{
	// Bits 7:4 HPRE[3:0]: AHB prescaler
	uint8_t idx = (RCC->CFGR >> 4) & 0xF;
	return (MCAL_RCC_Get_SysCLK_Freq() >> (AHB_PreScaler[idx]) );

}

uint32_t MCAL_RCC_Get_PCLK1_Freq()
{
	// Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	uint8_t idx = (RCC->CFGR >> 8) & 0b111;
	return (MCAL_RCC_Get_HCLK_Freq() >> APB_PreScaler[idx]); // /2^idx
}

uint32_t MCAL_RCC_Get_PCLK2_Freq()
{
	// Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	uint8_t idx = (RCC->CFGR >> 11) & 0b111;
	return (MCAL_RCC_Get_HCLK_Freq() >> APB_PreScaler[idx]); // /2^idx
}



