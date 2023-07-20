/*
 * void Timer_2_Init(void);.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */


#include <SystemLayers/RTOS/RTOS.h>
#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

void Timer_1A_Init(void){
    Gpt_Init();
    Gpt_EnableNotification(Gpt_Channel_Normal_0);
    Gpt_StartTimer(Gpt_Channel_Normal_0, INTERRUPT_Timer_2_Overflow);
}

void EnableInterrupt(){
    IntCtrl_Init();
    Enable_Interrupts();
}
