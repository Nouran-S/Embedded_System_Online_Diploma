/*
 * System.c
 *
 *  Created on: Sep 24, 2024
 *      Author: Nouran S.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "System.h"
#include "Queue.h"

elementType myBuffer[50];
Queue_t myQueue;

System_State_t System_INIT(int length)
{

	if(length > Queue_Max_Width)
	{
		printf("*** Can't create a 'Queue' with length max then '%d' ***\n", Queue_Max_Width);
		return System_error;
	}

	myQueue.head = myBuffer;
	myQueue.base = myBuffer;
	myQueue.tail = myBuffer;
	myQueue.count = 0;
	myQueue.length = length;

	return System_no_error;
}

void System_Options()
{
	int option = 2;

	printf("****************************************************************\n");
	printf(" 0: Exit \n");
	printf(" 1: Add From File \n");
	printf(" 2: Add Manually \n");
	printf(" 3: Find By ID \n");
	printf(" 4: Find By Name \n");
	printf(" 5: Find By Course ID \n");
	printf(" 6: Number Of Students \n");
	printf(" 7: Delete 1st Student \n");
	printf(" 8: Delete All \n");
	printf(" 9: Update Student Data \n");
	printf("10: Display Student Data \n");
	printf("Option: ");
	fflush(stdout);
	scanf("%d", &option);

	if(option < 0 ||  option > 11)
	{
		printf("***  Wrong Choice .. ***\n");
		printf("*****************************\n");
		System_Options(option);
	}

	printf("****************************************************************\n");
	System_Call(option);
}

void System_Call(int option)
{
	int intInput;
	char strInput[30];
	char buffer[100];
	elementType temp_item;

	switch (option)
	{
	case 0:
		printf("*************************** Adios .. ***************************\n");
		exit(1);
		break;
	case 1:
		printf("\t\t*** Add From File (only one student at a time) .. *** \n");
		printf("\tInput Format:ID,FirstName,LastName,GPA,course_1,course_2,course_3,course_4,course_5\n");
		printf("\tNote: courseID = 0 (null)\n\n");
		printf("\tFile Name: ");
		fflush(stdout);
		fflush(stdin);
		gets(strInput);
		File_Read(strInput, buffer);
		System_HandleFileData(buffer, &temp_item);

		if(System_IsIDUnique(&myQueue, temp_item.ID) == System_no_error)
			if(System_IsCourseIDUnique(&myQueue, &temp_item) == System_no_error)
				Queue_Enqueue(&myQueue, temp_item);
			else
				printf("\t** Duplicate course ID found **\n");
		else
			printf("\n\t** This ID Already Exist .. Try Update Option Instead **\n");
		break;
	case 2:
		printf("\t\t*** Add Manually (only one student at a time) .. *** \n");
		temp_item = Fill_Data();
		if(System_IsIDUnique(&myQueue, temp_item.ID) == System_no_error)
			if(System_IsCourseIDUnique(&myQueue, &temp_item) == System_no_error)
				Queue_Enqueue(&myQueue, temp_item);
			else
				printf("\n\t** Duplicate course ID found **\n");
		else
			printf("** This ID Already Exist .. Try Update Option Instead **\n");
		break;
		break;
	case 3:
		printf("\t\t*** Find By ID .. *** \n");
		printf("\tID: ");
		fflush(stdout);
		scanf("%d", &intInput);
		Queue_FindByID(&myQueue, intInput);
		break;
	case 4:
		printf("\t\t*** Find By Name .. *** \n");
		printf("\tName: ");
		fflush(stdout);
		fflush(stdin);
		gets(strInput);
		Queue_FindByName(&myQueue, strInput);
		break;
	case 5:
		printf("\t\t*** Find By Course ID .. *** \n");
		printf("\tCourse ID: ");
		fflush(stdout);
		scanf("%d", &intInput);
		Queue_FindByCourse(&myQueue, intInput);
		break;
	case 6:
		printf("\t\t*** Number Of Students: %d .. *** \n", myQueue.count);
		break;
	case 7:
		printf("\t\t*** Delete 1st Student .. *** \n");
		if(Queue_Dequeue(&myQueue, &temp_item) == Queue_Empty)
			printf("\t\t ** No Student To Delete ** \n");
		else
		{
			printf("\t\t--------------------------\n");
			printf("\t\t Deleted Student Data .. \n");
			printf("\t\t--------------------------\n");
			Queue_Print_Item(&temp_item);
		}
		break;
	case 8:
		printf("\t\t*** Delete All .. *** \n");
		System_INIT(50);
		break;
	case 9:
		printf("\t\t*** Update Student Data .. *** \n");
		printf("\tID: ");
		fflush(stdout);
		scanf("%d", &intInput);
		Queue_UpdateByID(&myQueue, intInput);
		break;
	case 10:
		printf("\t\t*** Display Student Data .. *** \n");
		Queue_Print(&myQueue);
		break;
	default:
		break;
	}
	System_Options();
}

void System_Update(elementType* selected)
{
	int option = -1;
	float tempFloat = 0;
	int tempInt = 0;
	char tempStr[10];

	do{
		printf("\t0: Exit\n");
		printf("\t1: Update First Name\n");
		printf("\t2: Update Last Name\n");
		printf("\t3: Update GPA\n");
		printf("\t4: Update Couses\n");
		printf("\tUpdate Option: ");
		fflush(stdout);
		scanf("%d", &option);

		switch (option) {
		case 0:
			printf("\t*** End Updates *** \n");
			break;
		case 1:
			printf("\t\tEnter New First Name: ");
			fflush(stdin);
			fflush(stdout);
			gets(tempStr);
			strcpy(selected->firstName, tempStr);
			break;
		case 2:
			printf("\t\tEnter New Last Name: ");
			fflush(stdin);
			fflush(stdout);
			gets(tempStr);
			strcpy(selected->lastName, tempStr);
			break;
		case 3:
			printf("\t\tEnter New GPA: ");
			fflush(stdout);
			scanf("%f", &tempFloat);
			selected->GPA = tempFloat;
			break;
		case 4:
			printf("\t\tEnter New No. Of Courses: ");
			fflush(stdout);
			scanf("%d", &selected->nC);
			for(int i=0; i<selected->nC; i++)
				selected->courses[i] = 0;

			for(int i=0; i<selected->nC; i++)
			{
				printf("\t\t\tCourse No.%d: ", i+1);
				fflush(stdout);
				scanf("%d", &selected->courses[i]);
			}
			break;
		default:
			printf("\t\t*** Wrong Choice .. ***\n");
			break;
		}
		printf("\t********************************\n");
	}while(option != 0);
}

void System_HandleFileData(char *buffer, elementType* data)
{
	int numCourses = 0;
	sscanf(buffer, "%d,%9[^,],%9[^,],%f,%d,%d,%d,%d,%d",
			&data->ID,
			data->firstName,
			data->lastName,
			&data->GPA,
			&data->courses[0],
			&data->courses[1],
			&data->courses[2],
			&data->courses[3],
			&data->courses[4]);

	for (int i = 0; i < 5; i++) {
		if (data->courses[i] != 0) {
			numCourses++;
		}
	}

	data->nC = numCourses;
}

System_State_t System_IsIDUnique(Queue_t* Queue, int ID)
{
	elementType* current = Queue->tail;
	for(int i=0; i<Queue->count; i++)
		if(current->ID == ID)
			return System_error;
		else
			current++;
	return System_no_error;
}

System_State_t System_IsCourseIDUnique(Queue_t* Queue, elementType* student)
{
	for (int i = 0; i < student->nC; i++)
		for (int j = i + 1; j < student->nC; j++)
			if (student->courses[i] == student->courses[j])
				return System_error;
	return System_no_error;
}
