/*
 * Alarm_System.c
 *
 *  Created on: Sep 22, 2024
 *      Author: Nouran S.
 */
#include "Alarm_System.h"
#include "state.h"
#include "driver.h"

int duration = 1000000;

void (*Alarm_State_Ptr) ();
Alarm_StateID_t Alarm_StateID;

STATE_DEFINE(Alarm_Waiting)
{
	Alarm_StateID = Alarm_Waiting;
}

STATE_DEFINE(Alarm_Start)
{
	Alarm_StateID = Alarm_Start;
	Set_Alarm_actuator(1);
	Delay(duration);
	Alarm_State_Ptr = STATE(Alarm_Stop);
}

STATE_DEFINE(Alarm_Stop)
{
	Alarm_StateID = Alarm_Stop;
	Set_Alarm_actuator(0);
	Alarm_State_Ptr = STATE(Alarm_Waiting);
}

void Start_Alarm()
{
	Alarm_State_Ptr = STATE(Alarm_Start);
}
