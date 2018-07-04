/*
 * playMenu.c
 *
 * Created: 17/06/2018 11:58:22
 *  Author: CDT
 */ 
#include "screens.h"

void playCode(decode_results *dec_results);

void updatePlay()
{
	uint8_t playQuery=1;
	decode_results dec_results;
	if(ChangedScreen)
	{
		sprintf(ScreenBuf[0], "Press 0-9 to");
		sprintf(ScreenBuf[1], "send saved code!");
		Refresh=1;
	}
	switch(PressedKeyCode)
	{
		case KEY_0:
			ir_sendNEC(0xC1AA59A6, NEC_BITS);
			//getCode(&dec_results, 0);
			break;
		case KEY_1:
			getCode(&dec_results, 1);
			break;
		case KEY_2:
			getCode(&dec_results, 2);
			break;
		case KEY_3:
			getCode(&dec_results, 3);
			break;
		case KEY_4:
			getCode(&dec_results, 4);
			break;
		case KEY_5:
			getCode(&dec_results, 5);
			break;
		case KEY_6:
			getCode(&dec_results, 6);
			break;
		case KEY_7:
			getCode(&dec_results, 7);
			break;
		case KEY_8:
			getCode(&dec_results, 8);
			break;
		case KEY_9:
			getCode(&dec_results, 9);
			break;
		case KEY_ASTERISK:
			playQuery=0;
			updatePtr=updateMain;
			ChangedScreen=1;
			break;
		default:
			playQuery=0;
			break;
	}
	if(playQuery)
	{
		playCode(&dec_results);
		displayProtocol(&dec_results);
	}
}

void playCode(decode_results *dec_results)
{
	switch(dec_results->decode_type)
	{
		case NEC:
		case NEC_EXT:
			ir_sendNEC(dec_results->value, dec_results->bits);
			break;
		case RC5:
			ir_sendRC5(dec_results->value, dec_results->bits);
		case SONY:
			ir_sendSony(dec_results->value, dec_results->bits);
			break;
		default:
			break;
	}
}