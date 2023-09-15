/*
 * Timeout.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdu
 */

#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "Timeout.h"

static void TimeoutISR(void);


static uint8 timeoutFlag = TIMEOUT_DID_NOT_HAPPENED;

inline uint8 TimeoutStatus(void){
    return timeoutFlag;
}

inline void TimeoutOccurs(void){
    timeoutFlag  = TIMEOUT_DID_HAPPENED;
}

inline void TimeoutRefresh(void){
    Gpt_StopTimer(TIMEOUT_USED_TIMER);
    timeoutFlag = TIMEOUT_DID_NOT_HAPPENED;
}


inline void TimeoutStop(void){
    Gpt_StopTimer(TIMEOUT_USED_TIMER);
}

inline void TimeoutStart(uint16 my_value){
    Gpt_StartTimer(TIMEOUT_USED_TIMER, my_value);
    timeoutFlag = TIMEOUT_DID_NOT_HAPPENED;
}


void TimeoutInit(void){
    Gpt_EnableNotification(TIMEOUT_USED_TIMER);
    TimeoutSetCallbackFunction(TimeoutISR);
}

void TimeoutSetCallbackFunction(void (*pTimeoutFun)(void)){
    Gpt_SetCallBackFunction(TIMEOUT_USED_TIMER, pTimeoutFun, Gpt_InterruptOverFlow);
}

static void TimeoutISR(void){
    TimeoutStop();
    TimeoutOccurs();
}

