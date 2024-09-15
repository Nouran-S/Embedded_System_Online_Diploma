/*
 *   main.c
 *
 *   Created on: Sep 13, 2024
 *  	Author: Nouran
 */
#include <stdio.h>
#include <stdlib.h>
#include "LIFO.h"
#include "FIFO.h"

int main()
{

	printf("\n************************* FIFO ********************************\n");
	FIOF_Buffer_t fifo;
	elementType buffer_fifo[FIFO_width];

	if(FIFO_INIT(&fifo, buffer_fifo, FIFO_width) == FIFO_no_error)
		printf("*** FIFO INIT DONE ***\n");

	// Enqueue:
	for (elementType i = 0; i < 7; i++)
		if(FIFO_Enqueue(&fifo, i) == FIFO_no_error)
			printf("*** FIFO ADD ITEM(%x) DONE ***\n", i);
		else
			printf("*** FIFO ADD ITEM(%x) Failed ***\n", i);
	FIFO_Print(&fifo);

	// Dequeue:
	elementType temp = 0;
	if(FIFO_Dequeue(&fifo, &temp) == FIFO_no_error)
		printf("*** FIFO Dequeue ITEM (%x) DONE ***\n", temp);
	if(FIFO_Dequeue(&fifo, &temp) == FIFO_no_error)
		printf("*** FIFO Dequeue ITEM (%x) DONE ***\n", temp);
	FIFO_Print(&fifo);

	// -----------------------------------------------------------------
	printf("\n************************* LIFO ********************************\n");
	LIOF_Buffer_t lifo;
	elementType buffer_lifo[LIFO_width];

	if(LIFO_INIT(&lifo, buffer_lifo, LIFO_width) == LIFO_no_error)
		printf("*** LIFO (STACK) INIT DONE ***\n");

	if(LIFO_ISEmpty(&lifo) == LIFO_Empty)
		printf("EMPTY\n");

	if(LIFO_ISFull(&lifo) == LIFO_Full)
		printf("FULL\n");

	// Push:
	for (elementType i = 0; i < 7; i++)
		if(LIFO_Push(&lifo, i) == LIFO_no_error)
			printf("*** LIFO ADD ITEM(%x) DONE ***\n", i);
		else
			printf("*** LIFO ADD ITEM(%x) Failed ***\n", i);
	LIFO_Print(&lifo);

	// Pop:
	elementType temp2;
	if(LIFO_Pop(&lifo, &temp2) == LIFO_no_error)
		printf("POP = %X\n", temp2);

	if(LIFO_Pop(&lifo, &temp2) == LIFO_no_error)
		printf("POP = %X\n", temp2);
	LIFO_Print(&lifo);

	return 0;
}
