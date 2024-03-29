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
    SWITCH_ON_OFF_Init();
    LED_Flash_Switch_Init();
    SCH_Add_Task(SWITCH_ON_OFF_Update, 0, 10);
    SCH_Add_Task(LED_Flash_Switch_Update, 0, 20);
    SCH_Init_T0();
    SCH_Start();
    while(1){
        SCH_Dispatch_Tasks();
    }
}

