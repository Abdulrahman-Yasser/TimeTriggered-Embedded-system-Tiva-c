/*
 * SendingToLCD.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#include "SendingToLCD.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"
#include "../TemperatureSensor/TemperatureGlobalData.h"

static LCD_Handler_Type* my_lcd;
char myMessage[]= "Temperature Is ";

void LCD_Temp_Init(void){
    my_lcd = LCD_Create(LCD_Interface_I2C, 0);
}

void LCDUpdate(char Message){
    char SendMessage[2] = {Message, '\0'};
    my_lcd->LCD_Write_Cmd(my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));
    my_lcd->LCD_Write_Data(my_lcd, &SendMessage);
}

void LCD_UpdateTask(void){
    // it will send one char every 10ms, which will be frequent as the example
    static uint8 i = 0;
    if(i < (uint8)sizeof(myMessage)){
        LCDUpdate(myMessage[i]);
        i++;
    }else{
        LCDUpdate(int_to_string(TemperatureValue_g));
        i = 0;
    }
}
