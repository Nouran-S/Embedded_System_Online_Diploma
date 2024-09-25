/*
 * Queue.c
 *
 *  Created on: Sep 23, 2024
 *      Author: Nouarn S.
 */
#include <stdio.h>
#include <string.h>
#include "Queue.h"

Queue_State_t Queue_INIT(Queue_t* Queue, elementType* buffer, uint32_t length)
{
	if(buffer == NULL)
		return Queue_Null;

	Queue->head = buffer;
	Queue->tail = buffer;
	Queue->base = buffer;
	Queue->count = 0;
	Queue->length = length;
	return Queue_no_error;
}

Queue_State_t Queue_Enqueue(Queue_t* Queue, elementType item)
{
	if(!Queue->head || !Queue->tail || !Queue->base)
		return Queue_Null;

	if(Queue_ISFull(Queue) == Queue_Full)
		return Queue_Full;

	*(Queue->head) = item;
	Queue->count++;

	if( Queue->head == (Queue->base + (Queue->length * sizeof(elementType))) )
		Queue->head = Queue->base;
	else
		Queue->head++;


	return Queue_no_error;
}

Queue_State_t Queue_Dequeue(Queue_t* Queue, elementType* item)
{
	if(!Queue->head || !Queue->tail || !Queue->base)
		return Queue_Null;

	if(Queue_ISEmpty(Queue) == Queue_Empty)
		return Queue_Empty;

	*item = *(Queue->tail);
	Queue->count--;

	if( Queue->tail == (Queue->base + (Queue->length * sizeof(elementType))) )
		Queue->tail = Queue->base;
	else
		Queue->tail++;


	return Queue_no_error;
}

Queue_State_t Queue_ISFull(Queue_t* Queue)
{
	if(!Queue->head || !Queue->tail || !Queue->base)
		return Queue_Null;

	if(Queue->length == Queue->count)
		return Queue_Full;

	return Queue_no_error;
}

Queue_State_t Queue_ISEmpty(Queue_t* Queue)
{
	if(!Queue->head || !Queue->tail || !Queue->base)
		return Queue_Null;

	if(Queue->count == 0)
		return Queue_Empty;

	return Queue_no_error;
}

void Queue_Print(Queue_t* Queue)
{
	if(!Queue->head || !Queue->tail || !Queue->base)
		printf("\t\t** Queue is NULL .. **\n");

	else if(Queue_ISEmpty(Queue) == Queue_Empty)
		printf("\t\t** Queue is Empty .. **\n");

	else
	{
		elementType* current = Queue->tail;
		for(int i=0; i<Queue->count; i++)
		{
			printf("\tID: %d \n", current->ID);
			printf("\tFirst Name: %s \n", current->firstName);
			printf("\tLast Name: %s \n", current->lastName);
			printf("\tGPA: %0.2f \n", current->GPA);
			printf("\tCourses: ");
			for(int j=0; j<current->nC; j++)
				printf("%d \t", current->courses[j]);
			printf("\n\t********************************\n");
			current++;
		}
	}
}

void Queue_Print_Item(elementType* item)
{
	if(!item)
		printf("\t** Item is NULL .. **\n");
	else
	{
		printf("\t\tID: %d \n", item->ID);
		printf("\t\tFirst Name: %s \n", item->firstName);
		printf("\t\tLast Name: %s \n", item->lastName);
		printf("\t\tGPA: %0.2f \n", item->GPA);
		printf("\t\tCourses: ");
		for(int j=0; j<item->nC; j++)
			printf("%d \t", item->courses[j]);
		printf("\n\t********************************\n");
	}
}

