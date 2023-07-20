/*
 * my_program.c
 *
 *  Created on: Apr 21, 2021
 *      Author: abduy
 */
#include "my_program.h"
#include "uart_soft.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"

#define PROG_LED 0x04
static int8_t PROG_led_state_G = 0;

void HW_prog_init(void);
void HW_prog_update(void);

int Hou_G = 0;
int Min_G = 0;
int Sec_G = 0;

void Elapsed_time_Init(){
    HW_prog_init();
    char Time_str[] = "Elapsed time";
    pc_link_write_string_to_buffer(Time_str);
}

void Elapsed_time_update(){
    HW_prog_update();
    char Time_str[30] = "/nElapsed time: ";
    if(++Sec_G == 60){
        Sec_G = 0;
        if(++Min_G == 60){
            Min_G = 0;
            if(++Hou_G == 24){
                Hou_G = 0;
            }
        }
    }
    Time_str[15] = CHAR_MAP_G[Hou_G / 10];
    Time_str[16] = CHAR_MAP_G[Hou_G % 10];

    Time_str[18] = CHAR_MAP_G[Min_G / 10];
    Time_str[19] = CHAR_MAP_G[Min_G % 10];

    Time_str[21] = CHAR_MAP_G[Sec_G / 10];
    Time_str[22] = CHAR_MAP_G[Sec_G % 10];

    if((Sec_G % 2) == 0){
        Time_str[17] = ':';
        Time_str[20] = ':';
    }else{
        Time_str[17] = ' ';
        Time_str[20] = ' ';
    }
    pc_link_write_string_to_buffer(Time_str);
}


void HW_prog_update(){
    if(PROG_led_state_G){
        GPIOPinWrite(GPIO_PORTA_BASE, PROG_LED, 0x00);
        PROG_led_state_G = 0;
    }else{
        GPIOPinWrite(GPIO_PORTA_BASE, PROG_LED, 0xff);
        PROG_led_state_G = 1;
    }
}

void HW_prog_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, PROG_LED);
}
