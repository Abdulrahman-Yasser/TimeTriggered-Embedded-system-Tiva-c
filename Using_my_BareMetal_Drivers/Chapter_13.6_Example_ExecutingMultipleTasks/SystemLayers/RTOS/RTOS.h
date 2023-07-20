/*
 * RTOS.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdu
 */

#ifndef RTOS_RTOS_H_
#define RTOS_RTOS_H_


#define INTERRUPT_Timer_0_Overflow 10
#define INTERRUPT_Timer_1_Overflow 30
#define INTERRUPT_Timer_2_Overflow 50

void Timers_Init(void);
void Timer_0A_Init(void);
void Timer_1A_Init(void);
void Timer_2A_Init(void);
void EnableInterrupt();


#endif /* RTOS_RTOS_H_ */
