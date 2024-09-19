/*
 * LIFO.h
 *
 *  Created on: Sep 15, 2024
 *      Author: DELL
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdio.h>
#include <stdint.h>

#define elementType uint8_t // Select the element type: uint_8
#define LIFO_width 5 		// Size of the Buffer

// FIFO Data Types:
typedef struct{
	unsigned int length;
	unsigned int count;
	elementType* base;
	elementType* head;
}LIOF_Buffer_t;

typedef enum{
	LIFO_no_error,
	LIFO_Full,
	LIFO_Empty,
	LIFO_Null,
}LIFO_Statue_t;

// APIs:
LIFO_Statue_t LIFO_INIT(LIOF_Buffer_t* lifo, elementType* buf, uint32_t length);
LIFO_Statue_t LIFO_Push(LIOF_Buffer_t* lifo, elementType item);
LIFO_Statue_t LIFO_Pop(LIOF_Buffer_t* lifo, elementType* item);
LIFO_Statue_t LIFO_ISFull(LIOF_Buffer_t* lifo);
LIFO_Statue_t LIFO_ISEmpty(LIOF_Buffer_t* lifo);
void LIFO_Print(LIOF_Buffer_t* lifo);


#endif /* LIFO_H_ */
