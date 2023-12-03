/*
 * main.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_MAIN_H_
#define SYSTEMLAYERS_MAIN_H_

#include <SystemLayers/RTOS/Scheduler/Scheduler.h>

#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/PLL/Static/inc/PLL.h"

#include "../TemperatureMonitoringSystem/Alarm/Alarm.h"
#include "../TemperatureMonitoringSystem/MainFurnaceController/MainFurnaceController.h"
#include "../TemperatureMonitoringSystem/SendingToLCD/SendingToLCD.h"
#include "../TemperatureMonitoringSystem/TemperatureSensor/TemperatureSensor.h"

#include "../app/app.h"

void TasksInit(void){
    AlarmInit();
    MainFurnaceController_Init();
    LCD_Temp_Init();
    TemperatureInit();
}


#endif /* SYSTEMLAYERS_MAIN_H_ */
