/*
 * CA.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

typedef enum {
    CA_Waiting,
    CA_Driving
} CA_StateID_t;

extern void (*CA_State_Ptr) ();
extern CA_StateID_t CA_StateID;

STATE_DEFINE(CA_Waiting);
STATE_DEFINE(CA_Driving);

#endif /* CA_H_ */
