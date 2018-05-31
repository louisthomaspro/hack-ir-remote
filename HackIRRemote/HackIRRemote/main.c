/*
 * HackIRRemote.c
 *
 * Created: 30/05/2018 12:49:52
 * Author : CDT
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Pic-IRremote-master/IRremote.h"


int main(void)
{
	DDRB |= 0x80;
    /* Replace with your application code */
    while (1) 
    {
		PORTB |= 0x80;
		_delay_ms(1000);
		PORTB &= 0X7F;
		_delay_ms(1000);
    }
}

