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

void Xs_Init(void){
    X_Init();
    X1_Init();
    X2_Init();
}

void X_Init(void){
    Gpt_SetCallBackFunction(Gpt_Channel_Normal_0, X, Gpt_InterruptOverFlow);
}

void X(void){
    Dio_FlipChannel(DIO_Channel1_F);
}


void X1_Init(void){
    Gpt_SetCallBackFunction(Gpt_Channel_Normal_1, X1, Gpt_InterruptOverFlow);
}

void X1(void){
    Dio_FlipChannel(DIO_Channel2_F);
}

void X2_Init(void){
    Gpt_SetCallBackFunction(Gpt_Channel_Normal_2, X2, Gpt_InterruptOverFlow);
}

void X2(void){
    Dio_FlipChannel(DIO_Channel3_F);
}
