/*
 * TemperatureSensor.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_TEMPERATURESENSOR_TEMPERATURESENSOR_H_
#define SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_TEMPERATURESENSOR_TEMPERATURESENSOR_H_

#include "../General_Common/Std_Types.h"


void TemperatureInit(void);
uint32 TemperatureRead(void);

void TemperatureUpdateTask(void);

#endif /* SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_TEMPERATURESENSOR_TEMPERATURESENSOR_H_ */