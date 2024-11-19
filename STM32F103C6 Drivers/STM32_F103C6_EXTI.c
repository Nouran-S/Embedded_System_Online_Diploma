/*
 * STM32_F103C6_EXTI.c
 *
 *  Created on: Oct 19, 2024
 *      Author: Nouran S.
 */

// Includes:
#include "STM32_F103C6_EXTI.h"

// Generic Macros:
#define AFIO_EXTI_GPIO_Mapping(x)	(	(x == GPIOA)? 0: \
		(x == GPIOB)? 1: \
				(x == GPIOC)? 2: \
						(x == GPIOD)? 3: \
								(x == GPIOE)? 4: \
										(x == GPIOF)? 5: \
												(x == GPIOG)? 5:0 \
)

// Generic Pointers:
void (*g_IRQ_Callback[15])() = {NULL};  // array of pointer to [15] functions take void and return void

/**================================================================
 * @Fn			- MCAL_EXTI_DeInit
 * @brief 		- Reset the EXTI
 * @retval 		- None
 * Note			- None
 */
void MCAL_EXTI_DeInit()
{
	// Reset Values
	EXTI->IMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR    = 0xFFFFFFFF;

	// Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXT0_Disable();
	NVIC_IRQ7_EXT1_Disable();
	NVIC_IRQ8_EXT2_Disable();
	NVIC_IRQ9_EXT3_Disable();
	NVIC_IRQ10_EXT4_Disable();
	NVIC_IRQ23_EXT5_9_Disable();
	NVIC_IRQ40_EXT10_16_Disable();

}

/**================================================================
 * @Fn			- MCAL_EXTI_INIT
 * @brief 		- Initialize the EXTI GPIO Pin
 * @param [in] 	- EXTI_PinCfg: the configuration of the EXTI [EXTI Pin, Trigger, IRQ Enable, Callback Function]
 * @retval 		- None
 * Note			- Enable Rcc & AFIO
 */
void MCAL_EXTI_INIT(EXTI_PinConfig_t* PinCfg)
{
	Update_EXTI(PinCfg);

}

/**================================================================
 * @Fn			- MCAL_EXTI_Update
 * @brief 		- Update the EXTI GPIO Pin
 * @param [in] 	- EXTI_PinCfg: the configuration of the EXTI [EXTI Pin, Trigger, IRQ Enable, Callback Function]
 * @retval 		- None
 * Note			- None
 */
void MCAL_EXTI_Update(EXTI_PinConfig_t* PinCfg)
{
	Update_EXTI(PinCfg);
}

// Generic Functions:
void Update_EXTI(EXTI_PinConfig_t* PinCfg)
{
	// 1- RCC CLK Enable
	if(PinCfg->EXTI_Pin.GPIO_Port == GPIOA)
		RCC_GPIOA_CLK_EN();
	if(PinCfg->EXTI_Pin.GPIO_Port == GPIOB)
		RCC_GPIOB_CLK_EN();
	if(PinCfg->EXTI_Pin.GPIO_Port == GPIOC)
		RCC_GPIOC_CLK_EN();
	if(PinCfg->EXTI_Pin.GPIO_Port == GPIOD)
		RCC_GPIOD_CLK_EN();
	if(PinCfg->EXTI_Pin.GPIO_Port == GPIOE)
		RCC_GPIOE_CLK_EN();

	// 2- Initialize the pin t be AT Input [Floating input]
	GPIO_PinConfig_t gpio_pinCfg;
	gpio_pinCfg.GPIO_Mode = GPIO_Mode_Input_Floating;
	gpio_pinCfg.GPIO_PinNumber = PinCfg->EXTI_Pin.GPIO_Pin;
	MCAL_GPIO_INIT(PinCfg->EXTI_Pin.GPIO_Port, &gpio_pinCfg);

	// 3- Update AFIO to rout between EXTI line with PORT[A, B, C, D]
	uint8_t AFIO_EXTICR_idx =  PinCfg->EXTI_Pin.EXTI_Line / 4;
	uint8_t AFIO_EXTICR_pos = (PinCfg->EXTI_Pin.EXTI_Line % 4) * 4;
	//	uint8_t AFIO_EXTICR_pos = AFIO_EXTICR_idx * 4;

	// Clear 4bits
	AFIO->EXTICR[AFIO_EXTICR_idx] &= ~(0xF << AFIO_EXTICR_pos);
	AFIO->EXTICR[AFIO_EXTICR_idx] |= ((AFIO_EXTI_GPIO_Mapping(PinCfg->EXTI_Pin.GPIO_Port)) &0xF) << AFIO_EXTICR_pos;

	// 4- Update Rising Failing Edge
	EXTI->FTSR &= ~(1<< PinCfg->EXTI_Pin.EXTI_Line);
	EXTI->RTSR &= ~(1<< PinCfg->EXTI_Pin.EXTI_Line);

	if(PinCfg->Trigger_Case == EXTI_Trigger_Falling)
		EXTI->FTSR |= (1<< PinCfg->EXTI_Pin.EXTI_Line);
	else if(PinCfg->Trigger_Case == EXTI_Trigger_Rising)
		EXTI->RTSR |= (1<< PinCfg->EXTI_Pin.EXTI_Line);
	else // EXTI_Trigger_FallingRising
	{
		EXTI->FTSR |= (1<< PinCfg->EXTI_Pin.EXTI_Line);
		EXTI->RTSR |= (1<< PinCfg->EXTI_Pin.EXTI_Line);
	}

	// 5- Update Callback function
	g_IRQ_Callback[PinCfg->EXTI_Pin.EXTI_Line] = PinCfg->IRQ_CallBack_ptr;

	// 6- Enable/Disable IRQ & NVIC
	if(PinCfg->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |=  (1<<PinCfg->EXTI_Pin.EXTI_Line);
		NVIC_Enable(PinCfg->EXTI_Pin.EXTI_Line);
	}
	else
	{
		EXTI->IMR &= ~(1<<PinCfg->EXTI_Pin.EXTI_Line);
		NVIC_Disable(PinCfg->EXTI_Pin.EXTI_Line);
	}
}

