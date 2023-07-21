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
    TRAFFIC_LIGHTS_Init();
    SCH_Add_Task(TRAFFIC_LIGHTS_Update, 1000, 1000);
    SCH_Init_T0();
    SCH_Start();
    while(1){
        SCH_Dispatch_Tasks();
    }
}

