

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "main.h"

#define LOCKED 1
#define UNLOCKED 0

bool Lock;

int main(void)
{
    SCH_Init_T2();

    LED_Flash_Init();

    //Function A will run every 2 ms
    SCH_Add_Task(LED_Flash_Update, 0, 2);


    while(1){
        SCH_Dispatcher_Tasks();
    }
}
