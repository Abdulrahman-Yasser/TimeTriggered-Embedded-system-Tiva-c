/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"

void X_Init(void){
    Gpt_SetCallBackFunction(Gpt_Channel_Normal_0, X, Gpt_InterruptOverFlow);
}

void X(void){
    Dio_FlipChannel(DIO_Channel1_F);
}
