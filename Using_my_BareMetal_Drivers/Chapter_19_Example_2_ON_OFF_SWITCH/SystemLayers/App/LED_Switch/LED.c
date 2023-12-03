/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/LED_Switch/LED.h>
#include "Common/Mcu_Hw.h"
#include "Common/Std_Types.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"


#define ON 0xff
#define OFF 0x00


#define Red_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(1<<3)))


extern uint8 Sw_pressed_G;

// ------ Private variable definitions ------------------------------

static uint8 LED_state_G;

/*------------------------------------------------------------------*-
TRAFFIC_LIGHTS_Init()
Prepare for the scheduled traffic light activity.
-*------------------------------------------------------------------*/
void LED_Flash_Switch_Init(void){
    LED_state_G = 0; // Slave is Green; Master is Red
}

/*------------------------------------------------------------------*-
TRAFFIC_LIGHTS_Update()
Must be called once per second.
-*------------------------------------------------------------------*/
void LED_Flash_Switch_Update(void){
    if(!Sw_pressed_G){
        return;
    }
    if(LED_state_G){
        LED_state_G = 0;
        Red_light = OFF;
    }else{
        LED_state_G = 1;
        Red_light = ON;
    }
}