void NVIC_Enable(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0:
		NVIC_IRQ6_EXT0_Enable();
		break;
	case 1:
		NVIC_IRQ7_EXT1_Enable();
		break;
	case 2:
		NVIC_IRQ8_EXT2_Enable();
		break;
	case 3:
		NVIC_IRQ9_EXT3_Enable();
		break;
	case 4:
		NVIC_IRQ10_EXT4_Enable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXT5_9_Enable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXT10_15_Enable();
		break;
	}
}

void NVIC_Disable(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0:
		NVIC_IRQ6_EXT0_Disable();
		break;
	case 1:
		NVIC_IRQ7_EXT1_Disable();
		break;
	case 2:
		NVIC_IRQ8_EXT2_Disable();
		break;
	case 3:
		NVIC_IRQ9_EXT3_Disable();
		break;
	case 4:
		NVIC_IRQ10_EXT4_Disable();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXT5_9_Disable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXT10_15_Disable();
		break;
	}
}

// ISR Functions:
void EXTI0_IRQHandler()
{
	// Clear Pending register (EXTI_PR) by writing a ‘1’ into the bit
	EXTI->PR |= (1<<EXTI0);

	// Call IRQ
	if(g_IRQ_Callback[EXTI0] != NULL)
		g_IRQ_Callback[EXTI0]();
}
void EXTI1_IRQHandler()
{
	// Clear Pending register (EXTI_PR) by writing a ΓÇÿ1ΓÇÖ into the bit
	EXTI->PR |= (1<<EXTI1);

	// Call IRQ
	if(g_IRQ_Callback[EXTI1] != NULL)
		g_IRQ_Callback[EXTI1]();
}
void EXTI2_IRQHandler()
{
	// Clear Pending register (EXTI_PR) by writing a ΓÇÿ1ΓÇÖ into the bit
	EXTI->PR |= (1<<EXTI2);

	// Call IRQ
	if(g_IRQ_Callback[EXTI2] != NULL)
		g_IRQ_Callback[EXTI2]();
}
void EXTI3_IRQHandler()
{
	// Clear Pending register (EXTI_PR) by writing a ΓÇÿ1ΓÇÖ into the bit
	EXTI->PR |= (1<<EXTI3);

	// Call IRQ
	if(g_IRQ_Callback[EXTI3] != NULL)
		g_IRQ_Callback[EXTI3]();
}
void EXTI4_IRQHandler()
{
	// Clear Pending register (EXTI_PR) by writing a ΓÇÿ1ΓÇÖ into the bit
	EXTI->PR |= (1<<EXTI4);

	// Call IRQ
	if(g_IRQ_Callback[EXTI4] != NULL)
		g_IRQ_Callback[EXTI4]();
}

void EXTI9_5_IRQHandler()
{
	if(EXTI->PR & (1<<EXTI5))	{EXTI->PR |= (1<<EXTI5);	g_IRQ_Callback[EXTI5]();}
	if(EXTI->PR & (1<<EXTI6))	{EXTI->PR |= (1<<EXTI6);	g_IRQ_Callback[EXTI6]();}
	if(EXTI->PR & (1<<EXTI7))	{EXTI->PR |= (1<<EXTI7);	g_IRQ_Callback[EXTI7]();}
	if(EXTI->PR & (1<<EXTI8))	{EXTI->PR |= (1<<EXTI8);	g_IRQ_Callback[EXTI8]();}
	if(EXTI->PR & (1<<EXTI9))	{EXTI->PR |= (1<<EXTI9);	g_IRQ_Callback[EXTI9]();}
}

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & (1<<EXTI10))	{EXTI->PR |= (1<<EXTI10);	g_IRQ_Callback[EXTI10]();}
	if(EXTI->PR & (1<<EXTI11))	{EXTI->PR |= (1<<EXTI11);	g_IRQ_Callback[EXTI11]();}
	if(EXTI->PR & (1<<EXTI12))	{EXTI->PR |= (1<<EXTI12);	g_IRQ_Callback[EXTI12]();}
	if(EXTI->PR & (1<<EXTI13))	{EXTI->PR |= (1<<EXTI13);	g_IRQ_Callback[EXTI13]();}
	if(EXTI->PR & (1<<EXTI14))	{EXTI->PR |= (1<<EXTI14);	g_IRQ_Callback[EXTI14]();}
	if(EXTI->PR & (1<<EXTI15))	{EXTI->PR |= (1<<EXTI15);	g_IRQ_Callback[EXTI15]();}
}


