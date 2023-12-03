/*
 * app.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_APP_H_
#define SYSTEMLAYERS_APP_APP_H_

#include "HAL_Layer/LCD/Static/inc/LCD.h"

#define LCD_LINES 2
#define LCD_CHARACTERS 16

void Keypad_LCD_Init(void);
void Keypad_LCD_Update(void);

#endif /* SYSTEMLAYERS_APP_APP_H_ */
