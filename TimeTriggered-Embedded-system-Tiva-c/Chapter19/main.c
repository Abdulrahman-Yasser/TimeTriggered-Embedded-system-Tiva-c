

/**
 * main.c
 */

#include "main.h"

int main(void)
{
    switch_init();
    LED_flash_init();

    SCH_Init_T2(0x3f);

    SCH_Add_Task(LED_flash_update, 1, 1000);

    SCH_Add_Task(switch_update, 0, 200);

    while(1){
        SCH_Dispatcher_Tasks();
    }

	return 0;
}
