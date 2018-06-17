/*
 * HackIRRemote.c
 *
 * Created: 30/05/2018 12:49:52
 * Author : CDT
 */ 
#include "systick.h"
#include "screens.h"
#include "keyboard.h"
#include "IRlib/IRremote.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "lcdpcf8574.h"



int main(void)
{
	uint16_t  keyboardRef;
	DDRD |= 1<<6;
	initSysTick();
	sei();
	lcd_init(LCD_DISP_ON);
	lcd_led(0);
	
	updatePtr = updateMain;
	
	
	marqueTime16(&keyboardRef);
	while(1)
	{
		if(elapsedTime16(&keyboardRef)>2) // 20ms
		{
			processKeyboard();
			marqueTime16(&keyboardRef);
		}
		if(ChangedScreen)
		{
			updatePtr();
			ChangedScreen=0;
		}
		else
			updatePtr();
		render();
		clearKeys();
	}
	
	
}

ISR(TIMER0_COMPA_vect)
{
	ir_interruptService();
}
ISR(TIMER2_COMPA_vect)
{
	incSysTick();
}

