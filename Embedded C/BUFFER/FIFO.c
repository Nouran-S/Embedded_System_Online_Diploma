/*
 * FIFO.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Nouran
 */
#include "FIFO.h"

FIFO_Statue_t FIFO_INIT(FIOF_Buffer_t* fifo, elementType* buf, uint32_t length)
{
	if(buf == NULL)
		return FIFO_Null;

	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;

	return FIFO_no_error;
}

FIFO_Statue_t FIFO_Enqueue(FIOF_Buffer_t* fifo, elementType item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	if(FIFO_ISFull(fifo) == FIFO_Full)
		return FIFO_Full;

	*(fifo->head) = item;
	fifo->count++;

	if( fifo->head == (fifo->base + (fifo->length * sizeof(elementType))) )
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;
}

FIFO_Statue_t FIFO_Dequeue(FIOF_Buffer_t* fifo, elementType* item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	if(FIFO_ISEmpty(fifo) == FIFO_Empty)
		return FIFO_Empty;

	*item = *(fifo->tail);
	fifo->count--;

	if( fifo->tail == (fifo->base + (fifo->length * sizeof(elementType))) )
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_no_error;
}

FIFO_Statue_t FIFO_ISFull(FIOF_Buffer_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	if(fifo->length == fifo->count)
		return FIFO_Full;

	return FIFO_no_error;
}

FIFO_Statue_t FIFO_ISEmpty(FIOF_Buffer_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	if(fifo->count == 0)
		return FIFO_Empty;

	return FIFO_no_error;
}

void FIFO_Print(FIOF_Buffer_t* fifo)
{
	elementType *temp;

	if(FIFO_ISEmpty(fifo) == FIFO_Empty)
		printf("** FIFO Is Empty ** \n");

	else
	{
		temp = fifo->tail;
		printf("FIFO Elements .. \n");
		for(int i=0; i<fifo->count; i++)
		{
			printf("\t %X ", *temp);
			temp++;
		}
		printf("\n");
	}
}

