/*
 * CA.c
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */
#include <stdio.h>
#include <stdlib.h>
#include "DC_Motor.h"
#include "state.h"

int DC_speed = 0;

void (*DC_State_Ptr) ();
DC_StateID_t DC_StateID;

STATE_DEFINE(DC_Idle)
{
	DC_StateID = DC_Idle;
	// Call PWM to set speed = CA_speed;
	printf("DC Motor Idle: Speed = %d \n", DC_speed);
}

STATE_DEFINE(DC_Busy)
{
	DC_StateID = DC_Busy;
	// Call PWM to set speed = CA_speed;
	DC_State_Ptr = STATE(DC_Idle);
	printf("DC Motor Busy: Speed = %d \n", DC_speed);
}

void DC_INIT()
{
	// INIT PWM & DC Motor Driver
	printf("INIT DC Motor .. \n");
}

void DC_Set_Speed(int s)
{
	DC_speed = s;
	DC_State_Ptr = STATE(DC_Busy);
	printf("Collision Avoidance ------------( speed = %d )------------> DC Motor \n", DC_speed);
}
