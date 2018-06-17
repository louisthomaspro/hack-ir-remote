/*
 * savedMenu.c
 *
 * Created: 17/06/2018 11:04:47
 *  Author: CDT
 */ 
#include "screens.h"

void updateSaved()
{
	static uint16_t ref1=0;
	if(ChangedScreen)
	{
		sprintf(ScreenBuf[0], "    Saved !     ");
		ScreenBuf[1][0]='\0';
		Refresh=1;
		marqueTime16(&ref1);
	}
	if(elapsedTime16(&ref1)>100)
	{
		updatePtr=updateSpyRec;
		ChangedScreen=1;
	}
}