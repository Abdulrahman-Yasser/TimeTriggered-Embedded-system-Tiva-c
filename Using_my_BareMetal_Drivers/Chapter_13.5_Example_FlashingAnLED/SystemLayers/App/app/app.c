/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../General_Mcal/GPT/Static/inc/GPT.h"

void X_Init(void){
    Gpt_SetCallBackFunction(Gpt_Channel_Normal_0, X, Gpt_InterruptOverFlow);
}

void X(void){
    Dio_FlipChannel(DIO_Channel1_F);
}
