/*
 * led_flash.c
 *
 *  Created on: Mar 25, 2021
 *      Author: abduy
 */


#include "led_flash.h"

//Private Variable

static uint32_t LED_state_G;

void LED_Flash_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0X08;
    GPIODigitalOutMine(GPIO_PORTF_BASE, 0x08);
}

void LED_Flash_Update(){
    LED_state_G = GPIOPinRead(GPIO_PORTF_BASE, 0x08);
    LED_state_G = ~(LED_state_G);
    GPIOPinWrite(GPIO_PORTF_BASE, 0x08, LED_state_G);
}
