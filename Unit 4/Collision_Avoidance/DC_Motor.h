/*
 * CA.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

typedef enum {
    DC_Idle,
    DC_Busy
} DC_StateID_t;

extern void (*DC_State_Ptr) ();
extern DC_StateID_t DC_StateID;

STATE_DEFINE(DC_Idle);
STATE_DEFINE(DC_Busy);
void DC_INIT();

#endif /* DC_MOTOR_H_ */
