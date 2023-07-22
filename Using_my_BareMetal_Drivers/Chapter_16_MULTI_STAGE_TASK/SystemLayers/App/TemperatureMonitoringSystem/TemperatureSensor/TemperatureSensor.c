/*
 * TemperatureSensor.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#include "TemperatureSensor.h"
#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

#include "TemperatureGlobalData.h"


void TemperatureInit(void){
    TempDriver_WeatherStation_Init();
}

uint32 TemperatureRead(void){
    return TempDriver_WeatherStation_Read();
}


void TemperatureUpdateTask(void){
    TemperatureValue_g = TemperatureRead();
}
