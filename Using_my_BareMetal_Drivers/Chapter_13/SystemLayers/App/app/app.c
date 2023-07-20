/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

void X_Init(void){
    Dio_Init();
}

void X(void){
    DigitalInterface_Type* myDio = Digital_Interface_Create(DIO_Channel1_F);
    while(1){
        myDio->Write_Toggle(myDio);
    }
}
