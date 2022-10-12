/*
 * uart.h
 *
 *  Created on: Apr 22, 2021
 *      Author: abduy
 */

#ifndef MY_UART_H_
#define MY_UART_H_

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


void uart1_isr_init(uint16_t baud_rate, void (*pfun)(void));
void uart1_init(uint16_t baud_rate);
bool uart_ts_check(void);
void uart_delay_init(uint16_t timerPresc);
void uart_delay_start(int timerLoad);
void uart_delay_fStart(int timerLoad);
bool uart_delay_fCheck(void);
void uart_delay_stop(void);

#endif /* MY_UART_H_ */
