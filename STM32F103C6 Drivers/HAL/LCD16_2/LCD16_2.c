/*
 * LCD16_2.c
 *
 *  Created on: Oct 18, 2024
 *      Author: Nouran S.
 */

#include "LCD16_2.h"

void LCD_INIT()
{
	// Initialize the GPIO Pins For LCD
	delay_ms(20);
	LCD_GPIO_INIT();

	// Initialize LCD
	delay_ms(15);
	LCD_Clear();
	LCD_CMD(LCD_1st_Row);
	LCD_CMD(LCD_DISPLAY_ON_CURSUR_OFF);
	LCD_CMD(LCD_FUNCTION_8Bits_2Lines);
	LCD_CMD(LCD_ENTRY_MODE);
}

void LCD_CMD(uint8_t command)
{
	LCD_IsBusy();
	MCAL_GPIO_WritePort(LCD_DATA_PORT, command);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_Pin_Reset);
	delay_ms(1);
	LCD_Puls();
}

void LCD_Char(uint8_t data)
{
	LCD_IsBusy();
	MCAL_GPIO_WritePort(LCD_DATA_PORT, data);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_Pin_Set);
	delay_ms(1);
	LCD_Puls();
}

void LCD_Str(uint8_t* str)
{
	for(uint64_t i=0; str[i] != '\0'; i++)
		LCD_Char(str[i]);
}

void LCD_IsBusy()
{
	GPIO_PinConfig_t pinCfg;

	// Data Pins (0-->7) are input
	pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;

	pinCfg.GPIO_PinNumber = GPIO_Pin_0;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_1;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_2;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_3;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_4;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_5;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_6;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_7;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	// RW = 1[Read] & RS = 0[CMD]
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_Pin_Set);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_Pin_Reset);
	LCD_Puls();

	// RW = 0 [Write]
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_Pin_Reset);
	LCD_GPIO_INIT();
}

void LCD_Puls()
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN, GPIO_Pin_Set);
	delay_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN, GPIO_Pin_Reset);

}

void LCD_Clear()
{
	LCD_CMD(LCD_CLEAR);
}

void LCD_GoToXY(uint8_t line, uint8_t position)
{
	if(line == 1)
	{
		if(position >= 0 && position < 16)
			LCD_CMD(LCD_1st_Row + position);
	}
	else if(line == 2)
	{
		if(position >= 0 && position < 16)
			LCD_CMD(LCD_2nd_Row + position);
	}
	else
		LCD_CMD(LCD_1st_Row);
}

void LCD_GPIO_INIT()
{
	// RCC CLK Enable
	if(LCD_DATA_PORT == GPIOA || LCD_CTRL_PORT == GPIOA)
		RCC_GPIOA_CLK_EN();
	if(LCD_DATA_PORT == GPIOB || LCD_CTRL_PORT == GPIOB)
		RCC_GPIOB_CLK_EN();
	if(LCD_DATA_PORT == GPIOC || LCD_CTRL_PORT == GPIOC)
		RCC_GPIOC_CLK_EN();
	if(LCD_DATA_PORT == GPIOD || LCD_CTRL_PORT == GPIOD)
		RCC_GPIOD_CLK_EN();
	if(LCD_DATA_PORT == GPIOE || LCD_CTRL_PORT == GPIOE)
		RCC_GPIOE_CLK_EN();

	GPIO_PinConfig_t pinCfg;

	// Control Pins [RS, RW, EN] are output with speed 10M Hz
	pinCfg.GPIO_Mode = GPIO_Mode_Output_PullUp;
	pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;

	pinCfg.GPIO_PinNumber = LCD_RS;
	MCAL_GPIO_INIT(LCD_CTRL_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = LCD_RW;
	MCAL_GPIO_INIT(LCD_CTRL_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = LCD_EN;
	MCAL_GPIO_INIT(LCD_CTRL_PORT, &pinCfg);

	// Data Pins (0-->7) are output with speed 10M Hz
	pinCfg.GPIO_Mode = GPIO_Mode_Output_PullUp;
	pinCfg.GPIO_Output_Speed = GPIO_Speed_10MHz;

	pinCfg.GPIO_PinNumber = GPIO_Pin_0;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_1;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_2;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_3;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_4;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_5;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_6;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	pinCfg.GPIO_PinNumber = GPIO_Pin_7;
	MCAL_GPIO_INIT(LCD_DATA_PORT, &pinCfg);

	// Reset RW & RS & EN
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN, GPIO_Pin_Reset);
}
