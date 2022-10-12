

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "main.h"

int main(void)
{
    gpio_a();
    IntMasterEnable();
    timer0_init();
    timer1_init();
    x();
    y();
    while(1){
        GPIOPinWrite(GPIO_PORTA_BASE, 0x10, 0xff);
        delay(15);
        GPIOPinWrite(GPIO_PORTA_BASE, 0x10, 0x00);
        delay(15);
    }
}
