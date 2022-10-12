/*
 * uart_soft.h
 *
 *  Created on: Apr 21, 2021
 *      Author: abduy
 */

#ifndef UART_SOFT_H_
#define UART_SOFT_H_

#include "my_uart.h"
#include "sch.h"

#define PC_LINK_TRAN_BUFFER_LENGTH 100

void pc_link_Init(uint32_t baudrate);

void pc_link_write_char_to_buffer(char ch);

void pc_link_write_string_to_buffer(char* str_ptr);

void pc_link_update(void);

void pc_link_send_char(char ch);


#endif /* UART_SOFT_H_ */
