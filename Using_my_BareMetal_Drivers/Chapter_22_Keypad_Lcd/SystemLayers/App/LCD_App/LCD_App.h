/*
 * LCD_App.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Abdu
 *      This file uses the LCD via a global buffer.
 *      all you have to do is to fill the buffer and the LCD will automatically write it.
 *      all it uses is LCD HAL Library
 */

#ifndef SYSTEMLAYERS_APP_LCD_APP_LCD_APP_H_
#define SYSTEMLAYERS_APP_LCD_APP_LCD_APP_H_

#include "HAL_Layer/LCD/Static/inc/LCD_Types.h"

#define LCD_Lines 2
#define LCD_Characters 16


void LCD_App_Init(LCD_Handler_Type* the_lcd);
void LCD_App_Update(void);



#endif /* SYSTEMLAYERS_APP_LCD_APP_LCD_APP_H_ */
