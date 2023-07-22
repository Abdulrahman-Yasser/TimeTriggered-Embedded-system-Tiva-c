/*
 * Alarm.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_ALARM_ALARM_H_
#define SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_ALARM_ALARM_H_

#include "Alarm.h"
#include "../General_Common/Std_Types.h"

#define ALARM_OVER_TEMPERATURE          1
#define ALARM_UNDER_TEMPERATURE         0

void AlarmInit(void);
void Alarm(uint8 OverUnderTemperature);
void AlarmUpdateTask(void);



#endif /* SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_ALARM_ALARM_H_ */
