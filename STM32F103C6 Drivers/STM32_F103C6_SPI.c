/*
 * STM32_F103C6_SPI.c
 *
 *  Created on: Dec 9, 2024
 *      Author: Nouran S.
 */

#include "STM32_F103C6_SPI.h"

#define SPI_SR_RXNE			((uint8_t)0x01)
#define SPI_SR_TXE			((uint8_t)0x02)
#define SPI1_index				0
#define SPI2_index				1

SPI_Config_t* SPI_Arr[2] = {NULL , NULL};

void MCAL_SPI_Init(SPI_Typedef* SPIx, SPI_Config_t* SpiCfg)
{
	// Safety for the control registers
	uint32_t temp_cr1 = 0x00;
	uint32_t temp_cr2 = 0x00;

	if(SPIx == SPI1)
	{
		SPI_Arr[SPI1_index] = SpiCfg;
		RCC_SPI1_CLK_EN();
	}
	else // SPI2
	{
		SPI_Arr[SPI2_index] = SpiCfg;
		RCC_SPI2_CLK_EN();
	}

	// CR1.1 Bit.6 SPE: SPI enable
	temp_cr1 |= (1<<6);

	// CR.1 Bit.2 MSTR: Master selection
	temp_cr1 |= (SpiCfg->DeviceMode<<2);

	// SPI Communication Mode
	if(SpiCfg->CommMode == SPI_CommMode_2Lines)
	{
		temp_cr1 &= ~(1<<15);
		temp_cr1 &= ~(1<<14);
		temp_cr1 &= ~(1<<10);
	}
	else if(SpiCfg->CommMode == SPI_CommMode_2Lines_Rx)
	{
		temp_cr1 &= ~(1<<15);
		temp_cr1 &= ~(1<<14);
		temp_cr1 |= (1<<10);
	}

	else if(SpiCfg->CommMode == SPI_CommMode_1Lines_Rx)
	{
		temp_cr1 |= (1<<15);
		temp_cr1 &= ~(1<<14);
		temp_cr1 |= (1<<10);
	}

	else if(SpiCfg->CommMode == SPI_CommMode_1Lines_Tx)
	{
		temp_cr1 |= (1<<15);
		temp_cr1 |= (1<<14);
		temp_cr1 |= (1<<10);
	}

	temp_cr1 |= (SpiCfg->FrameFormat<<7);		// Frame Format
	temp_cr1 |= (SpiCfg->DataSize<<11);		   	// Data Size
	temp_cr1 |= (SpiCfg->ClkPolarity<<1);      	// Clk Polarity
	temp_cr1 |= (SpiCfg->ClkPhase<<0);         	// Clk Phase
	temp_cr1 |= (SpiCfg->ClkFreq << 3);		   	// Clk Freq

	// NSS
	if(SpiCfg->NSS == SPI_NSS_HW_Output)
		temp_cr2 |= (1<<2);

	else if(SpiCfg->NSS == SPI_NSS_HW_Input)
		temp_cr2 &= ~(1<<2);

	else if(SpiCfg->NSS == SPI_NSS_SW_Reset)
		temp_cr1 |= (1<<9);

	else if(SpiCfg->NSS == SPI_NSS_SW_Set)
		temp_cr1 |= (1<<8) | (1<<9);

	// Interrupt
	if(SpiCfg->IRQ_Enable != SPI_IRQ_Enable_Null)
	{
		temp_cr2 |= SpiCfg->IRQ_Enable;
		if(SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable();
		else if(SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable();
	}

	SPIx->CR1 = temp_cr1;
	SPIx->CR2 = temp_cr2;

	MCAL_SPI_GPIO_Init(SPIx);
}

void MCAL_SPI_DeInit(SPI_Typedef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable();
		RCC_SPI1_RESET();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable();
		RCC_SPI2_RESET();
	}
}

void MCAL_SPI_GPIO_Init(SPI_Typedef* SPIx)
{
	/*
	 * SPI.1
	 * NSS  --> PA.4
	 * SCK  --> PA.5
	 * MISO --> PA.6
	 * MOSI --> PA.7
	 */

	/*
	 * SPI.2
	 * NSS  --> PB.12
	 * SCK  --> PB.13
	 * MISO --> PB.14
	 * MOSI --> PB.15
	 */

	GPIOx_Typedef* GPIOx;
	GPIO_PinConfig_t pinCfg;

	uint16_t NSSPin  = 0;
	uint16_t SCKPin  = 0;
	uint16_t MISOPin = 0;
	uint16_t MOSIPin = 0;
	uint8_t SPI_index = 0;

	if(SPIx == SPI1)
	{
		GPIOx = GPIOA;
		NSSPin = GPIO_Pin_4;
		SCKPin = GPIO_Pin_5;
		MISOPin = GPIO_Pin_6;
		MOSIPin = GPIO_Pin_7;
		RCC_GPIOA_CLK_EN();
		SPI_index = SPI1_index;
	}
	else if(SPIx == SPI2)
	{
		GPIOx = GPIOB;
		NSSPin = GPIO_Pin_12;
		SCKPin = GPIO_Pin_13;
		MISOPin = GPIO_Pin_14;
		MOSIPin = GPIO_Pin_15;
		RCC_GPIOB_CLK_EN();
		SPI_index = SPI2_index;
	}

	if(SPI_Arr[SPI_index]->DeviceMode == SPI_DeviceMode_Master)
	{
		// NSS  --> PA.4
		switch (SPI_Arr[SPI_index]->NSS)
		{
		case SPI_NSS_HW_Input:
			// Hardware master/slave: Input floating/ Input pull-up / Input pull-down
			pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
			pinCfg.GPIO_PinNumber = NSSPin;
			MCAL_GPIO_INIT(GPIOx, &pinCfg);
			break;
		case SPI_NSS_HW_Output:
			//  Hardware master/ NSS output enabled Alternate function push-pull
			pinCfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
			pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
			pinCfg.GPIO_PinNumber = NSSPin;
			MCAL_GPIO_INIT(GPIOx, &pinCfg);
			break;
		default:
			// Software Not used. Can be used as a GPIO
			break;
		}
		// SCK  --> PA.5
		// Master Alternate function push-pull
		pinCfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		pinCfg.GPIO_PinNumber = SCKPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);

		// MISO --> PA.6
		//  Full duplex / master Input floating / Input pull-up
		pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
		pinCfg.GPIO_PinNumber = MISOPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);

		// MOSI --> PA.7
		// Full duplex / master Alternate function push-pull
		pinCfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		pinCfg.GPIO_PinNumber = MOSIPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);
	}
	else	// Slave
	{
		// NSS
		if(SPI_Arr[SPI_index]->NSS == SPI_NSS_HW_Input)
		{
			pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
			pinCfg.GPIO_PinNumber = NSSPin;
			MCAL_GPIO_INIT(GPIOx, &pinCfg);
		}

		// SCK
		// Slave Input floating
		pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
		pinCfg.GPIO_PinNumber = SCKPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);

		// MISO
		// Full duplex /  slave (point to point) Alternate function push-pull
		pinCfg.GPIO_Mode = GPIO_Mode_Output_ALT_PullUp;
		pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		pinCfg.GPIO_PinNumber = MISOPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);

		// MOSI
		// Full duplex / master Alternate function push-pull
		pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
		pinCfg.GPIO_PinNumber = MOSIPin;
		MCAL_GPIO_INIT(GPIOx, &pinCfg);
	}
}


