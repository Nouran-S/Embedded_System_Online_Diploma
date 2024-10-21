/*
 * STM32_F103C6_GPIO.c
 *
 *  Created on: Oct 17, 2024
 *      Author: Nouran S.
 */

#include "STM32_F103C6_GPIO.h"
#include "stm32f103x6.h"

void Get_CRLH_Position(uint16_t pinNumber, uint8_t * pos)
{
	*(pos) = 0;
	switch (pinNumber)
	{
	case GPIO_Pin_0:
		*(pos) = 0;
		break;
	case GPIO_Pin_1:
		*(pos) = 4;
		break;
	case GPIO_Pin_2:
		*(pos) = 8;
		break;
	case GPIO_Pin_3:
		*(pos) = 12;
		break;
	case GPIO_Pin_4:
		*(pos) = 16;
		break;
	case GPIO_Pin_5:
		*(pos) = 20;
		break;
	case GPIO_Pin_6:
		*(pos) = 24;
		break;
	case GPIO_Pin_7:
		*(pos) = 28;
		break;
	case GPIO_Pin_8:
		*(pos) = 0;
		break;
	case GPIO_Pin_9:
		*(pos) = 4;
		break;
	case GPIO_Pin_10:
		*(pos) = 8;
		break;
	case GPIO_Pin_11:
		*(pos) = 12;
		break;
	case GPIO_Pin_12:
		*(pos) = 16;
		break;
	case GPIO_Pin_13:
		*(pos) = 20;
		break;
	case GPIO_Pin_14:
		*(pos) = 24;
		break;
	case GPIO_Pin_15:
		*(pos) = 28;
		break;
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_INIT
 * @brief 		- Initialize GPIOx PINy Peripheral according to the specified parameters
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in]	- PinConfig: the configuration information for the specified GPIO Pin
 * @retval 		- None
 * Note			- STM32F103C6 MCU has GPIO(A..E) but LQFB48 Package has only GPIO (A, B) and Part of GPIO(C, D)
 */
void MCAL_GPIO_INIT(GPIOx_Typedef* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	volatile uint32_t *configReg = NULL;
	uint8_t pin_config = 0;
	uint8_t pos;

	// Port configuration register low  (GPIOx_CRL) (0-->7)
	// Port configuration register High (GPIOx_CRL) (8-->15)
	configReg = (PinConfig->GPIO_PinNumber >= GPIO_Pin_8)? &GPIOx->CRH: &GPIOx->CRL;

	// Clear MODE, CNF
	Get_CRLH_Position(PinConfig->GPIO_PinNumber, &pos);
	(*configReg) &= ~(0xF << pos);

	// If the pin is output
	if(PinConfig->GPIO_Mode == GPIO_Mode_Output_ALT_PullDown || PinConfig->GPIO_Mode == GPIO_Mode_Output_ALT_PullUp ||
			PinConfig->GPIO_Mode == GPIO_Mode_Output_PullDown || PinConfig->GPIO_Mode == GPIO_Mode_Output_PullUp)
		pin_config = ((((PinConfig->GPIO_Mode - 4) << 2 ) | (PinConfig->GPIO_Output_Speed)) & 0x0f);

	// If the pin is input
	else // MODE = 00
	{
		if(PinConfig->GPIO_Mode == GPIO_Mode_Input_Floating || GPIO_Mode_Analog)
			pin_config = (((PinConfig->GPIO_Mode << 2 ) | (0x00)) & 0x0f);
		else if(PinConfig->GPIO_Mode == GPIO_Mode_Input_ALT) // == Input Floating
			pin_config = (((GPIO_Mode_Input_Floating << 2 ) | (0x00)) & 0x0f);
		else // == Input Pull Up or Pull Down
		{
			pin_config = (((GPIO_Mode_Input_PullUp << 2 ) | (0x00)) & 0x0f);
			if (PinConfig->GPIO_Mode == GPIO_Mode_Input_PullUp)
				// Table.20 [ODR = 1]
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			else
				GPIOx->ODR &= ~PinConfig->GPIO_PinNumber;
		}
	}

	(*configReg) |= (pin_config << pos);
}

/**================================================================
 * @Fn			- MCAL_GPIO_DeINIT
 * @brief 		- Reset all the GPIO Registers
 * @param [in] 	- GPIOx: [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @retval 		- None
 * Note			- None
 */
void MCAL_GPIO_DeINIT(GPIOx_Typedef* GPIOx)
{
	// Using The Reset Value:
	//	GPIOx->CRL  = 0x44444444;
	//	GPIOx->CRH  = 0x44444444;
	// GPIOx->IDR  = Read Only;
	//	GPIOx->ODR  = 0x00000000;
	//	GPIOx->BSRR = 0x00000000;
	//	GPIOx->BRR  = 0x00000000;
	//	GPIOx->LCKR = 0x00000000;

	// Using RCC:
	if (GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=  (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (GPIOx ==  GPIOB)
	{
		RCC->APB2RSTR |=  (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=  (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx ==  GPIOD)
	{
		RCC->APB2RSTR |=  (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx ==  GPIOE)
	{
		RCC->APB2RSTR |=  (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read Specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in] 	- PinNumber: Set the pin Number according to @ref GPIO_Pin_define
 * @param [out] 	- value    : The reading value of the pin 2 values on according to @ref GPIO_Pin_State
 * @retval 		- None
 * Note			- None
 */
uint8_t MCAL_GPIO_ReadPin(GPIOx_Typedef* GPIOx, uint16_t PinNumber)
{
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_Pin_Reset)
		return GPIO_Pin_Set;
	else
		return GPIO_Pin_Reset;
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read Specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [out] 	- value    : The reading value of the PORTx [where x can be(A..E) depend on the device used]
 * @retval 		- None
 * Note			- None
 */
uint16_t MCAL_GPIO_ReadPort(GPIOx_Typedef* GPIOx)
{
	return (uint16_t) GPIOx->IDR;
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write value on a specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in] 	- PinNumber: Set the pin Number according to @ref GPIO_Pin_define
 * @param [in] 	- value    : The value of the pin (2 values on according to @ref GPIO_Pin_State)
 * @retval 		- None
 * Note			- None
 */
void MCAL_GPIO_WritePin(GPIOx_Typedef* GPIOx, uint16_t PinNumber, uint8_t value)
{
	if(value != (uint8_t)GPIO_Pin_Reset)
		GPIOx->BSRR = (uint32_t)PinNumber; // OR: GPIOx->ODR |= PinNumber;

	else
		GPIOx->BRR = (uint32_t)PinNumber; // OR: GPIOx->ODR &= ~PinNumber;
}


/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Read Specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in] 	- value    : The value of the PORTx [where x can be(A..E) depend on the device used]
 * @retval 		- None
 * Note			- None
 */
void MCAL_GPIO_WritePort(GPIOx_Typedef* GPIOx, uint16_t value)
{
	GPIOx->ODR = (uint32_t) value;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle Specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in] 	- PinNumber: Set the pin Number according to @ref GPIO_Pin_define
 * @retval 		- None
 * Note			- None
 */
void MCAL_GPIO_TogglePin(GPIOx_Typedef* GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}

/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- Lock Specific Pin
 * @param [in] 	- GPIOx    : [where x can be(A..E) depend on the device used] to select the GPIO Peripheral
 * @param [in] 	- PinNumber: Set the pin Number according to @ref GPIO_Pin_define
 * @param [out] 	- state: ok if the pin is locked, Error if the pin isn't locked @ref GPIO_Return_Lock
 * @retval 		- None
 * Note			- None
 */
void MCAL_GPIO_LockPin(GPIOx_Typedef* GPIOx, uint16_t PinNumber, uint8_t *state)
{
	volatile uint32_t temp = (1<<16); // Set LCKK
	temp |= PinNumber; 				  // Set LCKy

	// LOCK key writing sequence:
	// Write 1
	GPIOx->LCKR = temp;
	// Write 0
	GPIOx->LCKR = PinNumber;
	// Write 1
	GPIOx->LCKR = temp;
	// Read 0
	temp = GPIOx->LCKR;
	// Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)((GPIOx->LCKR) && (1<<16) == 0))
		*state = GPIO_Return_Lock_Enable;
	else
		*state = GPIO_Return_Lock_Disable;
}

void delay_ms(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}


