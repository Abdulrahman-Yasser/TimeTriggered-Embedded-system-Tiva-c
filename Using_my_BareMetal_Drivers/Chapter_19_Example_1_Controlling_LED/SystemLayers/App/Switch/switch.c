/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/Switch/switch.h>
#include "Common/Mcu_Hw.h"
#include "Common/Std_Types.h"

#include "HAL_Layer/Button_Interface/Static/inc/Button.h"



#define SW_PRESSED (1)
#define SW_THRES (3)


// ------ Public variable definitions ------------------------------

uint8 Sw_pressed_G = 0; // The current switch status

static Button_Type* my_button;



void Switch_Init(void){
    my_button = Button_Create(SWITCH_CHANNEL);
}


void Switch_Update(void){
    static uint8 Duration = 0;
    my_button->Read(my_button);

    if(my_button->Last_State == SW_PRESSED){
        Duration += 1;
        if(Duration > SW_THRES){
            Duration = SW_THRES;
            Sw_pressed_G = 1;
            return;
        }
        Sw_pressed_G = 0;
        return;
    }
    Duration = 0;
    Sw_pressed_G = 0;
}


