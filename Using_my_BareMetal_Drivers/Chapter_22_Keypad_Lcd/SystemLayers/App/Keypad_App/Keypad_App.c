/*
 * app.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */




#include <SystemLayers/App/Keypad_App/Keypad_App.h>
#include "Common/Mcu_Hw.h"
#include "Common/Std_Types.h"

#include "HAL_Layer/Button_Interface/Static/inc/Button.h"


static sint8 KEYPAD_recv_buffer[KEYPAD_RECV_BUFFER_LENGTH+1][2];

static uint8 KEYPAD_in_read_index;
static uint8 KEYPAD_in_waiting_index;

void Keypad_App_Init(void){
    keypad_Init();
    KEYPAD_in_read_index= 0;
    KEYPAD_in_waiting_index = 0;
}

void Keypad_App_Update(void){
    sint8 Key, FnKey;
    // Scan keypad here...
    if (keypad_ScanSpecificKeypad(0, &Key, &FnKey) == 0){
    // No new key data - just return
        return;
    }
    if (KEYPAD_in_waiting_index == KEYPAD_in_read_index){
        KEYPAD_in_waiting_index = 0;
        KEYPAD_in_read_index = 0;
    }
    KEYPAD_recv_buffer[KEYPAD_in_waiting_index][0] = Key;
    KEYPAD_recv_buffer[KEYPAD_in_waiting_index][1] = FnKey;
    if (KEYPAD_in_waiting_index < KEYPAD_RECV_BUFFER_LENGTH){
    // Increment without overflowing buffer
        KEYPAD_in_waiting_index++;
    }
}


uint8 KEYPAD_Get_Data_From_Buffer(sint8* const pKey, sint8* const pFuncKey){
// If there is new data in the buffer
    if (KEYPAD_in_read_index < KEYPAD_in_waiting_index){
        *pKey = KEYPAD_recv_buffer[KEYPAD_in_read_index][0];
        *pFuncKey = KEYPAD_recv_buffer[KEYPAD_in_read_index][1];
        KEYPAD_in_read_index++;
        return 1;
    }
    return 0;
}

void KEYPAD_Clear_Buffer(void){
    KEYPAD_in_waiting_index = 0;
    KEYPAD_in_read_index = 0;
}


