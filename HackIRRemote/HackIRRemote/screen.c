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
void displayProtocol(decode_results *dec_results)
{
	char *typeStr = "Type:";
	char *addrStr = "Addr:";
	char *cmdStr = "Cmd:";
	
	strcpy(ScreenBuf[0], typeStr);
	
	switch(dec_results->decode_type)
	{
		case NEC:
			strcpy(ScreenBuf[0]+strlen(typeStr), "NEC");
			if(dec_results->value!=REPEAT)
				sprintf(ScreenBuf[1], "%sx%02X %sx%02X", addrStr, (uint8_t)((dec_results->value&0xFF000000)>>24), cmdStr, (uint8_t)((dec_results->value&0xFF00)>>8));
			else
				sprintf(ScreenBuf[1], "Repeat code");
			break;
		case RC5:
			strcpy(ScreenBuf[0]+strlen(typeStr), "RC5");
			sprintf(ScreenBuf[1], "%sx%02X %sx%02X", addrStr, (uint8_t)((dec_results->value&0x7C0)>>6), cmdStr, (uint8_t)(dec_results->value&0x3F));
			break;
		case SONY:
			strcpy(ScreenBuf[0]+strlen(typeStr), "SONY");
			if(dec_results->bits == 12)
				sprintf(ScreenBuf[1], "%sx%02X %sx%02X", addrStr, (uint8_t)(dec_results->value&0x1F), cmdStr, (uint8_t)((dec_results->value&0xFE0)>>5));
			else if(dec_results->bits == 15)
				sprintf(ScreenBuf[1], "%sx%02X %sx%02X", addrStr, (uint8_t)(dec_results->value&0xFF), cmdStr, (uint8_t)((dec_results->value&0x7F00)>>8));
			else if(dec_results->bits == 20)
			{
				sprintf(ScreenBuf[0], "%s Ex:x%02X", ScreenBuf[0], (uint8_t)(dec_results->value&0xFF));
				sprintf(ScreenBuf[1], "%sx%02X %sx%02X", addrStr, (uint8_t)((dec_results->value&0x1F00)>>8), cmdStr, (uint8_t)((dec_results->value&0xFE000)>>13));
			}
			break;
		default:
			strcpy(ScreenBuf[0]+strlen(typeStr), "UNKNOWN");
			ScreenBuf[1][0]='\0';
		break;
	}
	Refresh=1;
}