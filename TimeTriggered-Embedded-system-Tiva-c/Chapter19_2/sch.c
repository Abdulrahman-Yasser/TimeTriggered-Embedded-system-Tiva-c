/*
 * sch.c
 *
 *  Created on: Mar 28, 2021
 *      Author: abduy
 */


#include "sch.h"

// -------- Public Variable definitions ---------------

#define SCH_LED 0x10
static int8_t SCH_led_state_G = 0;

sTask SCH_tasks_G[SCH_MAX_TASKS];

// -------- Private Function definitions ---------------
void HW_sch_init(void);
void HW_sch_update(void);

static void timer1_init(uint16_t timerLoad);

static void SCH_Update(void);

bool SCH_Delete_Task(int8_t TASK_INDEX);

void SCH_Report_Status(void);


// -------- Private Variable definitions ---------------
static int32_t Error_tick_count_G;

static int8_t Last_error_code_G;

void timer1_init(uint16_t timerLoad){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_A);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, timerLoad);
    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 0xff);
    TimerIntRegister(TIMER1_BASE, TIMER_A, SCH_Update);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE, TIMER_A);
}


void SCH_Init_T2(uint32_t timer_value){
    int8_t i;
    HW_sch_init();
    for(i = 0; i < SCH_MAX_TASKS; i++){
        SCH_Delete_Task(i);
    }

    //Reset the global error variable
    Error_code_G = 0;

    //set-up timer with automatic reload
    timer1_init(timer_value);
}

void SCH_Update(void){
    int8_t Index;
    uint32_t q;
    HW_sch_update();

    for(Index = 0; Index < SCH_MAX_TASKS; Index++){
        if(SCH_tasks_G[Index].pTask){
            if(SCH_tasks_G[Index].Delay == 0){
                SCH_tasks_G[Index].RunMe += 1;
                if(SCH_tasks_G[Index].Period > 0){
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            }else{
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
    q = TimerIntStatus(TIMER1_BASE, 1);
    TimerIntClear(TIMER1_BASE, q);
}


int8_t SCH_Add_Task(void (*pFunction)(),
                    int32_t DELAY,
                    int32_t PERIOD){
    int8_t Index = 0;

    while((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
        Index++;
    }

    if(Index == SCH_MAX_TASKS){
//        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return SCH_MAX_TASKS;
    }
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;

    SCH_tasks_G[Index].RunMe = 0;

    return Index;
}



void SCH_Dispatcher_Tasks(void){
    int8_t Index;

    for(Index = 0; Index < SCH_MAX_TASKS; Index++){
        if(SCH_tasks_G[Index].RunMe > 0){

            (*SCH_tasks_G[Index].pTask)();

            SCH_tasks_G[Index].RunMe -= 1;

            if(SCH_tasks_G[Index].Period == 0){
                SCH_Delete_Task(Index);
            }else{
                SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
            }
        }
    }

    //Report system status
    SCH_Report_Status();

/*
    //The scheduler enters idle mode at this point
    SCH_Go_To_Sleep();
*/
}

bool SCH_Delete_Task(int8_t TASK_INDEX){
    bool Return_code;

    if(SCH_tasks_G[TASK_INDEX].pTask == 0){
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;

        Return_code = 0;

    }else{
        Return_code = 1;
    }
    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;

    return Return_code;
}

void HW_sch_update(){
    if(SCH_led_state_G){
        GPIOPinWrite(GPIO_PORTA_BASE, SCH_LED, 0x00);
        SCH_led_state_G = 0;
    }else{
        GPIOPinWrite(GPIO_PORTA_BASE, SCH_LED, 0xff);
        SCH_led_state_G = 1;
    }
}

void HW_sch_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, SCH_LED);
}

void SCH_Report_Status(void){
#ifdef SCH_REPORT_ERRORS
    if(Error_code_G != Last_error_code_G){

        Error_port = 255 - Error_code_G;

        Last_error_code_G = Error_code_G;

        if(Error_code_G != 0){
            Error_tick_count_G = 6000;
        }else{
            Error_tick_count_G = 0;
        }
    }else{
        if(Error_tick_count_G != 0){
            if(--Error_tick_count_G == 0){
                Error_code_G = 0;
            }
        }
    }
#endif
}


/*void SCH_Go_To_Sleep(void){
    //Go to sleep
}*/


