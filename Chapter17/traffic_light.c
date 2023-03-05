/*
 * traffic_light.c
 *
 *  Created on: Mar 29, 2021
 *      Author: abduy
 */


#include "traffic_light.h"

#define LED_short_pin 0x08
#define LED_long_pin 0x30

#define LED_LONG_ON GPIOPinWrite(GPIO_PORTA_BASE, LED_long_pin, 0xff);
#define LED_LONG_OFF GPIOPinWrite(GPIO_PORTA_BASE, LED_long_pin, 0x00);
#define LED_SHORT_ON GPIOPinWrite(GPIO_PORTA_BASE, LED_short_pin, 0xff);
#define LED_SHORT_OFF GPIOPinWrite(GPIO_PORTA_BASE, LED_short_pin, 0x00);

#define LOCKED 0
#define UNLOCKED 1

//------------ Private Functions -----------------
void HW_Init(void);
void timer2_init(uint16_t timerPresc);
void timer2_delay(uint16_t timerLoad);

//------------ Public Variables  -----------------
static int8_t LED_short_state_G = 0;

static int8_t LED_lock_G = UNLOCKED;

//------------- Function -------------//
void LED_Init(){
    LED_short_state_G = 0;
    HW_Init();
    timer2_init(0xff);
    LED_lock_G = UNLOCKED;
}


void LED_Short_Update(){
    if(LED_lock_G == LOCKED){
        return;
    }

//    LED_lock_G = LOCKED;
    if(LED_short_state_G){
        LED_short_state_G = 0;
        LED_SHORT_OFF;
    }else{
        LED_short_state_G = 1;
        LED_SHORT_ON;
    }
//    LED_lock_G = UNLOCKED;

}

void LED_Long_Update(){
    int8_t i;
    if(LED_lock_G == LOCKED){
        return;
    }

//    LED_lock_G = LOCKED;
    for(i = 0; i < 5; i++){
        LED_LONG_ON;
        timer2_delay(0xf7ff);
        while(!((TimerIntStatus(TIMER2_BASE, 0)) & TIMER_RIS_TATORIS));
        TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
        LED_LONG_OFF;
        timer2_delay(0xf7ff);
        while(!((TimerIntStatus(TIMER2_BASE, 0)) & TIMER_RIS_TATORIS));
        TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
    }
//    LED_lock_G = UNLOCKED;

}

void HW_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, 0x38);
}

void timer2_init(uint16_t timerPresc){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerDisable(TIMER2_BASE, TIMER_A);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT_UP);
    TimerPrescaleSet(TIMER2_BASE, TIMER_A, timerPresc);
}

void timer2_delay(uint16_t timerLoad){
    TimerLoadSet(TIMER2_BASE, TIMER_A, timerLoad);
    TimerEnable(TIMER2_BASE, TIMER_A);
}
