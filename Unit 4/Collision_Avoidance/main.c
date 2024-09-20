/*
 * main.c
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */

#include <stdio.h>
#include "state.h"
#include "CA.h"
#include "US_Sensor.h"
#include "DC_Motor.h"

void SetUp()
{
	US_INIT();
	DC_INIT();
	CA_State_Ptr = STATE(CA_Waiting);
	US_State_Ptr = STATE(US_Reading);
	DC_State_Ptr = STATE(DC_Idle);
}

void main()
{
	SetUp();

	while(1)
	{
		US_State_Ptr();
		CA_State_Ptr();
		DC_State_Ptr();

		for(int i=0; i<1000; i++); // Delay
	}
}
