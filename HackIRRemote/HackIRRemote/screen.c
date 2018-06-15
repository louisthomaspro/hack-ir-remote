/*
 * screen.c
 *
 * Created: 14/06/2018 17:19:17
 *  Author: CDT
 */ 
#include "screens.h"

void (*updatePtr)(void);
char ScreenBuf[2][17] = {0}; //17 pour '\0' 
uint8_t Refresh = 0;
uint8_t ChangedScreen = 1;
	
uint8_t updateIndex(uint8_t *index, uint8_t maxItem)
{
	switch(PressedKeyCode)
	{
		case KEY_2:
			if(*index == 0)
				*index=maxItem-1;
			else
				(*index)--;
			break;
		case KEY_8:
			if(*index == maxItem-1)
				*index=0;
			else
				(*index)++;
			break;
		default:
			return 0;
			break;
	}
	return 1;
}
	
void render()
{
	if(Refresh)
	{
		lcd_clrscr();
		lcd_home();
		lcd_puts(ScreenBuf[0]);
		lcd_gotoxy(0, 1);
		lcd_puts(ScreenBuf[1]);
		Refresh=0;
	}
}