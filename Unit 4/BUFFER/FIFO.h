/*
 * FIFO.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Nouran
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>

#define elementType uint8_t // Select the element type: uint_8
#define FIFO_width 5 		// Size of the Buffer

// FIFO Data Types:
typedef struct{
	unsigned int length;
	unsigned int count;
	elementType* base;
	elementType* head;
	elementType* tail;
}FIOF_Buffer_t;

typedef enum{
	FIFO_no_error,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null,
}FIFO_Statue_t;

// APIs:
FIFO_Statue_t FIFO_INIT(FIOF_Buffer_t* fifo, elementType* buf, uint32_t length);
FIFO_Statue_t FIFO_Enqueue(FIOF_Buffer_t* fifo, elementType item);
FIFO_Statue_t FIFO_Dequeue(FIOF_Buffer_t* fifo, elementType* item);
FIFO_Statue_t FIFO_ISFull(FIOF_Buffer_t* fifo);
FIFO_Statue_t FIFO_ISEmpty(FIOF_Buffer_t* fifo);
void FIFO_Print(FIOF_Buffer_t* fifo);

#endif /* FIFO_H_ */
