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
//    Disable_Interrupts();
}

int main(){
    system_init();
    Timers_Init();
    Xs_Init();
    EnableInterrupt();
    while(1){
        Wait_For_Interrupt();
    }
}

