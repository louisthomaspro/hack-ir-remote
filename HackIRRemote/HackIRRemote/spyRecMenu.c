/*
 * spyRecMenu.c
 *
 * Created: 15/06/2018 16:54:22
 *  Author: CDT
 */ 

#include "screens.h"

void spy();
void detectNEC_ext(decode_results *dec_results);



void updateSpyRec()
{	
	if(ChangedScreen)
	{
		ir_enableIRIn();
		sprintf(ScreenBuf[0], "Spying... Press");
		sprintf(ScreenBuf[1], "0-9 to save !");
		Refresh=1;
	}
		
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
	static decode_results dec_results_save;
	static uint16_t ref1=0;
	static uint8_t resume=0;
	uint8_t saved = 0;
	uint8_t found=ir_decode(&dec_results);
	
	
	if (found&&!resume) 
	{
		dec_results_save.decode_type = dec_results.decode_type;
		dec_results_save.bits = dec_results.bits;
		dec_results_save.value = dec_results.value;
		dec_results_save.panasonicAddress = dec_results.panasonicAddress;
		
		if(dec_results_save.decode_type==NEC)
			detectNEC_ext(&dec_results_save);
		
		displayProtocol(&dec_results_save);
		marqueTime16(&ref1);
		resume=1;		   
	}
	if (elapsedTime16(&ref1)>20 && resume) // wait 200ms before listening again
	{
		 ir_resume(); // Receive the next value
		 resume=0;
	}
	if(dec_results_save.decode_type != 0 && dec_results_save.decode_type != UNKNOWN)
	{	
		if(ChangedScreen)
			displayProtocol(&dec_results_save);
		saved=1;
		switch(PressedKeyCode)
		{
			case KEY_0:
				saveCode(&dec_results_save, 0);
				break;
			case KEY_1:
				saveCode(&dec_results_save, 1);
				break;
			case KEY_2:
				saveCode(&dec_results_save, 2);
				break;
			case KEY_3:
				saveCode(&dec_results_save, 3);
				break;
			case KEY_4:
				saveCode(&dec_results_save, 4);
				break;
			case KEY_5:
				saveCode(&dec_results_save, 5);
				break;
			case KEY_6:
				saveCode(&dec_results_save, 6);
				break;
			case KEY_7:
				saveCode(&dec_results_save, 7);
				break;
			case KEY_8:
				saveCode(&dec_results_save, 8);
				break;
			case KEY_9:
				saveCode(&dec_results_save, 9);
				break;
			default:
				saved=0;
				break;
		}
		if(saved)
		{
			updatePtr=updateSaved;
			ChangedScreen=1;
		}
		
	}
		
}
void detectNEC_ext(decode_results *dec_results)
{
	if((uint8_t)((dec_results->value&0xFF000000)>>24) != (uint8_t)~(((dec_results->value)&0xFF0000)>>16))
		dec_results->decode_type=NEC_EXT;
}