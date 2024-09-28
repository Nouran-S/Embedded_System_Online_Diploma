/*
 * Alarm_System.h
 *
 *  Created on: Sep 22, 2024
 *      Author: Nouran S.
 */

#ifndef ALARM_SYSTEM_H_
#define ALARM_SYSTEM_H_

#include "state.h"

extern int duration;
extern void (*Alarm_State_Ptr)();

typedef enum {
	Alarm_Waiting,
	Alarm_Start,
	Alarm_Stop,
} Alarm_StateID_t;

STATE_DEFINE(Alarm_Waiting);
STATE_DEFINE(Alarm_Start);
STATE_DEFINE(Alarm_Stop);

#endif /* ALARM_SYSTEM_H_ */
