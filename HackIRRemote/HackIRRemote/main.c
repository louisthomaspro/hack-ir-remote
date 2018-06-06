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
#include "IRlib/IRremote.h"


int main(void)
{
	DDRB |= 0x10;
	 /*timer 4A for ir-receiving*/
	 /*TCCR0A=0;
	 TCCR0B= 0b00001100; // /256
	 TIMSK0=0b00000010;
	 OCR0A=3; // division par 3
	//sei();*/
	decode_results dec_results;
    ir_enableIRIn();
    ir_blink13(0);
    while(1)
    {
		/*uint8_t irdata = (PINB & (1<<4))>>4;
		if(irdata)
		{
			PORTB |= 0x10;
		}
		else
		{
			PORTB &= 0xEF;
		}*/
	    if (ir_decode(&dec_results)) {
		    if (dec_results.decode_type == NEC)
		    {
			   PORTB ^= 0x10;
		    }
		    //do something here
		    ir_resume(); // Receive the next value
	    }
    }

}

ISR(TIMER0_COMPA_vect)
{
	ir_interruptService();
}

