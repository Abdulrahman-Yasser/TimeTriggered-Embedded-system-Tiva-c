/*
 * Alarm.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#include "Alarm.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

#include "../TemperatureSensor/TemperatureGlobalData.h"
#include "../TemperatureMonitoringSystem_Cfg.h"

static DigitalInterface_Type *myAlarmBuzzer;

void AlarmInit(void){
    myAlarmBuzzer = Digital_Interface_Create(DIO_Channel2_B);
}


void Alarm(uint8 OverUnderTemperature){
    if(OverUnderTemperature == ALARM_OVER_TEMPERATURE){
        myAlarmBuzzer->Write_High(myAlarmBuzzer);
    }else{
        myAlarmBuzzer->Write_High(myAlarmBuzzer);
    }
}


void AlarmUpdateTask(void){
    if(TemperatureValue_g >= TEMPERATURE_THRESHOLD){
        Alarm(ALARM_OVER_TEMPERATURE);
    }else{
        Alarm(ALARM_UNDER_TEMPERATURE);
    }
}
