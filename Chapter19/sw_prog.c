/*
 * sw_prog.c
 *
 *  Created on: Apr 24, 2021
 *      Author: abduy
 */

#include "sw_prog.h"
#include "main.h"


/****************** Public variables ******************/

int8_t SW_pressed_G = 0;

/****************** Private variables ******************/
#define SW_pin 0x01
#define SW_pin_hw HWREG(GPIO_PORTF_BASE + GPIO_O_DATA)
#define SW_pressed 1
#define SW_thres 3

/****************** Private functions ******************/

void SW_HW_init(void);


/*******************************************************/

void switch_init(void){
    SW_HW_init();
}

void switch_update(void){
    static int8_t duration;
    if(SW_pin_hw == SW_pressed){
        duration += 1;
        if(duration > SW_thres){
            duration = SW_thres;
            SW_pressed_G = 1;
            return;
        }
        SW_pressed_G = 0;
        return;
    }
    duration = 0;
    SW_pressed_G = 0;
}


void SW_HW_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0X11;
    GPIODigitalInMine(GPIO_PORTF_BASE, 0x11);
//    GPIODigitalOutMine(GPIO_PORTF_BASE, 0x0E);
}
