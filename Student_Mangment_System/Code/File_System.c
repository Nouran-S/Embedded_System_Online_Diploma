/*
 * File_System.c
 *
 *  Created on: Sep 25, 2024
 *      Author:  Nouran S.
 */
#include <stdio.h>
#include "File_System.h"

File_State_t File_Create(char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
    	printf("\t----------------------------------------------------\n");
        printf("\t ** Error: Could not create file %s\n **", filename);
        printf("\t----------------------------------------------------\n");
        return File_Null;
    }

    printf("\t File '%s' created successfully!\n", filename);
    printf("\t----------------------------------------------------\n");
    fclose(file);

    return File_no_error;
}

File_State_t File_Read(char *filename, char* buffer) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("\t----------------------------------------------------\n");
        printf("\t ** Error: Could not find file: '%s' **\n\t ** Creating one ..! **\n", filename);
        printf("\t----------------------------------------------------\n");
        File_Create(filename);
        return File_Null;
    }

    if (fgets(buffer, 256, file) == NULL) {
        printf("\t ** Error reading file '%s' **\n", filename);
        fclose(file);
        return File_error;
    }

    fclose(file);
    return File_no_error;
}
