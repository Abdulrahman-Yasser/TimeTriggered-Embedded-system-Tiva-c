#include "uart_soft.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

#define PC_LED 0x08
static int8_t PC_led_state_G = 0;

static int out_written_index_G;
static int out_waiting_index_G;


static char tran_buffer[PC_LINK_TRAN_BUFFER_LENGTH];


void HW_pc_init(void);
void HW_pc_update(void);

void pc_link_Init(uint32_t baudrate){
    uart1_init(baudrate);
    out_waiting_index_G = 0;
    out_written_index_G = 0;
    HW_pc_init();
}

void pc_link_update(void){
    HW_pc_update();
    if(out_written_index_G < out_waiting_index_G){
        pc_link_send_char(tran_buffer[out_written_index_G]);
        out_written_index_G++;
    }else{
        out_waiting_index_G = 0;
        out_written_index_G = 0;
    }
}

void pc_link_send_char(char ch){
    int q;
    if(ch == '\n'){
        //1ms = 62.282
        //delay 500ms
        uart_delay_fStart(31144);
        q = uart_delay_fCheck();
        while( q && uart_ts_check()){
            q = uart_delay_fCheck();
        }
        if(q == 0){
            Error_code_G = ERROR_USART_TI;
            return ;
        }
        uart_delay_stop();
        UARTCharPut(UART1_BASE, 0x0d);
    }else{
        uart_delay_fStart(31144);
        q = uart_delay_fCheck();
        while( q && uart_ts_check()){
            q = uart_delay_fCheck();
        }
        if(q == 0){
            Error_code_G = ERROR_USART_TI;
            return;
        }
        uart_delay_stop();
        UARTCharPut(UART1_BASE, ch);
    }
}

void pc_link_write_char_to_buffer(char ch){
    if(out_waiting_index_G < PC_LINK_TRAN_BUFFER_LENGTH){
        tran_buffer[out_waiting_index_G] = ch;
        out_waiting_index_G++;
    }else{
        Error_code_G = ERROR_USART_WRITE_CHAR;
    }
}



void pc_link_write_string_to_buffer(char* str_ptr){
    int i = 0;
    while(str_ptr[i] != '\0'){
        pc_link_write_char_to_buffer(str_ptr[i]);
        i++;
    }
}

void HW_pc_update(){
    if(PC_led_state_G){
        GPIOPinWrite(GPIO_PORTA_BASE, PC_LED, 0x00);
        PC_led_state_G = 0;
    }else{
        GPIOPinWrite(GPIO_PORTA_BASE, PC_LED, 0xff);
        PC_led_state_G = 1;
    }
}

void HW_pc_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIODigitalOutMine(GPIO_PORTA_BASE, PC_LED);
}
