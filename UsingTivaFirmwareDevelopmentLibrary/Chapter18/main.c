
/**
 * main.c
 */
#include "main.h"

int main(void)
{
    SCH_Init_T2(0x3f);

    pc_link_Init(9600);

    Elapsed_time_Init();

    SCH_Add_Task(Elapsed_time_update, 1000, 1000);
    SCH_Add_Task(pc_link_update, 10, 10);

    while(1){
        SCH_Dispatcher_Tasks();
    }
}
