/*
 * KeyPad.c
 *
 *  Created on: Oct 18, 2024
 *      Author: Nouran S.
 */

#include <stdint.h>
#include "KeyPad.h"

uint16_t KeyPad_ROWs[] = {KeyPad_Row_0, KeyPad_Row_1, KeyPad_Row_2, KeyPad_Row_3};
uint16_t KeyPad_COLs[] = {KeyPad_Col_0, KeyPad_Col_1, KeyPad_Col_2, KeyPad_Col_3};
uint16_t KeyPad_Keys[4][4] = {
		{'7', '4', '1', ' '},
		{'8', '5', '2', '0'},
		{'9', '6', '3', '='},
		{'/', '*', '-', '+'}};

void KeyPad_INIT()
{
	// RCC CLK Enable
	if(KeyPad_PORT == GPIOA)
		RCC_GPIOA_CLK_EN();
	if(KeyPad_PORT == GPIOB)
		RCC_GPIOB_CLK_EN();
	if(KeyPad_PORT == GPIOC)
		RCC_GPIOC_CLK_EN();
	if(KeyPad_PORT == GPIOD)
		RCC_GPIOD_CLK_EN();
	if(KeyPad_PORT == GPIOE)
		RCC_GPIOE_CLK_EN();

	GPIO_PinConfig_t pinCfg;

	// Rows are output
	pinCfg.GPIO_Mode = GPIO_Mode_Output_PullUp;
	pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;

	pinCfg.GPIO_PinNumber = KeyPad_ROWs[0];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_ROWs[1];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_ROWs[2];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_ROWs[3];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	// Columns are output
	pinCfg.GPIO_Mode = GPIO_Mode_Output_PullUp;
	pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;

	pinCfg.GPIO_PinNumber = KeyPad_Col_0;
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_COLs[1];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_COLs[2];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = KeyPad_COLs[3];
	MCAL_GPIO_INIT(KeyPad_PORT, &pinCfg);
	MCAL_GPIO_WritePort(KeyPad_PORT, 0xFF);
}

void KeyPad_GetKey(uint8_t *key)
{
	*key = '\0';
	for (int i = 0; i < 4; i++)
	{
		MCAL_GPIO_WritePin(KeyPad_PORT, KeyPad_COLs[0], GPIO_Pin_Set);
		MCAL_GPIO_WritePin(KeyPad_PORT, KeyPad_COLs[1], GPIO_Pin_Set);
		MCAL_GPIO_WritePin(KeyPad_PORT, KeyPad_COLs[2], GPIO_Pin_Set);
		MCAL_GPIO_WritePin(KeyPad_PORT, KeyPad_COLs[3], GPIO_Pin_Set);
		MCAL_GPIO_WritePin(KeyPad_PORT, KeyPad_COLs[i], GPIO_Pin_Reset);

		for (int j = 0; j < 4; j++)
			if((MCAL_GPIO_ReadPin(KeyPad_PORT, KeyPad_ROWs[j])) == 0)
			{
				while((MCAL_GPIO_ReadPin(KeyPad_PORT, KeyPad_ROWs[j])) == 0);
				*key = KeyPad_Keys[i][j];
			} // end if(value == 0)
	} // end for (int i = 0; i < 4; i++)
}
