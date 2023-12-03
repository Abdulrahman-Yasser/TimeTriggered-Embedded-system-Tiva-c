/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/Keypad_Lcd/Keypad_Lcd.h>
#include "../Keypad_App/Keypad_App.h"
#include "../Keypad_Lcd/Keypad_Lcd.h"

#include "Common/Mcu_Hw.h"
#include "Common/Std_Types.h"

#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/Keypad/Static/inc/keypad.h"

static sint8 Char_G;
extern sint8 LCD_DATA_G[LCD_LINES][LCD_CHARACTERS];

LCD_Handler_Type* my_lcd = Null_Ptr;



void Keypad_LCD_Init(void){
    int i;
    char* start_msg = "Type on keypad:   ";
    my_lcd = LCD_Create(LCD_Interface_I2C, 0);
    for(i = 0; i < LCD_CHARACTERS; i++){
        LCD_DATA_G[0][i] = start_msg[i];
        LCD_DATA_G[1][i] = '*';
    }
    Char_G = 0;
}


void Keypad_LCD_Update(void){
    sint8 Key, FnKey;
    Keypad_App_Update();
    if (KEYPAD_Get_Data_From_Buffer(&Key, &FnKey) == 0){
    // Buffer is empty
        return;
    }
    // Function key has been pressed (with another key)
    if (FnKey){
        LCD_DATA_G[1][Char_G] = FnKey;
        if (++Char_G == LCD_CHARACTERS){
            Char_G = 0;
        }
    }
    LCD_DATA_G[1][Char_G] = Key;
    if (++Char_G == LCD_CHARACTERS){
        Char_G = 0;
    }
}

