/*
 * DataBase.c
 *
 *  Created on: Sep 15, 2024
 *      Author: Nouran
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataBase.h"

struct SNode* pHead = NULL;
int LIST_Lenght = 0;

struct SStudentData Fill_Record()
{
	struct SStudentData temp;
	char buffer[10];

	printf("Enter Student ID: ");
	fflush(stdout);
	scanf("%d", &temp.ID);

	printf("Enter Student Name: ");
	fflush(stdout);
	getchar();
	fgets(temp.name, sizeof(temp.name), stdin);
	temp.name[strcspn(temp.name, "\n")] = '\0';

	printf("Enter Student Height: ");
	fflush(stdout);
	fgets(buffer, sizeof(buffer), stdin);
	temp.height = atof(buffer);

	return temp;
}

LIST_STATE_t LIST_ADD()
{
	struct SNode* pNew = (struct SNode*) malloc(sizeof(struct SNode));

	if (!pNew)
		return LIST_Null;

	pNew->Data = (struct SStudentData*) malloc(sizeof(struct SStudentData));

	if (!pNew->Data)
	{
		free(pNew);
		return LIST_Null;
	}

	if (LIST_IsEmpty() == LIST_Empty)
		pHead = pNew;

	else
	{
		struct SNode* pLast = pHead;
		while (pLast->pNext)
			pLast = pLast->pNext;
		pLast->pNext = pNew;
	}

	struct SStudentData data = Fill_Record();
	pNew->Data->ID = data.ID;
	strcpy(pNew->Data->name, data.name);
	pNew->Data->height = data.height;
	pNew->pNext = NULL;
	LIST_Lenght++;

	return LIST_no_error;
}

LIST_STATE_t LIST_Delete()
{
	if (LIST_IsEmpty() == LIST_Empty)
	{
		printf("** List Is Empty **\n");
		return LIST_Empty;
	}

	int id;
	printf("Enter the student ID: ");
	fflush(stdout);
	scanf("%d", &id);

	struct SNode* pLast = pHead;
	struct SNode* pPrev = NULL;

	while(pLast)
	{
		if(pLast->Data->ID == id)
		{
			if(pPrev)
				pPrev->pNext = pLast->pNext;

			else
				pHead = pLast->pNext;

			free(pLast);
			return LIST_no_error;
		}

		pPrev = pLast;
		pLast = pLast->pNext;
		LIST_Lenght--;
	}

	printf("** Can't find a student with id = %d **\n", id);
	return LIST_no_error;
}

LIST_STATE_t LIST_DeleteAll()
{
	if (LIST_IsEmpty() == LIST_Empty)
	{
		printf("** List Is Empty **\n");
		return LIST_Empty;
	}

	struct SNode* pLast = pHead;
	struct SNode* pPrev = NULL;

	while(pLast)
	{
		pPrev = pLast;
		pLast = pLast->pNext;
		free(pPrev);
	}


	pHead = NULL;
	LIST_Lenght = 0;
	return LIST_no_error;
}

LIST_STATE_t LIST_IsEmpty()
{
	if(pHead == NULL)
		return LIST_Empty;
	return LIST_no_error;
}

LIST_STATE_t LIST_Find(struct SStudentData* temp, LIST_Find_Pos_t pos)
{
	struct SNode* pSelected = pHead;
	int index, count = 0;

	printf("Find Student .. index: ");
	fflush(stdout);
	scanf("%d", &index);

	if(pos == LIST_Find_Last)
		index = LIST_Lenght - index - 1;

	while(pSelected)
	{
		if(count == index)
		{
			temp->ID = pSelected->Data->ID;
			strcpy(temp->name, pSelected->Data->name);
			temp->height = pSelected->Data->height;
			return LIST_Found;
		}

		pSelected = pSelected->pNext;
		count++;
	}

	return LIST_Not_Found;
}


int LIST_GetLength()
{
	int len = 0;
	struct SNode* pSelected = pHead;
	while(pSelected)
	{
		len++;
		pSelected = pSelected->pNext;
	}
	return len;
}

void LIST_Print()
{
	printf("********************************************");
	if(LIST_IsEmpty() == LIST_Empty)
		printf("\n** LIST Is Empty ** \n");

	struct SNode* pLast = pHead;
	int count = 0;

	while(pLast)
	{
		count++;
		printf("\nStudent No.%d ..\n", count);
		printf("\tStudent ID: %d\n", pLast->Data->ID);
		printf("\tStudent Name: %s\n", pLast->Data->name);
		printf("\tStudent Height: %0.3f\n", pLast->Data->height);
		pLast = pLast->pNext;
	}

	printf("********************************************\n");
}



