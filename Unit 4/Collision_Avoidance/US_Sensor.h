/*
 * CA.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */
#ifndef US_SENSOR_H_
#define US_SENSOR_H_

#include "state.h"

typedef enum {
    US_Reading
} US_StateID_t;

extern void (*US_State_Ptr) ();
extern US_StateID_t US_StateID;

STATE_DEFINE(US_Reading);
void US_INIT();

#endif /* US_SENSOR_H_ */
