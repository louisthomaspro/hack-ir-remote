/*
 * global.h
 *
 * Created: 14/06/2018 14:46:35
 *  Author: CDT
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define TIMER0_SYSTICK 0
#define TIMER0_RECV 1

extern volatile uint8_t Timer0Mode;

#endif /* TIMER_H_ */