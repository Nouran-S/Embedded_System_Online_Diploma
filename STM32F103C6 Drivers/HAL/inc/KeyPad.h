/*
 * KeyPad.h
 *
 *  Created on: Oct 18, 2024
 *      Author: Nouran S.
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

// Include
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

// KeyPad Port
#define KeyPad_PORT			GPIOB

// KeyPad Rows
#define KeyPad_Row_0		GPIO_Pin_0
#define KeyPad_Row_1		GPIO_Pin_1
#define KeyPad_Row_2		GPIO_Pin_3
#define KeyPad_Row_3		GPIO_Pin_4

// KeyPad Columns
#define KeyPad_Col_0		GPIO_Pin_5
#define KeyPad_Col_1		GPIO_Pin_6
#define KeyPad_Col_2		GPIO_Pin_7
#define KeyPad_Col_3		GPIO_Pin_8

// KeyPad APIs
void KeyPad_INIT();
void KeyPad_GetKey(uint8_t *key);

#endif /* KEYPAD_KEYPAD_H_ */
