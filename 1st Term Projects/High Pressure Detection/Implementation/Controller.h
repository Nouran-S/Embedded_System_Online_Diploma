/*
 * Controller.h
 *
 *  Created on: Sep 27, 2024
 *      Author: DELL
 */
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "state.h"

extern int pressure_value;
extern int threshold;
extern void (*Controller_State_Ptr)();

typedef enum {
	Controller_Waiting,
	Controller_AlarmOn,
	Controller_Storing,
} Controller_StateID_t;

STATE_DEFINE(Controller_Waiting);
STATE_DEFINE(Controller_AlarmOn);
STATE_DEFINE(Controller_Storing);

#endif
