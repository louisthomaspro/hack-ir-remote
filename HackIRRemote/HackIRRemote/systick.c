/*
 * systick.c
 *
 * Created: 14/06/2018 14:39:33
 *  Author: CDT
 */ 

#include "systick.h"

volatile uint16_t SysTick = 0;

void initSysTick()
{
	OCR2A=78; // division par 78
	TCCR2A=0b00000010;
	TCCR2B=0b00000111; // /1024
	TIMSK2=0b00000010;
	// Génère une interruption toutes les 9.98 ms
}
void incSysTick()
{
	SysTick++;
}
void marqueTime16(uint16_t *ref)
{
	*ref=SysTick;
}
uint16_t elapsedTime16(uint16_t *ref)
{
	if(SysTick<*ref)
		return (65535UL-(SysTick-*ref))+1;
	else
		return (SysTick-*ref);
	
}