elementType Fill_Data()
{
	elementType temp;
	char dataInput[20];

	printf("\tID: ");
	fflush(stdout);
	fflush(stdin);
	gets(dataInput);
	temp.ID = atoi(dataInput);

	printf("\tFirst Name: ");
	fflush(stdout);
	gets(dataInput);
	strcpy(temp.firstName, dataInput);

	printf("\tLast Name: ");
	fflush(stdout);
	gets(dataInput);
	strcpy(temp.lastName, dataInput);

	printf("\tGPA: ");
	fflush(stdout);
	scanf("%f", &temp.GPA);

	printf("\tNo. of Courses: ");
	fflush(stdout);
	scanf("%d", &temp.nC);

	for(int j=0; j<5; j++)
		temp.courses[j] = -1;


	for(int j=0; j<temp.nC; j++)
	{
		printf("\t\tCourses No.%d: ", j+1);
		fflush(stdout);
		scanf("%d", &temp.courses[j]);
	}
	printf("\n****************************************************************\n");

	return temp;
}

// **********************************************************************************
Queue_State_t Queue_FindByID(Queue_t* Queue, int id)
{
	elementType* current = Queue->tail;

	if(!Queue->head || !Queue->tail || !Queue->base)
	{
		printf("\t\t** Queue is NULL .. **\n");
		return Queue_Null;
	}

	else if(Queue_ISEmpty(Queue) == Queue_Empty)
	{
		printf("\t\t** Queue is Empty .. **\n");
		return Queue_Empty;
	}

	int found  = 0;
	for(int j=0; j<Queue->count; j++)
	{
		if(current->ID == id)
		{
			printf("\t*********** Found A Student Has The Same ID ***********\n");
			Queue_Print_Item(current);
			return Queue_no_error;
		}

		current++;
	}

	printf("\t** This ID can not be found *** \n");
	return Queue_Null;
}

Queue_State_t Queue_FindByName(Queue_t* Queue, char* name)
{
	elementType* current = Queue->tail;

	if(!Queue->head || !Queue->tail || !Queue->base)
	{
		printf("\t\t** Queue is NULL .. **\n");
		return Queue_Null;
	}

	if(Queue_ISEmpty(Queue) == Queue_Empty)
	{
		printf("\t\t** Queue is Empty .. **\n");
		return Queue_Empty;
	}

	int found  = 0;
	for(int j=0; j<Queue->count; j++)
	{
		if(strcmp(current->firstName, name) == 0 || strcmp(current->lastName, name) == 0)
		{
			printf("\t*********** Found A Student Has The Same Name ***********\n");
			Queue_Print_Item(current);
			found = 1;
		}

		current++;
	}

	if(found != 0)
		return Queue_no_error;

	printf("\t** This Name can not be found *** \n");
	return Queue_Null;
}

Queue_State_t Queue_FindByCourse(Queue_t* Queue, int courseID)
{
	elementType* current = Queue->tail;

	if(!Queue->head || !Queue->tail || !Queue->base)
	{
		printf("\t\t** Queue is NULL .. **\n");
		return Queue_Null;
	}

	if(Queue_ISEmpty(Queue) == Queue_Empty)
	{
		printf("\t\t** Queue is Empty .. **\n");
		return Queue_Empty;
	}

	int found  = 0;
	for(int j=0; j<Queue->count; j++)
	{
		for(int i=0; i<current->nC; i++)
			if(current->courses[i] == courseID)
			{
				printf("\t*********** Found A Student Enrolls In The Same Course ID ***********\n");
				Queue_Print_Item(current);
				found = 1;
			}

		current++;
	}

	if(found != 0)
		return Queue_no_error;

	printf("\t** This Course can not be found *** \n");
	return Queue_Null;
}

Queue_State_t Queue_DeleteByID(Queue_t* Queue, elementType *item, int courseID)
{
	return Queue_no_error;
}

Queue_State_t Queue_UpdateByID(Queue_t* Queue, int id)
{
	elementType* current = Queue->tail;

	if(Queue_FindByID(Queue, id) == Queue_no_error)
	{
		while(current)
		{
			if(current->ID == id)
				break;
			current++;
		}

		System_Update(current);
		printf("*** Updated Data *** \n");
		Queue_Print_Item(current);
	}
	return Queue_no_error;
}


