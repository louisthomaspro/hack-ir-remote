/*
 * HackIRRemote.c
 *
 * Created: 30/05/2018 12:49:52
 * Author : CDT
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Pic-IRremote-master/IRremote.h"


int main(void)
{
	DDRB |= 0x80;
	TCCR4A=0;
	TCCR4B= 0b00001100; // /256
	TIMSK4=0b00000010;
	OCR4A=3; // division par 3
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(TIMER4_COMPA_vect)
{
	PORTB ^= 0x80;
}

