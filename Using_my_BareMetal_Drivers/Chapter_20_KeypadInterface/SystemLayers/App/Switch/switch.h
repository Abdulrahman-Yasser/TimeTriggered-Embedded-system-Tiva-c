/*
 * app.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_APP_SWITCH_H_
#define SYSTEMLAYERS_APP_SWITCH_H_

#include "MCAL_Layer/DIO/Static/inc/DIO_Types.h"

#define SWITCH_CHANNEL DIO_Channel0_F

void SWITCH_ON_OFF_Init(void);
void SWITCH_ON_OFF_Update(void);

#endif /* SYSTEMLAYERS_APP_APP_H_ */
