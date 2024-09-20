/*
 * CA.c
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */
#include <stdio.h>
#include <stdlib.h>
#include "US_Sensor.h"
#include "state.h"

int US_distance = 0;

void (*US_State_Ptr) ();
US_StateID_t US_StateID;

int Ultrasonic_read_distance(int min, int max, int count);

STATE_DEFINE(US_Reading)
{
    US_StateID = US_Reading;
    US_distance = Ultrasonic_read_distance(45, 55, 1);
    printf("US Reading: Distance = %d \n", US_distance);
    US_Set_Distance(US_distance);
    US_State_Ptr = STATE(US_Reading);
}

void US_INIT()
{
	// INIT US Sensor Driver
	printf("INIT US Sensor .. \n");
}

int Ultrasonic_read_distance(int min, int max, int count)
{
    int randNum;
    for (int i = 0; i < count; i++)
        randNum = rand() % (max - min + 1) + min;
    return randNum;
}

