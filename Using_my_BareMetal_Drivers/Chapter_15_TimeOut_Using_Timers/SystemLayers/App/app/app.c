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

#include <SystemLayers/RTOS/TimeOut/Timeout.h>




void App_Init(void){
    TimeoutInit();
}



/*
 * Application 1
 */

uint8 Flibbing_a_led(DIO_ChannelType myChannel){
    if(myChannel <= 44){
        Dio_FlipChannel(DIO_Channel1_F);
        return RETURN_FINE;
    }else{
        return RETURN_ERROR;
    }
}

void LED_FlashUpdate_1(void){
    TimeoutStart(1000);
    // either of them will become zero first, it will break
    // one of those lines is when error occurs and the other is the normal one
    while( ( TimeoutStatus() == TIMEOUT_DID_NOT_HAPPENED ) && (Flibbing_a_led(DIO_Channel_NotUsed) == RETURN_ERROR ) );
//    while( ( TimeoutStatus() == TIMEOUT_DID_NOT_HAPPENED ) && (Flibbing_a_led(DIO_Channel1_F) == RETURN_ERROR ) );
    if(TimeoutStatus() == TIMEOUT_DID_HAPPENED){
        Dio_WriteChannel(DIO_Channel1_F, DIO_Level_HIGH);
        Dio_WriteChannel(DIO_Channel2_F, DIO_Level_HIGH);
        Dio_WriteChannel(DIO_Channel3_F, DIO_Level_HIGH);
    }
    TimeoutRefresh();
}

void LED_FlashUpdate_2(void){
    TimeoutStart(1000);
    Dio_FlipChannel(DIO_Channel2_F);
    TimeoutRefresh();
}
