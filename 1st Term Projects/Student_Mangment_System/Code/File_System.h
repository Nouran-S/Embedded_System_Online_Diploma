/*
 * File_System.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Nouran S.
 */

#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

typedef enum{
	File_no_error,
	File_error,
	File_Null,
}File_State_t;

File_State_t File_Create(char *filename);
File_State_t File_Read(char *filename, char* buffer);

#endif /* FILE_SYSTEM_H_ */
