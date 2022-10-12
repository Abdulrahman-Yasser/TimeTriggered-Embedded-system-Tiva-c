

/**
 * main.c
 */

#include "main.h"
#include "led_flash.h"


int main(void)
{
    SCH_Init_T2();

    LED_Flash_Init();

    SWT_Flash_Init();

    SCH_Add_Task(LED_Flash_update, 0, 1000);

    SCH_Add_Task(SWT_Flash_Update, 0, 1000);

    SCH_Start();

    while(1){
        SCH_Dispatcher_Task();
    }
}
