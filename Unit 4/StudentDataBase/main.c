/*
 * main.c
 *
 *  Created on: Sep 15, 2024
 *      Author: Nouran
 */
#include <stdio.h>
#include "DataBase.h"

int main()
{
	int n = -1;
	struct SStudentData temp;

	do {
		printf("** Choose one of the following options **\n");
		printf("\t0: Exit\n");
		printf("\t1: Add Student\n");
		printf("\t2: Delete Student\n");
		printf("\t3: Delete All Students\n");
		printf("\t4: View Students\n");
		printf("\t5: Find Student From First \n");
		printf("\t6: Find Student From Last\n");
		printf("\t7: Find No. of Student\n");
		printf("Option No: ");
		fflush(stdout);
		scanf("%d", &n);
		printf("********************************************\n");

		switch (n)
		{
		case 0:
			printf("\n\t*** Adios *** \t\n");
			break;
		case 1:
			LIST_ADD();
			break;
		case 2:
			LIST_Delete();
			break;
		case 3:
			LIST_DeleteAll();
			printf("** Delete All Done ** \n");
			break;
		case 4:
			LIST_Print();
			break;
		case 5:
			if(LIST_Find(&temp, LIST_Find_First) == LIST_Found)
			{
				printf("Data the selected index ...\n");
				printf("\tStudent ID: %d \n", temp.ID);
				printf("\tStudent Name: %s \n", temp.name);
				printf("\tStudent Height: %0.3f \n", temp.height);
			}
			else
				printf("** No Data at the selected index ** \n");
			printf("********************************************\n");
			break;
		case 6:
			if(LIST_Find(&temp, LIST_Find_Last) == LIST_Found)
			{
				printf("Data the selected index ...\n");
				printf("\tStudent ID: %d \n", temp.ID);
				printf("\tStudent Name: %s \n", temp.name);
				printf("\tStudent Height: %0.3f \n", temp.height);
			}
			else
				printf("** No Data at the selected index ** \n");
			printf("********************************************\n");
			break;
		case 7:
			int len = LIST_GetLength();
			printf("Length = %d \n", len);
			printf("********************************************\n");
			break;
		default:
			printf("** Wrong Choice ** \n");
			printf("********************************************\n");
		}

	} while (n != 0);

	return 0;
}
