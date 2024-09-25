/*
 * System.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Nouran S.
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "Queue.h"

typedef enum{
	System_no_error,
	System_error
}System_State_t;

System_State_t System_INIT(int length);
void System_Options();
void System_Call(int option);
void System_Update(elementType* selected);
void System_HandleFileData(char *buffer, elementType* data);
System_State_t System_IsIDUnique(Queue_t* Queue, int ID);
System_State_t System_IsCourseIDUnique(Queue_t* Queue, elementType* student);
#endif /* SYSTEM_H_ */
