/*
 * sch.h
 *
 *  Created on: Mar 28, 2021
 *      Author: abduy
 */

#ifndef SCH_H_
#define SCH_H_

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
}sTask;

//Public Functions

int8_t SCH_Add_Task(void (*pFunction)(),
                    int32_t DELAY,
                    int32_t PERIOD);

void SCH_Dispatcher_Tasks(void);

void SCH_Init_T2(uint32_t timer_value);

// -------- Public Constants ---------------

#define SCH_MAX_TASKS 1

#define RETURN_NORMAL 0
#define RETURN_ERROR 1

#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_CANNOT_DELETE_TASK 2

#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 0xAA
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 0xAA

#define ERROR_SCH_ONE_OR_MORE_SLAVE_DID_NOT_START 0xA0
#define ERROR_SCH_LOST_SLAVE 0x80

#define ERROR_I2C_WRITE_BYTE_MC 11
#define ERROR_I2C_READ_BYTE_MC 12
#define ERROR_I2C_WRITE_BYTE 13
#define ERROR_I2C_READ_BYTE 14

#define ERROR_USART_TI 21
#define ERROR_USART_WRITE_CHAR 22

#endif /* SCH_H_ */
