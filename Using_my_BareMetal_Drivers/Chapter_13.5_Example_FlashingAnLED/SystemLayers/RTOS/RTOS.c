/*
 * void Timer_2_Init(void);.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */


#include <SystemLayers/RTOS/RTOS.h>
#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

void Timer_0A_Init(void){
    Gpt_EnableNotification(Gpt_Channel_Normal_0);
    Gpt_StartTimer(Gpt_Channel_Normal_0, INTERRUPT_Timer_0_Overflow * 1000);    // 5ms
}

void EnableInterrupt(){
//    Enable_Interrupts();
}

