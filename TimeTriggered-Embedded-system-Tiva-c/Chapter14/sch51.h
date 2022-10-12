/*
 * sch51.h
 *
 *  Created on: Mar 22, 2021
 *      Author: abduy
 */

#ifndef SCH51_H_
#define SCH51_H_

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




// -------- Public data type declarations ---------------
//Store in DATA area, if possible, for rapid access
//Total memory per task is 7 bytes

typedef struct data{
    void(*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
}sTask;

// -------- Public Function prototypes ---------------
//Core scheduler functions
void SCH_Init_T2(void);

void SCH_Dispatcher_Tasks(void);
int8_t SCH_Add_Task(void (*pFunction)(),
                    int32_t DELAY,
                    int32_t PERIOD);


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

/*void SCH_Update(void);
void timer1_init(uint16_t timerLoad);
void SCH_Init_T2(void);
*/
#endif /* SCH51_H_ */
