/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"


void LED_FlashUpdate_1(void){
    Dio_FlipChannel(DIO_Channel1_F);
}

void LED_FlashUpdate_2(void){
    Dio_FlipChannel(DIO_Channel2_F);
}
