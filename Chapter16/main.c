

/**
 * main.c
 */

#include "main.h"


int main(void)
{
    SCH_Init_T2(SYS_TICK);
    TRAFFIC_LIGHT_Init(0);

    SCH_Add_Task(TRAFFIC_LIGHT_Update, 0, 1);
    while(1){
        SCH_Dispatcher_Tasks();
    }
}
