/*
 * hSCH.c
 *
 *  Created on: Mar 28, 2021
 *      Author: abduy
 */


#include "hSCH.h"

// -------- Public Variable definitions ---------------

int8_t Error_code_G = 0;

sTask hSCH_tasks_G[hSCH_MAX_TASKS];

// -------- Private Function definitions ---------------

static void timer1_init(uint16_t timerLoad);

static void hSCH_Update(void);

bool hSCH_Delete_Task(int8_t TASK_INDEX);

void hSCH_Report_Status(void);

void HW_sch_init(void);

void HW_SCH_update(void);
// -------- Private Variable definitions ---------------
static int32_t Error_tick_count_G;

static int8_t Last_error_code_G;

#define SCH_LED 4

#define SCH_LED_ON GPIOPinWrite(GPIO_PORTA_BASE, SCH_LED, 0xff);

#define SCH_LED_OFF GPIOPinWrite(GPIO_PORTA_BASE, SCH_LED, 0x00);

void timer1_init(uint16_t timerLoad){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_A);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC_UP);
    TimerLoadSet(TIMER1_BASE, TIMER_A, timerLoad);
    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 0xff);
    TimerIntRegister(TIMER1_BASE, TIMER_A, hSCH_Update);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE, TIMER_A);
}

void HW_sch_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, SCH_LED);
}

void HW_SCH_update(void){
    int8_t t;
    t = GPIOPinRead(GPIO_PORTA_BASE, SCH_LED);
    GPIOPinWrite(GPIO_PORTA_BASE, SCH_LED, ~t);
}

void hSCH_Init_T2(uint32_t timer_value){
    int8_t i;
    HW_sch_init();
    for(i = 0; i < hSCH_MAX_TASKS; i++){
        hSCH_Delete_Task(i);
    }

    //Reset the global error variable
    Error_code_G = 0;

    //set-up timer with automatic reload
    timer1_init(timer_value);
}

void hSCH_Update(void){
    HW_SCH_update();
    int8_t Index;
    uint32_t q;
    q = TimerIntStatus(TIMER1_BASE, 1);
    TimerIntClear(TIMER1_BASE, q);

    for(Index = 0; Index < hSCH_MAX_TASKS; Index++){
        if(hSCH_tasks_G[Index].pTask){
            if(hSCH_tasks_G[Index].Delay == 0){
                if(!hSCH_tasks_G[Index].CO_OP){
                    (*hSCH_tasks_G[Index].pTask)();
                    hSCH_tasks_G[Index].RunMe += 1;
                    if(hSCH_tasks_G[Index].Period == 0){
                        hSCH_tasks_G[Index].pTask = 0;
                    }
                }else{
                    hSCH_tasks_G[Index].RunMe += 1;
                }
                if(hSCH_tasks_G[Index].Period){
                    hSCH_tasks_G[Index].Delay = hSCH_tasks_G[Index].Period;
                }
            }else{
                hSCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}


int8_t hSCH_Add_Task(void (*pFunction)(),
                    int32_t DELAY,
                    int32_t PERIOD,
                    int8_t co_op){
    int8_t Index = 0;

    while((hSCH_tasks_G[Index].pTask != 0) && (Index < hSCH_MAX_TASKS)){
        Index++;
    }

    if(Index == hSCH_MAX_TASKS){
//        Error_code_G = ERROR_hSCH_TOO_MANY_TASKS;
        return hSCH_MAX_TASKS;
    }
    hSCH_tasks_G[Index].pTask = pFunction;
    hSCH_tasks_G[Index].Delay = DELAY;
    hSCH_tasks_G[Index].Period = PERIOD;

    hSCH_tasks_G[Index].RunMe = 0;

    hSCH_tasks_G[Index].CO_OP = co_op;

    return Index;
}



void hSCH_Dispatcher_Tasks(void){
    int8_t Index;

    for(Index = 0; Index < hSCH_MAX_TASKS; Index++){
        if(hSCH_tasks_G[Index].RunMe > 0 && hSCH_tasks_G[Index].CO_OP){

            (*hSCH_tasks_G[Index].pTask)();

            hSCH_tasks_G[Index].RunMe -= 1;

            if(hSCH_tasks_G[Index].Period == 0){
                hSCH_Delete_Task(Index);
            }
        }
    }

    //Report system status
    hSCH_Report_Status();

/*
    //The hSCHeduler enters idle mode at this point
    hSCH_Go_To_Sleep();
*/
}

bool hSCH_Delete_Task(int8_t TASK_INDEX){
    bool Return_code;

    if(hSCH_tasks_G[TASK_INDEX].pTask == 0){
        Error_code_G = ERROR_hSCH_CANNOT_DELETE_TASK;

        Return_code = 0;

    }else{
        Return_code = 1;
    }
    hSCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    hSCH_tasks_G[TASK_INDEX].Delay = 0;
    hSCH_tasks_G[TASK_INDEX].Period = 0;
    hSCH_tasks_G[TASK_INDEX].RunMe = 0;

    return Return_code;
}


void hSCH_Report_Status(void){
#ifdef hSCH_REPORT_ERRORS
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


/*void hSCH_Go_To_Sleep(void){
    //Go to sleep
}*/


