/*
 * DataBase.h
 *
 *  Created on: Sep 15, 2024
 *      Author: Nouran
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string.h>

struct SStudentData{
	char name[30];
	int ID;
	float height;
};

struct SNode{
	struct SStudentData* Data;
	struct SNode* pNext;
};

typedef enum{
	LIST_no_error,
	LIST_Empty,
	LIST_Null,
}LIST_STATE_t;

typedef enum{
	LIST_Not_Found,
	LIST_Found,
}LIST_Find_t;

typedef enum{
	LIST_Find_First,
	LIST_Find_Last,
}LIST_Find_Pos_t;

struct SStudentData Fill_Record();
LIST_STATE_t LIST_ADD();
LIST_STATE_t LIST_Delete();
LIST_STATE_t LIST_DeleteAll();
LIST_STATE_t LIST_IsEmpty();
LIST_STATE_t LIST_Find(struct SStudentData* temp, LIST_Find_Pos_t pos);
int LIST_GetLength();
void LIST_Print();

#endif /* DATABASE_H_ */
