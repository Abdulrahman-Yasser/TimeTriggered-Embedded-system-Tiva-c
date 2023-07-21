/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../General_Mcal/DIO/Static/inc/DIO.h"


void LED_FlashUpdate_1(void){
    Dio_FlipChannel(DIO_Channel1_F);
}

void LED_FlashUpdate_2(void){
    Dio_FlipChannel(DIO_Channel2_F);
}
