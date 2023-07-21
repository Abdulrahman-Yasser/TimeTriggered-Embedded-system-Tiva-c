/*
 * Timeout.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdu
 */

#ifndef SYSTEMLAYERS_RTOS_TIMEOUT_TIMEOUT_H_
#define SYSTEMLAYERS_RTOS_TIMEOUT_TIMEOUT_H_

#include "../General_Mcal/GPT/Static/inc/GPT_Types.h"

#define TIMEOUT_USED_TIMER  Gpt_Channel_Normal_1

#define TIMEOUT_DID_HAPPENED        1
#define TIMEOUT_DID_NOT_HAPPENED    0

inline uint8 TimeoutStatus(void);
inline void TimeoutOccurs(void);
inline void TimeoutRefresh(void);

inline void TimeoutStop(void);
inline void TimeoutStart(uint16 my_value);
void TimeoutInit(void);
void TimeoutSetCallbackFunction(void (*pTimeoutFun)(void));

#endif /* SYSTEMLAYERS_RTOS_TIMEOUT_TIMEOUT_H_ */
