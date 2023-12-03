/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/app/app.h>

#include "Common/Mcu_Hw.h"
#include "Common/Std_Types.h"
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"

#include <SystemLayers/RTOS/TimeOut/Timeout.h>


#define ON 0xff
#define OFF 0x00

#define RED_DURATION (10)
#define RED_AND_AMBER_DURATION (10)
#define GREEN_DURATION RED_DURATION
#define AMBER_DURATION RED_AND_AMBER_DURATION



#define Red_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(1<<3)))
#define Green_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(0x1<<5)))
#define Amber_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(5<<3)))
#define white_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(7<<3)))


typedef enum {Red = 5, Red_and_Amber, Green, Amber}states;

states Light_state_G = 0;

/*------------------------------------------------------------------*-
TRAFFIC_LIGHTS_Init()
Prepare for the scheduled traffic light activity.
-*------------------------------------------------------------------*/
void TRAFFIC_LIGHTS_Init(void){
    Light_state_G = Red; // Slave is Green; Master is Red
}

/*------------------------------------------------------------------*-
TRAFFIC_LIGHTS_Update()
Must be called once per second.
-*------------------------------------------------------------------*/
void TRAFFIC_LIGHTS_Update(void){
    static uint32 Time_in_state;
    switch (Light_state_G){
    case Red:
        {
            white_light = OFF;
            Amber_light = OFF;
            Green_light = OFF;
            Red_light = ON;
            if (++Time_in_state == RED_DURATION){
                Light_state_G = Red_and_Amber;
                Time_in_state = 0;
            }
        break;
        }
    case Red_and_Amber:
        {
            // suppose to be red and amber
            white_light = ON;
            if (++Time_in_state == RED_AND_AMBER_DURATION){
                Light_state_G = Green;
                Time_in_state = 0;
            }
            break;
        }
    case Green:
        {
            white_light = OFF;
            Red_light = OFF;
            Amber_light = OFF;
            Green_light = ON;
            if (++Time_in_state == GREEN_DURATION){
                Light_state_G = Amber;
                Time_in_state = 0;
            }
            break;
        }
    case Amber:
        {
            white_light = OFF;
            Red_light = OFF;
            Green_light = OFF;
            Amber_light = ON;
            if (++Time_in_state == AMBER_DURATION){
                Light_state_G = Red;
                Time_in_state = 0;
            }
            break;
        }
    }
}

