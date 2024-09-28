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
#define STATE_CALL(_state_)        ST_##_state_()

void Send_Preseeure_Value(int pressure_value);
void Start_Alarm();
void Store_Value(int pressure_value); // Flash

#endif /* STATE_H_ */
