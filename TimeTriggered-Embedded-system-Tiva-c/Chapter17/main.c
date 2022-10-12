

/**
 * main.c
 */

#include "main.h"


int main(void)
{
    hSCH_Init_T2(0xefff);
    LED_Init();

    /*Pre-emptive task that runs with the hSCH_Update ... every system tick
    with Delay 2-Sys_tick
    periodic task
    */
    hSCH_Add_Task(LED_Short_Update, 2, 1, 0);

    /*Co-operative task that runs with the Dispatcher by incrementing the run in hSCH_Update
    with Delay 20-Sys_tick
    periodic task
    */
    hSCH_Add_Task(LED_Long_Update, 20, 1, 1);

    while(1){
        hSCH_Dispatcher_Tasks();
    }
}
