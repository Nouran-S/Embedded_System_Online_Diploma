/*
 * Controller.c
 *
 *  Created on: Sep 27, 2024
 *      Author: DELL
 */
#include "Controller.h"
#include "state.h"

int pressure_value;
int threshold = 20;

void (*Controller_State_Ptr) ();
Controller_StateID_t Controller_StateID;

STATE_DEFINE(Controller_Waiting)
{
	Controller_StateID = Controller_Waiting;
}

STATE_DEFINE(Controller_AlarmOn)
{
	Controller_StateID = Controller_AlarmOn;
	Start_Alarm();
	Controller_State_Ptr = STATE(Controller_Storing);
}

STATE_DEFINE(Controller_Storing)
{
	Controller_StateID = Controller_Storing;
	// Store in a Flash Memory
	Controller_State_Ptr = STATE(Controller_Storing);
}

void Send_Pressure_Value(int pressure)
{
	pressure_value = pressure;
	(pressure_value >= threshold) ? (Controller_State_Ptr = STATE(Controller_AlarmOn)) : (Controller_State_Ptr  = STATE(Controller_Storing));
}
