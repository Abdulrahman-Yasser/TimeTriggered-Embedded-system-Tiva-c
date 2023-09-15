/*
 * LCD_App.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Abdu
 */


#include "LCD_App.h"

#include "../General_HAL/LCD/Static/inc/LCD.h"


sint8 LCD_DATA_G[LCD_Lines][LCD_Characters] = {"PLEASE WAIT     ","....    ....    "};

LCD_Handler_Type* my_ch22_lcd;

void LCD_App_Init(LCD_Handler_Type* the_lcd){
    my_ch22_lcd = the_lcd;
}

void LCD_App_Update(void){
    static uint8 line, character;
    uint8 Tests, Update_required;
    if(my_ch22_lcd == Null_Ptr){
        return;
    }
    Tests = LCD_Characters * LCD_Lines;
    do{
        if(++character == LCD_Characters){
            character = 0;
        }
        if(++ line == LCD_Lines){
            line = 0;
        }
        Update_required = (LCD_DATA_G[line][character] != '\0');
    }while((Tests-- > 0) && (!Update_required) );

    if(Update_required == 0){
        return;
    }

    my_ch22_lcd->LCD_Write_Cmd(my_ch22_lcd, LCD_I2C_SET_DDRAM_ADDRESS(line, character));
    my_ch22_lcd->LCD_Write_Data(my_ch22_lcd, LCD_DATA_G[line][character]);
    LCD_DATA_G[line][character] = '\0';

}