void MCAL_SPI_Tx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling)
{
	if(polling == SPI_Polling_Enable)
		while(!(SPIx->SR & SPI_SR_TXE));

	SPIx->DR = *data;
}

void MCAL_SPI_Rx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling)
{
	if(polling == SPI_Polling_Enable)
		while(!(SPIx->SR & SPI_SR_RXNE));

	*data = SPIx->DR;
}

void MCAL_SPI_Tx_Rx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling)
{
	if(polling == SPI_Polling_Enable)
		while(!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *data;

	if(polling == SPI_Polling_Enable)
		while(!(SPIx->SR & SPI_SR_RXNE));
	*data = SPIx->DR;
}

// SPI IRQ Handler
//void SPI1_IRQHandler() {
//	struct S_IRQ_Src src;
//	src.TXE = ((SPI1->SR & (1 << 1)) >> 1);
//	src.RXNE = ((SPI1->SR & (1 << 0)) >> 0);
//	src.ERRIE = ((SPI1->SR & (1 << 4)) >> 4);
//
//	if (SPI_Arr[SPI1_index] && SPI_Arr[SPI1_index]->P_IRQ_CallBack)
//		SPI_Arr[SPI1_index]->P_IRQ_CallBack(src);
//
//}
//
//void SPI2_IRQHandler() {
//	struct S_IRQ_Src src;
//	src.TXE = ((SPI2->SR & (1 << 1)) >> 1);
//	src.RXNE = ((SPI2->SR & (1 << 0)) >> 0);
//	src.ERRIE = ((SPI2->SR & (1 << 4)) >> 4);
//
//	if (SPI_Arr[SPI2_index] && SPI_Arr[SPI2_index]->P_IRQ_CallBack)
//		SPI_Arr[SPI2_index]->P_IRQ_CallBack(src);
//}
