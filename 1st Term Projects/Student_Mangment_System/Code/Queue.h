/*
 * Queue.h
 *
 *  Created on: Sep 23, 2024
 *      Author: Nouarn S.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdint.h>

#define elementType struct SData
#define Queue_Max_Width 50
#define Courses_Max_Width 5

struct SData{
	int ID;
	char firstName[10];
	char lastName[10];
	float GPA;
	int courses[5];
	int nC;
};

typedef struct{
	unsigned int length; // total length(size) of the Queue
	unsigned int count;  // no of elements in the Queue
	elementType* base;   // 1st element in the Queue
	elementType* head;  // current element in the Queue
	elementType* tail;  // last element in the Queue
}Queue_t;

typedef enum{
	Queue_no_error,
	Queue_Full,
	Queue_Empty,
	Queue_Null,
}Queue_State_t;

// APIs:
Queue_State_t Queue_INIT(Queue_t* Queue, elementType* buffer, uint32_t length);
Queue_State_t Queue_Enqueue(Queue_t* Queue, elementType item);
Queue_State_t Queue_Dequeue(Queue_t* Queue, elementType* item);
Queue_State_t Queue_ISFull(Queue_t* Queue);
Queue_State_t Queue_ISEmpty(Queue_t* Queue);
void Queue_Print(Queue_t* Queue);
void Queue_Print_Item(elementType* item);
elementType Fill_Data();

Queue_State_t Queue_FindByID(Queue_t* Queue, int id);
Queue_State_t Queue_FindByName(Queue_t* Queue, char* name);
Queue_State_t Queue_FindByCourse(Queue_t* Queue, int courseID);
Queue_State_t Queue_DeleteByID(Queue_t* Queue, elementType *item, int courseID);
Queue_State_t Queue_UpdateByID(Queue_t* Queue, int id);

#endif /* QUEUE_H_ */
