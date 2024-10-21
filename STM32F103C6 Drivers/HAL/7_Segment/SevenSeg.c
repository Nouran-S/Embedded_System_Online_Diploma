/*
 * SevenSeg.c
 *
 *  Created on: Oct 19, 2024
 *      Author: Nouran S.
 */

#include "SevenSeg.h"

uint8_t SevenSeg_Numbers_CA[] = {Seg_CA_0, Seg_CA_1, Seg_CA_2, Seg_CA_3, Seg_CA_4, Seg_CA_5, Seg_CA_6, Seg_CA_7, Seg_CA_8, Seg_CA_9};
uint8_t SevenSeg_Numbers_CC[] = {Seg_CC_0, Seg_CC_1, Seg_CC_2, Seg_CC_3, Seg_CC_4, Seg_CC_5, Seg_CC_6, Seg_CC_7, Seg_CC_8, Seg_CC_9};

void SevenSeg_INIT()
{
	// RCC CLK Enable
	if(SevenSeg_PORT == GPIOA)
		RCC_GPIOA_CLK_EN();
	if(SevenSeg_PORT == GPIOB)
		RCC_GPIOB_CLK_EN();
	if(SevenSeg_PORT == GPIOC)
		RCC_GPIOC_CLK_EN();
	if(SevenSeg_PORT == GPIOD)
		RCC_GPIOD_CLK_EN();
	if(SevenSeg_PORT == GPIOE)
		RCC_GPIOE_CLK_EN();

	// All The Pins are output push-pull with speed 10M Hz
	GPIO_PinConfig_t pinCfg;
	pinCfg.GPIO_Mode = GPIO_Mode_Output_PullUp;
	pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;

	pinCfg.GPIO_PinNumber = SevenSeg_PinA;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinB;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinC;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinD;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinE;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinF;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = SevenSeg_PinG;
	MCAL_GPIO_INIT(SevenSeg_PORT, &pinCfg);
}

void SevenSeg_Write(uint8_t number)
{
	MCAL_GPIO_WritePort(SevenSeg_PORT, SevenSeg_Numbers_CC[number] << SevenSeg_1stPin);
//	MCAL_GPIO_WritePort(SevenSeg_PORT, SevenSeg_Numbers_CA[number] << SevenSeg_1stPin);
}
