/*
 * LIFO.c
 *
 *  Created on: Sep 15, 2024
 *      Author: DELL
 */
#include "LIFO.h"

LIFO_Statue_t LIFO_INIT(LIOF_Buffer_t* lifo, elementType* buf, uint32_t length)
{
	if(buf == NULL)
		return LIFO_no_error;

	lifo->base = buf;
	lifo->head = buf;
	lifo->length = length;
	lifo->count = 0;

	return LIFO_no_error;
}

LIFO_Statue_t LIFO_Push(LIOF_Buffer_t* lifo, elementType item)
{
	if(!lifo->base || !lifo->head)
		return LIFO_Null;

	if(LIFO_ISFull(lifo) == LIFO_Full)
		return LIFO_Full;

	*(lifo->head ) = item;
	lifo->head++;
	lifo->count++;

	return LIFO_no_error;
}

LIFO_Statue_t LIFO_Pop(LIOF_Buffer_t* lifo, elementType* item)
{
	if(!lifo->base || !lifo->head)
		return LIFO_Null;

	if(LIFO_ISEmpty(&lifo) == LIFO_Empty)
		return LIFO_Empty;

	lifo->head--;
	*item = *(lifo->head);
	lifo->count--;

	return LIFO_no_error;
}

LIFO_Statue_t LIFO_ISFull(LIOF_Buffer_t* lifo)
{
	if(!lifo->base || !lifo->head)
		return LIFO_Null;

	if(lifo->length <= lifo->count)
		return LIFO_Full;

	return LIFO_no_error;
}

LIFO_Statue_t LIFO_ISEmpty(LIOF_Buffer_t* lifo)
{
	if(!lifo->base || !lifo->head)
		return LIFO_Null;

	if(lifo->count == 0)
		return LIFO_Empty;

	return LIFO_no_error;
}

void LIFO_Print(LIOF_Buffer_t* lifo)
{
	elementType *temp = lifo->head;

	if(LIFO_ISEmpty(lifo) == LIFO_Empty)
		printf("LIFO Is Empty ** \n");

	else
	{
		printf("LIFO Items...  \n");
		for (elementType i = 0; i<lifo->count; i++)
		{
			temp--;
			printf("\t %X ", *temp);
		}
		printf("\n");
	}
}


