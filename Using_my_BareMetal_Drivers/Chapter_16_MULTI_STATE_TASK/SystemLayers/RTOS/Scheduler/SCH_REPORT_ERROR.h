/*
 * SCH_REPORT_ERROR.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdu
 */

#ifndef SCH_REPORT_ERROR_H
#define SCH_REPORT_ERROR_H

#include "Common/Std_Types.h"

#define ERROR_SCH_TOO_MANY_TASKS                        1
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK              2
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 3
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START      4
#define ERROR_SCH_LOST_SLAVE                            5
#define ERROR_SCH_CAN_BUS_ERROR                         6
#define ERROR_I2C_WRITE_BYTE_AT24C64                    7
#define ERROR_SCH_CANNOT_DELETE_TASK                    8


#endif /* SYSTEMLAYERS_RTOS_SCH_REPORT_ERROR_H_ */
