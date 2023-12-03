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



#define SW_PRESSED_A_ms (500)
#define SW_PRESSED_B_ms (1000)
#define SW_THRES (1500)


// ------ Public variable definitions ------------------------------
typedef enum{
    Switch_State_Released, Switch_State_A, Switch_State_B
}Switch_State_t;

Switch_State_t Sw_pressed_G = 0; // The current switch status


// ------ Private variable definitions ------------------------------

static uint8 Sw_press_duration_G = 0;
static uint8 Sw_blocked_G = 0;

static Button_Type* my_button;


void SWITCH_ON_OFF_Init(void){
    Sw_pressed_G = Switch_State_Released; // Switch is initially OFF
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
        switch(Sw_press_duration_G){
        case SW_PRESSED_A_ms :
            Sw_pressed_G = Switch_State_A;
            break;
        case SW_PRESSED_B_ms :
            Sw_pressed_G = Switch_State_B;
            break;
        case SW_THRES :
            Sw_pressed_G = Switch_State_Released;
            Sw_press_duration_G = 0;
            Sw_blocked_G = 2000;    // 5 seconds
            break;
        }
        return;
    }
    Sw_press_duration_G = 0;
}


