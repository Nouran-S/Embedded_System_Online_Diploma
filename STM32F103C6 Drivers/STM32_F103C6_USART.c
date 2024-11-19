/*
 * STM32_F103C6_USART.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Nouran S.
 */

#include "STM32_F103C6_USART.h"

// BaudRate Calculation:
#define USARTDIV(__PCLK__, __BAUD__)            (uint32_t)(__PCLK__ / (16 * __BAUD__))
#define Mantissa(__PCLK__, __BAUD__)            (uint32_t)(USARTDIV(__PCLK__, __BAUD__))
#define USARTDIV_MUL100(__PCLK__, __BAUD__)     (uint32_t)((25*__PCLK__) / (4 * __BAUD__))
#define Mantissa_MUL100(__PCLK__, __BAUD__)     (uint32_t)(100 * USARTDIV(__PCLK__, __BAUD__))
#define DIV_Fraction(__PCLK__, __BAUD__)        (uint32_t)(((USARTDIV_MUL100(__PCLK__, __BAUD__) - Mantissa_MUL100(__PCLK__, __BAUD__)) * 16) / 100)
#define USART_BRR_Reg(__PCLK__, __BAUD__)       (((Mantissa(__PCLK__, __BAUD__)) << 4) | (DIV_Fraction(__PCLK__, __BAUD__)))

// Generic Variables:
USART_Config_t* Cfg_g[3] = {NULL, NULL, NULL};

// Generic Functions:

// APIs
void MCAL_USART_INIT(USART_Typedef* USARTx, USART_Config_t* USART_Cfg)
{
	uint32_t PCLK, BRR_Value;

	// Enable RCC CLK For USART
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		// Set the global configuration variable
		Cfg_g[0] = USART_Cfg;
	}

	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
		// Set the global configuration variable
		Cfg_g[1] = USART_Cfg;
	}

	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		// Set the global configuration variable
		Cfg_g[2] = USART_Cfg;
	}

	// Enable USART: Bit 13 UE
	USARTx->CR1 |= (1<<13);

	// Enable Tx/Rx For USART
	USARTx->CR1 |= USART_Cfg->USART_Mode;

	// Program the M bit in USART_CR1 to define the word length
	USARTx->CR1 |= USART_Cfg->PayLoad_Length;

	// Program the Parity using  PCE & PS bits in USART_CR1
	USARTx->CR1 |= USART_Cfg->Parity;

	// Program the number of stop bits in USART_CR2
	USARTx->CR2 |= USART_Cfg->StopBits;

	// Program the flow control in USART_CR3
	// Bit9 CTSE: CTS enable & Bit8  RTSE: RTS enable
	USARTx->CR3 |= USART_Cfg->HW_FlowControl;

	// Program baud rate register (BRR)
	// PCLK1(USART2, 3) & PCLK2(USART1)
	if(USARTx == USART1)
		PCLK = MCAL_RCC_Get_PCLK2_Freq();
	else // USARTx == USART2 || USARTx == USART3
		PCLK = MCAL_RCC_Get_PCLK1_Freq();

	BRR_Value = USART_BRR_Reg(PCLK, USART_Cfg->BaudRate);
	USARTx->BRR = BRR_Value;

	// Enable/Disable Interrupt
	if(USART_Cfg->IRQEN != USART_IRQEN_Null)
	{
		USARTx->CR1 |= USART_Cfg->IRQEN;
		// Enable NVIC For USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable();
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable();
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable();
	}

	MCAL_USART_GPIO_SetPins(USARTx);

}

void MCAL_USART_Reset(USART_Typedef* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable();
	}

	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable();
	}

	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable();
	}

}

void MCAL_USART_GPIO_SetPins(USART_Typedef* USARTx)
{
	GPIO_PinConfig_t Pin_Cfg;

	// USART1 ..
	if(USARTx == USART1)
	{
		RCC_GPIOA_CLK_EN();
		// Tx : PA9
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_9;
		MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);

		// Rx : PA10
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_ALT;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_10;
		MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);

		if(Cfg_g[0]->HW_FlowControl == USART_HW_FlowControl_CTC || Cfg_g[0]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// CTC: PA11
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_Floating;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_11;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}

		if(Cfg_g[0]->HW_FlowControl == USART_HW_FlowControl_RTC || Cfg_g[0]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// RTC: PA12
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
			Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_12;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}
	}


	// USART2 ..
	else if(USARTx == USART2)
	{
		RCC_GPIOA_CLK_EN();
		// Tx : PA2
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_2;
		MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);

		// Rx : PA3
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_ALT;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_3;
		MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);

		if(Cfg_g[1]->HW_FlowControl == USART_HW_FlowControl_CTC || Cfg_g[1]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// CTC: PA0
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_Floating;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_0;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}

		if(Cfg_g[1]->HW_FlowControl == USART_HW_FlowControl_RTC || Cfg_g[1]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// RTC: PA1
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
			Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_1;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}
	}


	// USART1 ..
	else if(USARTx == USART3)
	{
		RCC_GPIOB_CLK_EN();
		// Tx : PB10
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_10;
		MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);

		// Rx : PB11
		Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_ALT;
		Pin_Cfg.GPIO_PinNumber = GPIO_Pin_11;
		MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);

		if(Cfg_g[2]->HW_FlowControl == USART_HW_FlowControl_CTC || Cfg_g[2]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// CTC: PB13
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Input_Floating;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_13;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
		}

		if(Cfg_g[2]->HW_FlowControl == USART_HW_FlowControl_RTC || Cfg_g[2]->HW_FlowControl == USART_HW_FlowControl_RTC_CTC)
		{
			// RTC: PB14
			Pin_Cfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
			Pin_Cfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
			Pin_Cfg.GPIO_PinNumber = GPIO_Pin_14;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
		}
	}

