/*
 * sw_prog.h
 *
 *  Created on: Apr 24, 2021
 *      Author: abduy
 */

#ifndef SW_PROG_H_
#define SW_PROG_H_


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

void switch_init(void);

void switch_update(void);

#endif /* SW_PROG_H_ */
