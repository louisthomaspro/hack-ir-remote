/*
 * HackIRRemote.c
 *
 * Created: 30/05/2018 12:49:52
 * Author : CDT
 */ 
#include "IRlib/IRremote.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "lcdpcf8574.h"



#define y1 PD0
#define y2 PD1
#define y3 PD2
#define y4 PD3

#define x1 PD4
#define x2 PD5
#define x3 PD6

//char keypad[4][3]={1,2,3,4,5,6,7,8,9,'*','0','#'};


int main(void)
{
	//DDRB |= 1<<3;
	DDRD |= 1<<6;
	 /*timer 4A for ir-receiving*/
	 /*TCCR0A=0;
	 TCCR0B= 0b00001100; // /256
	 TIMSK0=0b00000010;
	 OCR0A=3; // division par 3
	//sei();*/
	//decode_results dec_results;
    //ir_enableIRIn();
    //ir_blink13(0);
	
	//OCR2B = pwmval / 3;
	//TIMSK2=0x02;
	
	//ir_sendNEC(0x00FF20DF, 32);
	
	/*while (1)
	{
		ir_sendNEC(0x00FF20DF, 32);
	}*/
	
	
	
	//init lcd
	lcd_init(LCD_DISP_ON_BLINK);
	//lcd go home
	lcd_home();
	uint8_t led = 0;
	lcd_led(led); //set led
	
	
    while(1)
    {
		
		//lcd_led(led); //set led
		//led = !led; //invert led for next loop

		//test loop
		int i = 0;
		int line = 0;
		for(i=0; i<10; i++) {
			char buf[10];
			itoa(i, buf, 10);
			lcd_gotoxy(1, line);
			lcd_puts("i= ");
			itoa(i, buf, 10);
			lcd_gotoxy(4, line);
			lcd_puts(buf);
			line++;
			line %= 2;
			//uart_puts(buf);
			//uart_puts("\r\n");
			//_delay_ms(100);
		}
		
		/*uint8_t irdata = (PINB & (1<<4))>>4;
		if(irdata)
		{
			PORTB |= 0x10;
		}
		else
		{
			PORTB &= 0xEF;
		}*/
	    /*if (ir_decode(&dec_results)) {
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
	    }*/
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

/*ISR(TIMER2_COMPA_vect)
{
 PORTB ^= 0x21;
}*/

