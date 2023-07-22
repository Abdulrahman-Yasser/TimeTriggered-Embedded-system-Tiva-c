/*
 * MainFurnaceController.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_MAINFURNACECONTROLLER_MAINFURNACECONTROLLER_H_
#define SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_MAINFURNACECONTROLLER_MAINFURNACECONTROLLER_H_

#include "../General_Mcal/DIO/Static/inc/DIO_Types.h"

#define MainFurnaceController_channel           DIO_Channel1_F
#define MainFurnaceController_CONTINUE_HEAT     1
#define MainFurnaceController_STOP_HEAT         0

void MainFurnaceController_Init(void);
void MainFurnaceController_Heat(uint8 state);
void MainFurnaceControllerUpdate_Task(void);

#endif /* SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_MAINFURNACECONTROLLER_MAINFURNACECONTROLLER_H_ */