//	RCC_AFIO_CLK_EN();
}

void MCAL_USART_SendData(USART_Typedef* USARTx, uint16_t* data, enum PollingMech PollingEN)
{
	// Wait till TXE Flag is set in the SR
	if(PollingEN == Enable)
		while(!(USARTx->SR & (1<<7)));
	if(USARTx == USART1)
	{
		if(Cfg_g[0]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			USARTx->DR =  (*data & (uint16_t)0x1FF);
		else
			USARTx->DR =  (*data & (uint16_t)0xFF);
	}

	else if(USARTx == USART2)
	{
		if(Cfg_g[1]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			USARTx->DR =  (*data & (uint16_t)0x1FF);
		else
			USARTx->DR =  (*data & (uint16_t)0xFF);
	}

	else if(USARTx == USART3)
	{
		if(Cfg_g[2]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			USARTx->DR =  (*data & (uint16_t)0x1FF);
		else
			USARTx->DR =  (*data & (uint16_t)0xFF);
	}
}

void MCAL_USART_ReceiveData(USART_Typedef* USARTx, uint16_t* data, enum PollingMech PollingEN)
{
	// Bit 5 RXNE: Read data register not empty
	if(PollingEN == Enable)
		while(!(USARTx->SR & (1<<5)));

	if(USARTx == USART1)
	{
		// The Length of the data = 9 Bits
		if(Cfg_g[0]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			if(Cfg_g[0]->Parity == USART_Parity_Null)
				// No Parity so receive all the 9 bits
				*((uint16_t*)data) = USARTx->DR;
			else
				// There is a Parity so receive only 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;

		// The Length of the data = 8 Bits
		else
			if(Cfg_g[0]->Parity == USART_Parity_Null)
				// No Parity so receive all the 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;
			else
				// There is a Parity so receive only 7 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0x7F;
	}

	else if(USARTx == USART2)
	{
		// The Length of the data = 9 Bits
		if(Cfg_g[1]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			if(Cfg_g[1]->Parity == USART_Parity_Null)
				// No Parity so receive all the 9 bits
				*((uint16_t*)data) = USARTx->DR;
			else
				// There is a Parity so receive only 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;

		// The Length of the data = 8 Bits
		else
			if(Cfg_g[1]->Parity == USART_Parity_Null)
				// No Parity so receive all the 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;
			else
				// There is a Parity so receive only 7 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0x7F;
	}

	else if(USARTx == USART3)
	{
		// The Length of the data = 9 Bits
		if(Cfg_g[2]->PayLoad_Length == USART_PayLoad_Length_9Bits)
			if(Cfg_g[2]->Parity == USART_Parity_Null)
				// No Parity so receive all the 9 bits
				*((uint16_t*)data) = USARTx->DR;
			else
				// There is a Parity so receive only 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;

		// The Length of the data = 8 Bits
		else
			if(Cfg_g[2]->Parity == USART_Parity_Null)
				// No Parity so receive all the 8 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0xFF;
			else
				// There is a Parity so receive only 7 bits
				*((uint16_t*)data) = USARTx->DR & (uint8_t)0x7F;
	}

}

void MCAL_USART_WaitTC(USART_Typedef* USARTx)
{
	// Wait till TC Flag is set in the SR
	while(!(USARTx->SR & (1<<6)));
}


// ISR
void USART1_IRQHandler()
{
	if(Cfg_g[0]->PTR_IRQ_CallBack != NULL)
		Cfg_g[0]->PTR_IRQ_CallBack();
}

void USART2_IRQHandler()
{
	if(Cfg_g[1]->PTR_IRQ_CallBack != NULL)
		Cfg_g[1]->PTR_IRQ_CallBack();
}

void USART3_IRQHandler()
{
	if(Cfg_g[2]->PTR_IRQ_CallBack != NULL)
		Cfg_g[2]->PTR_IRQ_CallBack();
}









