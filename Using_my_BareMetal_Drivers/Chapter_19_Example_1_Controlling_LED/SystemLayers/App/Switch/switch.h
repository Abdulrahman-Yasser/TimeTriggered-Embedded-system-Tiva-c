/*
 * app.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_SWITCH_H_
#define SYSTEMLAYERS_APP_SWITCH_H_

#include "../General_Mcal/DIO/Static/inc/DIO_Types.h"

#define SWITCH_CHANNEL DIO_Channel0_F

void Switch_Init(void);
void Switch_Update(void);

#endif /* SYSTEMLAYERS_APP_APP_H_ */
