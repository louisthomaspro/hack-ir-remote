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
	DDRB |= 0x21;
	DDRD |=0x08;
	 /*timer 4A for ir-receiving*/
	 /*TCCR0A=0;
	 TCCR0B= 0b00001100; // /256
	 TIMSK0=0b00000010;
	 OCR0A=3; // division par 3
	//sei();*/
	decode_results dec_results;
    ir_enableIRIn();
    ir_blink13(0);
	
	const uint8_t pwmval = (16000000UL / 2000UL / (38));
	TCCR2A = 0x01;
	TCCR2B = 0x09;
	OCR2A = pwmval;
	OCR2B = pwmval / 3;
	TIMSK2=0x02;
	
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
		    switch(dec_results.decode_type)
			{
				case NEC:
				PORTB |= 0x01;
				break;
				case RC5:
				PORTB |= 0x01;
				break;
				case SONY:
				PORTB |= 0x01;
				break;
				default:
				PORTB |= 0x01;
				break;
			}
		    //do something here
		    ir_resume(); // Receive the next value
	    }
		/*PORTB &= 0xFE;
		_delay_ms(1000);
		PORTB |= 0x01;
		_delay_ms(1000);*/
	}

}

ISR(TIMER0_COMPA_vect)
{
	ir_interruptService();
}

ISR(TIMER2_COMPA_vect)
{
 PORTB ^= 0x21;
}

