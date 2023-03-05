/*
* uart.c
*
*  Created on: Apr 22, 2021
*      Author: abduy
*/

#include <my_uart.h>

void uart1_pin_init(void);




void uart1_isr_init(uint16_t baud_rate, void (*pfun)(void)){
    uint32_t q;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    UARTDisable(UART1_BASE);
    q = SysCtlClockGet();
    UARTConfigSetExpClk(UART1_BASE, q, baud_rate, UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE | UART_CONFIG_WLEN_8);
    UARTTxIntModeSet(UART1_BASE, UART_TXINT_MODE_FIFO);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX6_8, UART_FIFO_RX6_8);
    UARTFIFOEnable(UART1_BASE);
    HWREG(UART1_BASE + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |UART_CTL_RXE);
    IntMasterEnable();
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_IM_RXIM | UART_IM_TXIM);
    UARTIntRegister(UART1_BASE, pfun);
    uart1_pin_init();
}

void uart1_init(uint16_t baud_rate){
    uart_delay_init(0xff);
    uint32_t q;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    UARTDisable(UART1_BASE);
    q = SysCtlClockGet();
    UARTConfigSetExpClk(UART1_BASE, q, baud_rate, UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE | UART_CONFIG_WLEN_8);
    UARTTxIntModeSet(UART1_BASE, UART_TXINT_MODE_FIFO);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX6_8, UART_FIFO_RX6_8);
    UARTFIFOEnable(UART1_BASE);
    HWREG(UART1_BASE + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE );
    uart1_pin_init();
}

void uart1_pin_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//    GPIOPinTypeUART(GPIO_PORTB_BASE, 0x01);
    GPIOPinTypeUART(GPIO_PORTB_BASE, 0x02);
//    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
}


bool uart_ts_check(){
    int q;
    q = HWREG(UART1_BASE + UART_O_FR);
    if(q & UART_FR_TXFF){
        return 1;
    }
    return 0;
}

void uart_delay_init(uint16_t timerPresc){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerDisable(TIMER2_BASE, TIMER_A);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT);
    TimerPrescaleSet(TIMER2_BASE, TIMER_A, timerPresc);
}


void uart_delay_start(int timerLoad){
    TimerLoadSet(TIMER2_BASE, TIMER_A, timerLoad);
    TimerEnable(TIMER2_BASE, TIMER_A);
    while(!((TimerIntStatus(TIMER2_BASE, 0)) & TIMER_RIS_TATORIS));
    TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
}

void uart_delay_fStart(int timerLoad){
    TimerLoadSet(TIMER2_BASE, TIMER_A, timerLoad);
    TimerEnable(TIMER2_BASE, TIMER_A);
}

void uart_delay_stop(void){
    TimerDisable(TIMER2_BASE, TIMER_A);
}

bool uart_delay_fCheck(void){
    int q = TimerIntStatus(TIMER2_BASE, 0);
    if(q & TIMER_RIS_TATORIS){
        TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
        return 0;
    }
    return 1;
}
