/*
 * SendingToLCD.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_SENDINGTOLCD_SENDINGTOLCD_H_
#define SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_SENDINGTOLCD_SENDINGTOLCD_H_


void LCD_Temp_Init(void);
void LCDUpdate(char Message);
void LCD_UpdateTask(void);


#endif /* SYSTEMLAYERS_APP_TEMPERATUREMONITORINGSYSTEM_SENDINGTOLCD_SENDINGTOLCD_H_ */
