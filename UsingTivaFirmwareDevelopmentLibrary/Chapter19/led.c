/*
 * led.c
 *
 *  Created on: Apr 24, 2021
 *      Author: abduy
 */


#include "led.h"
/************ Public variables *****************/

extern int8_t SW_pressed_G;

/************ Private variables *****************/
#define LED_pin 0x0E

#define LED_pin HWREG(GPIO_PORTF_BASE + GPIO_O_DATA)

static int8_t LED_state_G;

/************ Private functions *****************/


void LED_flash_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0X0E;
//    GPIODigitalInMine(GPIO_PORTF_BASE, 0x11);
    GPIODigitalOutMine(GPIO_PORTF_BASE, 0x0E);
    LED_state_G = 0;
}

void LED_flash_update(void){
    if(!SW_pressed_G){
        return;
    }
    if(LED_state_G == 1){
        LED_state_G = 0;
        LED_pin = 0;
    }else{
        LED_state_G = 1;
        LED_pin = 1;
    }
}

