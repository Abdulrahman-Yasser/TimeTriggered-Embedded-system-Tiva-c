/*
 * traffic_light.c
 *
 *  Created on: Mar 29, 2021
 *      Author: abduy
 */


#include "traffic_light.h"





#define RED_DURATION 13
#define RED_AND_AMBER_DURATION 7
#define GREEN_DURATION RED_DURATION
#define AMBER_DURATION RED_AND_AMBER_DURATION

#define Red 0
#define Red_and_Amber 1
#define Green 2
#define Amber 3

#define red_pin 0x04
#define amber_pin 0x08
#define green_pin 0x10

#define Red_light_on GPIOPinWrite(GPIO_PORTA_BASE, red_pin, 0xff);
#define Red_light_off GPIOPinWrite(GPIO_PORTA_BASE, red_pin, 0x00);
#define Amber_light_on GPIOPinWrite(GPIO_PORTA_BASE, amber_pin, 0xff);
#define Amber_light_off GPIOPinWrite(GPIO_PORTA_BASE, amber_pin, 0x00);
#define Green_light_on GPIOPinWrite(GPIO_PORTA_BASE, green_pin, 0xff);
#define Green_light_off GPIOPinWrite(GPIO_PORTA_BASE, green_pin, 0x00);


//------------ Private Functions -----------------
void HW_Init(void);

//------------ Public Variables  -----------------
int16_t Light_state_G;

void TRAFFIC_LIGHT_Init(const int16_t START_STATE){
    HW_Init();
    Light_state_G = START_STATE;
}



void TRAFFIC_LIGHT_Update(void){
    static uint16_t Time_in_state;
    switch(Light_state_G){
    case Red:
        Red_light_on;
        Amber_light_off;
        Green_light_off;
        /*  after calling the function 13 times ..
            each time is 1 sec
            all 13 sec
        */
        if(++Time_in_state == RED_DURATION){
            Light_state_G = Red_and_Amber;
            Time_in_state = 0;
        }
        break;
    case Red_and_Amber:
        Red_light_on;
        Amber_light_on;
        Green_light_off;

        /*  after calling the function 7 times ..
            each time is 1 sec
            all 7 sec
        */
        if(++Time_in_state == RED_AND_AMBER_DURATION){
            Light_state_G = Green;
            Time_in_state = 0;
        }
        break;
    case Green:
        Red_light_off;
        Amber_light_off;
        Green_light_on;

        /*  after calling the function 13 times ..
            each time is 1 sec
            all 13 sec
        */
        if(++Time_in_state == GREEN_DURATION){
            Light_state_G = Amber;
            Time_in_state = 0;
        }
        break;
    case Amber:
        Red_light_off;
        Amber_light_on;
        Green_light_off;

        /*  after calling the function 7 times ..
            each time is 1 sec
            all 7 sec
        */
        if(++Time_in_state == AMBER_DURATION){
            Light_state_G = Red;
            Time_in_state = 0;
        }
        break;
    }
}


void HW_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, 0x1C);
}
