/*
 * STM32_F103C6_SPI.h
 *
 *  Created on: Dec 9, 2024
 *      Author: Nouran S.
 */

#ifndef INC_STM32_F103C6_SPI_H_
#define INC_STM32_F103C6_SPI_H_

// Includes:
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO.h"

typedef struct{
	uint16_t DeviceMode;	// Master/ Slave [@ref: SPI_DeviceMode_define]
	uint16_t FrameFormat;	// MSB/LSB first [@ref: SPI_FrameFormat_define]
	uint16_t DataSize;		// 8/16 bits [@ref: SPI_DataSize_define]
	uint16_t ClkPhase;		// [@ref: SPI_ClkPhase_define]
	uint16_t ClkPolarity;	// [@ref: SPI_ClkPolarity_define]
	uint16_t ClkFreq;		// Baud Rate [@ref: SPI_ClkFreq_define]
	uint16_t CommMode;		// bidirectional mode state [@ref: SPI_CommMode_define]
	uint16_t NSS;			// HW/SW [@ref: SPI_NSS_define]
	uint16_t IRQ_Enable;	// [@ref: SPI_IRQ_Enable_define]
	void (*P_IRQ_CallBack)(struct S_IRQ_Src src);
}SPI_Config_t;

struct S_IRQ_Src {
    uint8_t TXE : 1;
    uint8_t RXNE : 1;
    uint8_t ERRIE : 1;
    uint8_t Reversed : 5;
};

typedef enum{
	SPI_DeviceMode_Slave,
	SPI_DeviceMode_Master,
}SPI_DeviceMode_define;

typedef enum{
	SPI_FrameFormat_MSB,
	SPI_FrameFormat_LSB,
}SPI_FrameFormat_define;

typedef enum{
	SPI_DataSize_8Bit,
	SPI_DataSize_16Bit,
}SPI_DataSize_define;

typedef enum{
	SPI_ClkPhase_1stEdge,
	SPI_ClkPhase_2ndEdge,
}SPI_ClkPhase_define;

typedef enum{
	SPI_ClkPolarity_Low,
	SPI_ClkPolarity_High,
}SPI_ClkPolarity_define;

typedef enum{
	SPI_ClkFreq_2,
	SPI_ClkFreq_4,
	SPI_ClkFreq_8,
	SPI_ClkFreq_16,
	SPI_ClkFreq_32,
	SPI_ClkFreq_64,
	SPI_ClkFreq_128,
	SPI_ClkFreq_256,
}SPI_ClkFreq_define;

typedef enum{
	SPI_NSS_SW_Reset,		// Master or Slave
	SPI_NSS_SW_Set,			// Master or Slave
	SPI_NSS_HW_Input,		// Master
	SPI_NSS_HW_Output,		// Master
}SPI_NSS_define;

typedef enum{
	SPI_CommMode_2Lines,
	SPI_CommMode_2Lines_Rx,
	SPI_CommMode_1Lines_Rx,
	SPI_CommMode_1Lines_Tx,
}SPI_CommMode_define;

typedef enum{
	SPI_Polling_Disable,
	SPI_Polling_Enable
}SPI_Polling_define;

// @ref: SPI_IRQ_Enable_define
#define  SPI_IRQ_Enable_Null		(uint32_t)(0)
#define  SPI_IRQ_Enable_TXE			(uint32_t)(1<<7)
#define  SPI_IRQ_Enable_RXNE		(uint32_t)(1<<6)
#define  SPI_IRQ_Enable_ERR			(uint32_t)(1<<5)

// APIs Supported by "MCAL SPI DRIVER":
void MCAL_SPI_Init(SPI_Typedef* SPIx, SPI_Config_t* SpiCfg);
void MCAL_SPI_DeInit(SPI_Typedef* SPIx);
void MCAL_SPI_GPIO_Init(SPI_Typedef* SPIx);
void MCAL_SPI_Tx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling);
void MCAL_SPI_Rx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling);
void MCAL_SPI_Tx_Rx(SPI_Typedef* SPIx, uint16_t* data, SPI_Polling_define polling);

#endif /* INC_STM32_F103C6_SPI_H_ */
