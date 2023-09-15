/*
 * app.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_SWITCH_H_
#define SYSTEMLAYERS_APP_SWITCH_H_

#include "../General_HAL/Keypad/Static/inc/keypad.h"

#define KEYPAD_RECV_BUFFER_LENGTH 6

void Keypad_App_Init(void);
void Keypad_App_Update(void);
uint8 KEYPAD_Get_Data_From_Buffer(sint8* const pKey, sint8* const pFuncKey);
#endif /* SYSTEMLAYERS_APP_APP_H_ */
