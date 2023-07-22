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

#define LONG_CHANNEL_1    DIO_Channel1_F
#define LONG_CHANNEL_2    DIO_Channel2_F
#define SHORT_CHANNEL    DIO_Channel3_F


// For the lock mechanism

#define LOCKED 1
#define UNLOCKED 0

// ------ Private variable definitions ------------------------------
static uint8 LED_short_state_G;

// The lock flag
static uint8 LED_lock_G = UNLOCKED;

void LED_Init(void){
    LED_short_state_G = 0;
    Dio_WriteChannel(LONG_CHANNEL_1, DIO_Level_LOW);
    Dio_WriteChannel(LONG_CHANNEL_2, DIO_Level_LOW);
    LED_lock_G = UNLOCKED;
}



void LED_Short_Update(void){
    // The port has a lock
    // If it is locked, we simply return
    if (LED_lock_G == LOCKED){
        return;
    }
    // Port is free - lock it
    LED_lock_G = LOCKED;

    // Change the LED from OFF to ON (or vice versa)
    LED_short_state_G = Dio_FlipChannel(SHORT_CHANNEL);

    // Unlock the port
    LED_lock_G = UNLOCKED;
}



void LED_Long_Update(void){
    uint8 i;
    // The port has a lock
    // If it is locked, we simply return
    if (LED_lock_G == LOCKED){
        return;
    }
    // Port is free - lock it
    LED_lock_G = LOCKED;
    for (i = 0; i < 5; i++){
        Dio_WriteChannel(LONG_CHANNEL_1, DIO_Level_HIGH);
        Dio_WriteChannel(LONG_CHANNEL_2, DIO_Level_LOW);
        Delay_ms(1000);
        Dio_WriteChannel(LONG_CHANNEL_2, DIO_Level_HIGH);
        Dio_WriteChannel(LONG_CHANNEL_1, DIO_Level_LOW);
        Delay_ms(1000);
    }
    Dio_WriteChannel(LONG_CHANNEL_2, DIO_Level_LOW);
    Dio_WriteChannel(LONG_CHANNEL_1, DIO_Level_LOW);
    // Unlock the port
    LED_lock_G = UNLOCKED;
}
