/*
 * main.h
 *
 *  Created on: Mar 17, 2021
 *      Author: abduy
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"

#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"


void gpio_a(void);
void x(void);
void y(void);
void timer0_init(void);
void timer1_init(void);
void delay(int i);
void t0_func(void);
void t1_func(void);


void gpio_a(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, 0x1C);
}

void x(){
    int q;
    q = GPIOPinRead(GPIO_PORTA_BASE, 0x04);
    if(q){
        GPIOPinWrite(GPIO_PORTA_BASE, 0x04, 0);
    }else{
        GPIOPinWrite(GPIO_PORTA_BASE, 0x04, 0xff);
    }
}

void y(){
    int q;
    q = GPIOPinRead(GPIO_PORTA_BASE, 0x08);
    if(q){
        GPIOPinWrite(GPIO_PORTA_BASE, 0x08, 0);
    }else{
        GPIOPinWrite(GPIO_PORTA_BASE, 0x08, 0xff);
    }
}

void timer0_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerDisable(TIMER0_BASE, TIMER_A);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 32767);
    TimerPrescaleSet(TIMER0_BASE, TIMER_A, 0xff);
    TimerIntRegister(TIMER0_BASE, TIMER_A, t0_func);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void timer1_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_A);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 32767);
    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 0x00);
    TimerIntRegister(TIMER1_BASE, TIMER_A, t1_func);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE, TIMER_A);
}

void t0_func(){
    uint32_t q;
    q = TimerIntStatus(TIMER0_BASE, 1);
    TimerIntClear(TIMER0_BASE, q);
    x();
    delay(30);
}

void t1_func(){
    uint32_t q;
    q = TimerIntStatus(TIMER1_BASE, 1);
    TimerIntClear(TIMER1_BASE, q);
    y();
    delay(30);
}

void delay(int i){
    int j;
    for( ;i > 0; i--){
        for(j = 16000; j > 0; j--){

        }
    }
}

#endif /* MAIN_H_ */
