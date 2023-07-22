/*
 * main.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include "main.h"

void system_init(void){
    PLL_Init();
    Port_Init();
    Gpt_Init();
    IntCtrl_Init();
}

int main(){
    system_init();
    // Add the 'short' task (on for ~1000 ms, off for ~1000 ms)
    // THIS IS A PRE-EMPTIVE TASK
    hSCH_Add_Task(LED_Short_Update, 0, 1000, 0);

    // Add the 'long' task (duration 10 seconds)
    // THIS IS A CO-OPERATIVE TASK
    hSCH_Add_Task(LED_Long_Update, 0, 20000, 1);

    hSCH_Init_T0();
    hSCH_Start();
    while(1){
        hSCH_Dispatch_Tasks();
    }
}

