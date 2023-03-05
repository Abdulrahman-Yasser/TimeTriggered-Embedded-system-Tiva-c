/*
 * traffic_light.h
 *
 *  Created on: Mar 29, 2021
 *      Author: abduy
 */

#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

#include <stdint.h>
#include <stdbool.h>


#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"


#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

void TRAFFIC_LIGHT_Init(const int16_t START_STATE);
void TRAFFIC_LIGHT_Update(void);


#endif /* TRAFFIC_LIGHT_H_ */
