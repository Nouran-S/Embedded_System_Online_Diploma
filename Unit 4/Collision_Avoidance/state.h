/*
 * state.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Nouran
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_DEFINE(_state_) void ST_##_state_()
#define STATE(_state_)             ST_##_state_

void US_Set_Distance(int d);
void DC_Set_Speed(int s);

#endif /* STATE_H_ */
