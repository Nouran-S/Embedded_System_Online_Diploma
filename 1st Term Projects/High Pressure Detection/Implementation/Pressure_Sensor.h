/*
 * Pressure_Sensor.h
 *
 *  Created on: Sep 22, 2024
 *      Author: Nouran S.
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "state.h"

extern int pressure_value;
extern void (*Sensor_State_Ptr)();

typedef enum {
    Sensor_Reading,
    Sensor_Waiting,
} Sensor_StateID_t;

void Sensor_INIT();
STATE_DEFINE(Sensor_Reading);
STATE_DEFINE(Sensor_Waiting);

#endif /* PRESSURE_SENSOR_H_ */
