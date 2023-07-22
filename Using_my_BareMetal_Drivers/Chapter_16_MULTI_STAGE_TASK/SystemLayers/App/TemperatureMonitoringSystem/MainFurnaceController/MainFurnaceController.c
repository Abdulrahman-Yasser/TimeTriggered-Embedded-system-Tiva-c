/*
 * MainFurnaceController.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

/*
 * here the LED represents the heat.
 * If the furnace needs more heat it will be On.
 * If the furnace does not need more heat it will be Off.
 */

#include "../General_Mcal/DIO/Static/inc/DIO.h"
#include "MainFurnaceController.h"
#include "../TemperatureMonitoringSystem_Cfg.h"
#include "../TemperatureSensor/TemperatureGlobalData.h"

void MainFurnaceController_Init(void){

}


void MainFurnaceController_Heat(uint8 state){
    if(state == MainFurnaceController_CONTINUE_HEAT){
        Dio_WriteChannel(MainFurnaceController_channel, DIO_Level_HIGH);
    }else if(state == MainFurnaceController_STOP_HEAT){
        Dio_WriteChannel(MainFurnaceController_channel, DIO_Level_LOW);
    }
}


void MainFurnaceControllerUpdate_Task(void){
    if(TemperatureValue_g >= TEMPERATURE_THRESHOLD){
        MainFurnaceController_Heat(MainFurnaceController_STOP_HEAT);
    }else{
        MainFurnaceController_Heat(MainFurnaceController_CONTINUE_HEAT);
    }
}
