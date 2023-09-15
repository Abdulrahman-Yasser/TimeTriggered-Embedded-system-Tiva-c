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
    I2C_init();
    IntCtrl_Init();
}


int main(){
    system_init();
    LCD_Handler_Type* lcd_g = LCD_Create(LCD_Interface_I2C, 0);
    Keypad_App_Init();
    LCD_App_Init(lcd_g);
    Keypad_LCD_Init();
    SCH_Add_Task(Keypad_LCD_Update, 0, 100);
    SCH_Add_Task(LCD_App_Update, 0, 1000);
    SCH_Init_T0();
    SCH_Start();
    while(1){
        SCH_Dispatch_Tasks();
    }
}

