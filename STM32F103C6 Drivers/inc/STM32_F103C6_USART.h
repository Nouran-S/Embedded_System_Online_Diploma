/*
 * STM32_F103C6_USART.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32_F103C6_USART_H_
#define INC_STM32_F103C6_USART_H_

// Includes:
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"
#include "STM32_F103C6_RCC.h"

// Configuration Structure:
typedef struct{
	uint8_t  USART_Mode;		// Tx/Rx Enable/Disable   (@ref: USART_Mode_define)
	uint32_t BaudRate;			// Set The BaudRate Value (@ref: USART_BaudRate_define)
	uint8_t  PayLoad_Length;	// No. of Data Bits (@ref: USART_PayLoad_Length_define)
	uint8_t  Parity;			// Parity Mode (@ref: USART_Parity_define)
	uint8_t  StopBits;			// Stop Bits (0.5, 1, 1.5, 2) (@ref: USART_StopBits_define)
	uint8_t  HW_FlowControl;	// HW Flow Control Enable/Diable (@ref: USART_HW_FlowControl_define)
	uint8_t  IRQEN;				// Enable/Disable IRQ Tx/Rx	(@ref: USART_IRQEN_define)
	void (*PTR_IRQ_CallBack)();	// IRQ Handler for any interrupt
}USART_Config_t;

// Macros Configuration References:
// ------------------------------------
// @ref: USART_Mode_define
#define USART_Mode_Rx		(uint32_t)(1<<2) 	// USART_CR1 Bit 2 RE: Receiver enable
#define USART_Mode_Tx		(uint32_t)(1<<3) 	// USART_CR1 Bit 3 TE: Transmitter enable
#define USART_Mode_Rx_Tx	(uint32_t)(1<<2 | 1<<3)

// @ref: USART_BaudRate_define
#define USART_BaudRate_2400			2400
#define USART_BaudRate_9600			9600
#define USART_BaudRate_19200		19200
#define USART_BaudRate_57600		57600
#define USART_BaudRate_115200		115200
#define USART_BaudRate_230400		230400
#define USART_BaudRate_460800		460800
#define USART_BaudRate_921600		921600
#define USART_BaudRate_2250000		2250000
#define USART_BaudRate_4500000		4500000

// @ref: USART_PayLoad_Length_define
#define USART_PayLoad_Length_8Bits		(uint32_t)(0)		// 1 Start bit, 8 Data bits, n Stop bit
#define USART_PayLoad_Length_9Bits		(uint32_t)(1<<12)	// 1 Start bit, 9 Data bits, n Stop bit

// @ref: USART_Parity_define
#define USART_Parity_Null		(uint32_t)(0)		     // Bit 10: PCE Parity control disabled
#define USART_Parity_Even		(uint32_t)(1<<10)	     // Bit 10: PCE Parity control enabled & Bit 9: PS = 0 Even parity
#define USART_Parity_Odd		(uint32_t)(1<<10 | 1<<9) // Bit 10: PCE Parity control enabled & Bit 9: PS = 1 Odd parity

// @ref: USART_StopBits_define
// Bits 13:12 STOP: STOP bits at USART_CR2 Reg.
#define USART_StopBits_0_5Bit	(uint32_t)(1<<12)
#define USART_StopBits_1Bit		(uint32_t)(0)
#define USART_StopBits_1_5Bits	(uint32_t)(3<<12)
#define USART_StopBits_2Bits	(uint32_t)(2<<12)

// @ref: USART_HW_FlowControl_define
#define USART_HW_FlowControl_Null		(uint32_t)(0)
#define USART_HW_FlowControl_RTC		(uint32_t)(1<<8)
#define USART_HW_FlowControl_CTC		(uint32_t)(1<<9)
#define USART_HW_FlowControl_RTC_CTC	(uint32_t)(1<<8 | 1<<9)

// @ref: USART_IRQEN_define
#define USART_IRQEN_Null					(uint32_t)(0)
#define USART_IRQEN_PE					(uint32_t)(1<<8)	// Parity error interrupt enable
#define USART_IRQEN_TXE					(uint32_t)(1<<7)	// Transmit data register empty interrupt enable
#define USART_IRQEN_TC					(uint32_t)(1<<6)	// Transmission complete interrupt enable
#define USART_IRQEN_RXNEIE				(uint32_t)(1<<5)	// Received data ready to be read & Overrun error detected interrupt enable

enum PollingMech{
	Disable,
	Enable,
};

// APIs:
void MCAL_USART_INIT(USART_Typedef* USARTx, USART_Config_t* USART_Cfg);
void MCAL_USART_Reset(USART_Typedef* USARTx);
void MCAL_USART_GPIO_SetPins(USART_Typedef* USARTx);
void MCAL_USART_SendData(USART_Typedef* USARTx, uint16_t* data, enum PollingMech PollingEN);
void MCAL_USART_ReceiveData(USART_Typedef* USARTx, uint16_t* data, enum PollingMech PollingEN);
void MCAL_USART_WaitTC(USART_Typedef* USARTx);

#endif /* INC_STM32_F103C6_USART_H_ */
