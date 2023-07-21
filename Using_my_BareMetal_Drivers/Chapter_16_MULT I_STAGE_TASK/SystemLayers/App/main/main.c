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
    SCH_Add_Task(LED_FlashUpdate_2, 1000, 1000);
    SCH_Add_Task(LED_FlashUpdate_1, 5000, 5000);
    SCH_Init_T0();
    App_Init();
    SCH_Start();
    while(1){
        SCH_Dispatch_Tasks();
    }
}

