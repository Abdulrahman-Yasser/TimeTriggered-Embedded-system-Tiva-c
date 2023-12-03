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


typedef enum{
    OFF, ON_STATE_1, ON_STATE_2
}LED_State_t;

#define ON 0xff
#define OFF 0x00


#define Red_light (*(volatile uint32*)(GPIO_PORTF_BASE_ADDRESS+(1<<3)))


extern enum {
    Switch_State_Released, Switch_State_A, Switch_State_B, Switch_State_C, Switch_State_D
}Switch_State_t;
// ------ Private variable definitions ------------------------------

static uint16 Blocking_G, Blocking_2_G;
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
    static uint8 sw_blocking = 0;
    /* This approach consumes much time, a better approach is to arrange those values
     * into array and map the array through the enum, but whatever. It's just
     * a prove of concept code */
    switch(Switch_State_t){
    case Switch_State_Released:
        return;
    case Switch_State_A :
        Blocking_G = 60;
        break;
    case Switch_State_B :
        Blocking_G = 40;
        break;
    case Switch_State_C :
        Blocking_G = 20;
        break;
    case Switch_State_D :
        Blocking_G = 10;
        break;
    }
    if(Blocking_G != Blocking_2_G){
        Blocking_2_G = Blocking_G;
        sw_blocking = Blocking_G;
    }
    if(!sw_blocking--){
        /* Toggling */
        if(LED_state_G){
            LED_state_G = 0;
            Red_light = OFF;
        }else{
            LED_state_G = 1;
            Red_light = ON;
        }

    }

}

