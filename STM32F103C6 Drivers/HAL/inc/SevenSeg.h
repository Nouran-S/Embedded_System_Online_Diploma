/*
 * SevenSeg.h
 *
 *  Created on: Oct 19, 2024
 *      Author: Nouran S.
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

// Include
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

// 7 Seg. PORT
#define SevenSeg_PORT 	GPIOB

// Seven Segment 1st Pin
#define SevenSeg_1stPin		9
#define SevenSeg_PinA		GPIO_Pin_9
#define SevenSeg_PinB		GPIO_Pin_10
#define SevenSeg_PinC		GPIO_Pin_11
#define SevenSeg_PinD		GPIO_Pin_12
#define SevenSeg_PinE		GPIO_Pin_13
#define SevenSeg_PinF		GPIO_Pin_14
#define SevenSeg_PinG		GPIO_Pin_15


// Hex Code For Numbers on the 7 Seg. Common Anode
#define Seg_CA_0		0x01
#define Seg_CA_1		0x79
#define Seg_CA_2		0x24
#define Seg_CA_3		0x30
#define Seg_CA_4		0x4C
#define Seg_CA_5		0x12
#define Seg_CA_6		0x02
#define Seg_CA_7		0x19
#define Seg_CA_8		0x00
#define Seg_CA_9		0x10

// Hex Code For Numbers on the 7 Seg. Common Cathode
#define Seg_CC_0		0x7F
#define Seg_CC_1		0x06
#define Seg_CC_2		0x5B
#define Seg_CC_3		0x4F
#define Seg_CC_4		0x66
#define Seg_CC_5		0x6D
#define Seg_CC_6		0x7D
#define Seg_CC_7		0x47
#define Seg_CC_8		0x3F
#define Seg_CC_9		0x6F

// Seven Segment APIs
void SevenSeg_INIT();
void SevenSeg_Write(uint8_t number);

#endif /* SEVENSEG_H_ */
