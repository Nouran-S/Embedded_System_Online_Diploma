/*
 * CA.c
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */
#include <stdio.h>
#include <stdlib.h>
#include "CA.h"
#include "state.h"

int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;

void (*CA_State_Ptr) ();
CA_StateID_t CA_StateID;

STATE_DEFINE(CA_Waiting)
{
    CA_StateID = CA_Waiting;
    printf("CA Waiting: Distance = %d \t Speed = %d \n", CA_distance, CA_speed);

    // DC_Motor(Set Speed);
    CA_speed = 0;
    DC_Set_Speed(CA_speed);

}

STATE_DEFINE(CA_Driving)
{
    CA_StateID = CA_Driving;
    printf("CA Driving: Distance = %d \t Speed = %d \n", CA_distance, CA_speed);

    // DC_Motor(Set Speed);
    CA_speed = 30;
    DC_Set_Speed(CA_speed);

}

void US_Set_Distance(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (CA_State_Ptr = STATE(CA_Waiting)) : (CA_State_Ptr = STATE(CA_Driving));
	printf("US Sensor ------------( distance = %d )------------> Collision Avoidance \n", CA_distance);
}
