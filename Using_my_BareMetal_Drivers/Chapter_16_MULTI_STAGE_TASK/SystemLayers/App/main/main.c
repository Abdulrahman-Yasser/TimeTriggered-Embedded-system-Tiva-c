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
    TasksInit();
    SCH_Add_Task(TemperatureUpdateTask, 1000, 1000);
    SCH_Add_Task(AlarmUpdateTask, 1000, 1000);
    SCH_Add_Task(MainFurnaceController_Init, 1000, 1000);
    SCH_Add_Task(LCD_UpdateTask, 1000, 10);
    SCH_Init_T0();
    SCH_Start();
    while(1){
        SCH_Dispatch_Tasks();
    }
}

