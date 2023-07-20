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
    IntCtrl_Init();
    Gpt_Init();
//    Disable_Interrupts();
}

int main(){
    system_init();
    Timer_0A_Init();
    X_Init();
    EnableInterrupt();
    while(1){
        Wait_For_Interrupt();
    }
}

