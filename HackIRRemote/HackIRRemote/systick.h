/*
 * systick.h
 *
 * Created: 14/06/2018 14:35:40
 *  Author: CDT
 */ 


#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "timer.h"

extern volatile uint16_t SysTick;

void initSysTick();
void incSysTick();
void marqueTime16(uint16_t *ref);
uint16_t elapsedTime16(uint16_t *ref);



#endif /* SYSTICK_H_ */