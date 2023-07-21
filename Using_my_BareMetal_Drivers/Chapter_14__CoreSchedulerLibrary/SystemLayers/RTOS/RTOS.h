/*
 * RTOS.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef RTOS_RTOS_H_
#define RTOS_RTOS_H_

#include "../General_Common/Std_Types.h"
#include "../General_Mcal/GPT/Static/inc/GPT_Types.h"
#define INTERRUPT_Timer_0_Overflow 1
#define RTOS_Used_Timer_Channel Gpt_Channel_Normal_0

#define SCH_REPORT_ERRORS 0

typedef struct{
    void(*pTask)(void);
    uint32 Delay;
    uint32 Period;
    uint8 RunMe;
}sTask;

// ------ Public function prototypes -------------------------------

// Core scheduler functions

void SCH_Update(void);
void SCH_Start();


void SCH_Init_T0(void);
void SCH_Dispatch_Tasks(void);
uint8 SCH_Add_Task(void (*pFunction)(void), const uint32 DELAY, const uint32 PERIOD);
uint8 SCH_Delete_Task(const uint8 TASK_INDEX);
void SCH_Report_Status(void);

// ------ Public constants -----------------------------------------

// The maximum number of tasks required at any one time
// during the execution of the program
//
// MUST BE ADJUSTED FOR EACH NEW PROJECT

#define SCH_MAX_TASKS (5)

#endif /* RTOS_RTOS_H_ */
