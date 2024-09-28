/*
 * Pressure_Sensor.c
 *
 *  Created on: Sep 22, 2024
 *      Author: Nouran S.
 */
#include "Pressure_Sensor.h"
#include "driver.h"

int pressure_value;
int pulling = 100;

void (*Sensor_State_Ptr) ();
Sensor_StateID_t Sensor_StateID;

void Sensor_INIT()
{
	GPIO_INITIALIZATION();
}

STATE_DEFINE(Sensor_Reading)
{
	Sensor_StateID = Sensor_Reading;
	pressure_value = getPressureVal();
	Send_Pressure_Value(pressure_value);
	Sensor_State_Ptr = STATE(Sensor_Waiting);
}

STATE_DEFINE(Sensor_Waiting)
{
	Sensor_StateID = Sensor_Waiting;
	Delay(pulling);
	Sensor_State_Ptr = STATE(Sensor_Reading);
}

