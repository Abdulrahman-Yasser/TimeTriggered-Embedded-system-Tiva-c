/*
 * led_flash.c
 *
 *  Created on: Mar 25, 2021
 *      Author: abduy
 */


#include "led_flash.h"


void Test_200ms_T0(void);

//Private Variable

static uint32_t LED_state_G;

void LED_Flash_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0X08;
    GPIODigitalOutMine(GPIO_PORTF_BASE, 0x08);
}

void SWT_Flash_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x11;
    GPIODigitalInMine(GPIO_PORTF_BASE, 0x11);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, 0x1C);
}

void LED_Flash_Update(){
    LED_state_G = GPIOPinRead(GPIO_PORTF_BASE, 0x08);
    LED_state_G = ~(LED_state_G);
    GPIOPinWrite(GPIO_PORTF_BASE, 0x08, LED_state_G);
}

void SWT_Flash_Update(){
    uint8_t SWT_state;
    Test_200ms_T0();
    while( (!(GPIOPinRead(GPIO_PORTF_BASE, 0x11))) && (!(TimerIntStatus(TIMER0_BASE, 0) & TIMER_TIMA_TIMEOUT )));
    SWT_state = GPIOPinRead(GPIO_PORTF_BASE, 0x11);

    switch(SWT_state){
    case 0x00 :
        GPIOPinWrite(GPIO_PORTA_BASE, 0x10, 0x1C);
        return 0;
    case 0x01 :
        GPIOPinWrite(GPIO_PORTA_BASE, 0x04, 0x0C);
        return 1;
    case 0x10 :
        GPIOPinWrite(GPIO_PORTA_BASE, 0x08, 0x0C);
        return 2;
    case 0x11 :
        GPIOPinWrite(GPIO_PORTA_BASE, 0x0C, 0x0C);
        return 3;
    }
}
void timer0_init(uint16_t timerLoad){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerDisable(TIMER0_BASE, TIMER_A);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT_UP);
    TimerLoadSet(TIMER0_BASE, TIMER_A, timerLoad);
    TimerPrescaleSet(TIMER0_BASE, TIMER_A, 0xff);
    TimerIntRegister(TIMER0_BASE, TIMER_A, SCH_Update);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void Test_200ms_T0(void){
    timer0_init(0x7fff);
}

