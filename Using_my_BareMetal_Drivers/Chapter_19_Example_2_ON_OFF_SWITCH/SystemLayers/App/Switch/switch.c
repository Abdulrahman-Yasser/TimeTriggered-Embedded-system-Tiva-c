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

uint8 Sw_pressed_G ; // The current switch status


// ------ Private variable definitions ------------------------------

static uint8 Sw_press_duration_G;
static uint8 Sw_blocked_G;

static Button_Type* my_button;



void SWITCH_ON_OFF_Init(void){
    Sw_pressed_G = 0; // Switch is initially OFF
    Sw_press_duration_G = 0;
    Sw_blocked_G = 0;
}


void SWITCH_ON_OFF_Update(void){
    if(Sw_blocked_G){
        Sw_blocked_G--;
        return;
    }

    my_button->Read(my_button);
    if(my_button->Last_State == SW_PRESSED){
        Sw_press_duration_G += 1;
        if(Sw_press_duration_G > SW_THRES){
            Sw_press_duration_G = SW_THRES;

            if(Sw_pressed_G == 1){
                Sw_pressed_G = 0;
            }else{
                Sw_pressed_G = 1;
            }
            Sw_blocked_G = 5;
            return;
        }
        // waiting for the whole duration
        return;
    }
    Sw_press_duration_G = 0;
}


