/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Nouran S.
 * @brief          : Main program body
 ******************************************************************************
 */
#include "driver.h"
#include "state.h"
#include "Alarm_System.h"
#include "Pressure_Sensor.h"
#include "Controller.h"

void SetUp()
{
	Sensor_INIT();
	Sensor_State_Ptr = STATE(Sensor_Waiting);
	Alarm_State_Ptr = STATE(Alarm_Waiting);
	Controller_State_Ptr = STATE(Controller_Waiting);
}

int main(void)
{
	SetUp();
	while(1)
	{
		Sensor_State_Ptr();
		Controller_State_Ptr();
		Alarm_State_Ptr();
	}
}
