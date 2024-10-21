/*
 * LCD16_2.h
 *
 *  Created on: Oct 18, 2024
 *      Author: Nouran S.
 */

#ifndef LCD16_2_LCD16_2_H_
#define LCD16_2_LCD16_2_H_

// Include
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

// LCD Pins & Ports
#define LCD_DATA_PORT		GPIOA
#define LCD_CTRL_PORT		GPIOA
#define LCD_RS				GPIO_Pin_8
#define LCD_RW		    	GPIO_Pin_9
#define LCD_EN				GPIO_Pin_10

// LCD Commands
#define LCD_FUNCTION_8Bits_1Lines 		0x30
#define LCD_FUNCTION_8Bits_2Lines 		0x38
#define LCD_FUNCTION_4Bits_1Lines 		0x20
#define LCD_FUNCTION_4Bits_2Lines 		0x28
#define LCD_ENTRY_MODE					0x06
#define LCD_DISPLAY_OFF_CURSUR_OFF		0x08
#define LCD_DISPLAY_ON_CURSUR_ON   		0x0E
#define LCD_DISPLAY_ON_CURSUR_OFF 		0x0C
#define LCD_DISPLAY_ON_CURSUR_BLI   	0x0F
#define LCD_SHIFT_LEFT			    	0x18
#define LCD_SHIFT_RIGHT			    	0x1C
#define LCD_CURSUR_LEFT  				0x10
#define LCD_CURSUR_RIGHT				0x14
#define LCD_CLEAR						0x01
#define LCD_1st_Row						0x80
#define LCD_2nd_Row						0xC0

// LCD APIs
void LCD_INIT();
void LCD_CMD(uint8_t command);
void LCD_Char(uint8_t data);
void LCD_Str(uint8_t* str);
void LCD_IsBusy();
void LCD_Puls();
void LCD_Clear();
void LCD_GoToXY(uint8_t line, uint8_t position);

#endif /* LCD16_2_LCD16_2_H_ */
