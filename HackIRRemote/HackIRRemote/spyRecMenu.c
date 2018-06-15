/*
 * spyRecMenu.c
 *
 * Created: 15/06/2018 16:54:22
 *  Author: CDT
 */ 

#include "screens.h"
#include "IRremote.h"

void spy();

void updateSpyRec()
{
	char *l1Str = "Spying... Press";
	char *l2Str = "0-9 to save !";
	strcpy(ScreenBuf[0], l1Str);
	strcpy(ScreenBuf[1], l2Str);
	
	if(ChangedScreen)
		ir_enableIRIn();
	spy();
	
	if(PressedKeyCode==KEY_ASTERISK)
	{
		updatePtr=updateMain;
		ChangedScreen=1;
	}
}
void spy()
{
	decode_results dec_results;
	
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
}