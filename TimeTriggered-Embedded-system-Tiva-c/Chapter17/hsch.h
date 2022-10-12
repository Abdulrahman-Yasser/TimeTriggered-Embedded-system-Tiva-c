/*
 * hSCH.h
 *
 *  Created on: Mar 28, 2021
 *      Author: abduy
 */

#ifndef HSCH_H_
#define HSCH_H_

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


//Public typedef
typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint8_t Period;
    uint8_t RunMe;
    uint8_t CO_OP;
}sTask;

//Public Functions

int8_t hSCH_Add_Task(void (*pFunction)(),
                    int32_t DELAY,
                    int32_t PERIOD,
                    int8_t co_op);

void hSCH_Dispatcher_Tasks(void);

void hSCH_Init_T2(uint32_t timer_value);

// -------- Public Constants ---------------

#define hSCH_MAX_TASKS 3

#define RETURN_NORMAL 0
#define RETURN_ERROR 1

#define ERROR_hSCH_TOO_MANY_TASKS 1
#define ERROR_hSCH_CANNOT_DELETE_TASK 2

#define ERROR_hSCH_WAITING_FOR_SLAVE_TO_ACK 0xAA
#define ERROR_hSCH_WAITING_FOR_START_COMMAND_FROM_MASTER 0xAA

#define ERROR_hSCH_ONE_OR_MORE_SLAVE_DID_NOT_START 0xA0
#define ERROR_hSCH_LOST_SLAVE 0x80

#define ERROR_I2C_WRITE_BYTE_MC 11
#define ERROR_I2C_READ_BYTE_MC 12
#define ERROR_I2C_WRITE_BYTE 13
#define ERROR_I2C_READ_BYTE 14

#define ERROR_USART_TI 21
#define ERROR_USART_WRITE_CHAR 22

#endif /* HhSCH_H_ */
