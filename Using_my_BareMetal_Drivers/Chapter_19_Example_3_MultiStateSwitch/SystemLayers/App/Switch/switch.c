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
#define SW_PRESSED_C_ms (1500)
#define SW_PRESSED_D_ms (2000)
#define SW_THRES (3000)
#define SW_PRESSED 1

// ------ Public variable definitions ------------------------------
enum {
    Switch_State_Released, Switch_State_A, Switch_State_B, Switch_State_C, Switch_State_D
}Switch_State_t;


// ------ Private variable definitions ------------------------------

static uint16 Sw_press_duration_G = 0;

static Button_Type* my_button;


void SWITCH_ON_OFF_Init(void){
    Switch_State_t = Switch_State_Released; // Switch is initially OFF
    Sw_press_duration_G = 0;
}


void SWITCH_ON_OFF_Update(void){
    my_button->Read(my_button);
    if(my_button->Last_State == SW_PRESSED){
        Sw_press_duration_G += 1;
        switch(Sw_press_duration_G){
        case SW_PRESSED_A_ms :
            Switch_State_t = Switch_State_A;
            break;
        case SW_PRESSED_B_ms :
            Switch_State_t = Switch_State_B;
            break;
        case SW_PRESSED_C_ms :
            Switch_State_t = Switch_State_C;
            break;
        case SW_PRESSED_D_ms :
            Switch_State_t = Switch_State_D;
            break;
        }
        return;
    }
    Switch_State_t = Switch_State_Released;
    Sw_press_duration_G = 0;
}


