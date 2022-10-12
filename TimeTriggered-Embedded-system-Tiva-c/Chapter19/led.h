/*
 * led.h
 *
 *  Created on: Apr 24, 2021
 *      Author: abduy
 */

#ifndef LED_H_
#define LED_H_

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

void LED_flash_init(void);

void LED_flash_update(void);


#endif /* LED_H_ */
