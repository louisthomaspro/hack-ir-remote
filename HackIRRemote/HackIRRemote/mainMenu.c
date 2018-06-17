/*
 * mainMenu.c
 *
 * Created: 14/06/2018 15:57:19
 *  Author: CDT
 */

#include "screens.h"

#define NB_ITEM_MAINMENU 3


void updateMain()
{
	static uint8_t index=0;
	
	char *playStr = "Play";
	char *spyRecStr = "Spy & Record";
	char *customStr = "Custom";
	
	Refresh|=updateIndex(&index, NB_ITEM_MAINMENU);
	
	if(ChangedScreen)
		Refresh=1;
		
	switch(index)
	{
		case 0:
			ScreenBuf[0][0] = '>';
			strcpy(ScreenBuf[0]+1, playStr);
			
			ScreenBuf[1][0] = ' ';
			strcpy(ScreenBuf[1]+1, spyRecStr);
			break;
		case 1:
			ScreenBuf[0][0] = ' ';
			strcpy(ScreenBuf[0]+1, playStr);
			
			ScreenBuf[1][0] = '>';
			strcpy(ScreenBuf[1]+1, spyRecStr);
			break;
		case 2:
			ScreenBuf[0][0] = '>';
			strcpy(ScreenBuf[0]+1, customStr);
			
			ScreenBuf[1][0]='\0';
			break;
		default:
			break;
	}
	
	if(PressedKeyCode==KEY_5)
	{
		switch(index)
		{
			case 0:
				updatePtr=updatePlay;
				break;
			case 1:
				updatePtr=updateSpyRec;
				break;
			default:
				break;
		}
		ChangedScreen=1;
	}
				
}
 
