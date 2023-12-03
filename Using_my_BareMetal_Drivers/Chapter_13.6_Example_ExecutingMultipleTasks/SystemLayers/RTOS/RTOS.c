/*
 * void Timer_2_Init(void);.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */


#include <SystemLayers/RTOS/RTOS.h>
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"

void Timers_Init(void){
    Timer_0A_Init();
    Timer_1A_Init();
    Timer_2A_Init();
}

void Timer_0A_Init(void){
    Gpt_EnableNotification(Gpt_Channel_Normal_0);
    Gpt_StartTimer(Gpt_Channel_Normal_0, INTERRUPT_Timer_0_Overflow * 1000);    // 5ms
}

void Timer_1A_Init(void){
    Gpt_EnableNotification(Gpt_Channel_Normal_1);
    Gpt_StartTimer(Gpt_Channel_Normal_1, INTERRUPT_Timer_1_Overflow * 1000);    // 5ms
}

void Timer_2A_Init(void){
    Gpt_EnableNotification(Gpt_Channel_Normal_2);
    Gpt_StartTimer(Gpt_Channel_Normal_2, INTERRUPT_Timer_2_Overflow * 1000);    // 5ms
}

void EnableInterrupt(){
//    Enable_Interrupts();
}

