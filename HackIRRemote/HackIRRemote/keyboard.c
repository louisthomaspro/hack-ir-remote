/*
 * keyboard.c
 *
 * Created: 15/06/2018 11:14:23
 *  Author: CDT
 */ 

#include "keyboard.h"

uint8_t PressedKeyCode=KEY_NONE;
uint8_t ReleasedKeyCode=KEY_NONE;

void processKeyboard()
{
	static uint8_t PrevKeyCode = KEY_NONE;
	uint8_t colCode, lineCode, keyCode;
	
	setKeyboardPhase1();
	colCode=readKeyboardPhase1();
	setKeyboardPhase2();
	lineCode=readKeyboardPhase2();
	
	keyCode = colCode | lineCode;
	
	switch(keyCode)
	{
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:
		case KEY_ASTERISK:
		case KEY_0:
		case KEY_HASH:
			if(PrevKeyCode!=keyCode) // detection d'un appui
				PressedKeyCode=keyCode;
			break;
		default:
			keyCode=KEY_NONE;
			if(PrevKeyCode!=keyCode)// detection d'un relachement
				ReleasedKeyCode=PrevKeyCode;
	}
	if(PressedKeyCode==ReleasedKeyCode)// Une touche ne peut être appuyée et relachée en même temps ...
		PressedKeyCode=0;
		
	PrevKeyCode=keyCode;
	
}
void clearKeys()
{
	PressedKeyCode=KEY_NONE;
	ReleasedKeyCode=KEY_NONE;
}

void setKeyboardPhase1()
{
	keyboardPORTx &= ~(1<<X1 | 1<<X2 | 1<<X3); //désactive les sorties des colonnes
	keyboardDDRx &= ~(1<<X1 | 1<<X2 | 1<<X3); //bascule les colonnes en entrées
	keyboardDDRx |= (1<<Y1 | 1<<Y2 | 1<<Y3 | 1<<Y4); //bascule les lignes en sorties
	keyboardPORTx |= (1<<Y1 | 1<<Y2 | 1<<Y3 | 1<<Y4); //active les sorties des lignes
}
void setKeyboardPhase2()
{
	keyboardPORTx &= ~(1<<Y1 | 1<<Y2 | 1<<Y3 | 1<<Y4); //désactive les sorties des lignes
	keyboardDDRx &= ~(1<<Y1 | 1<<Y2 | 1<<Y3 | 1<<Y4); //bascule les lignes en entrées
	keyboardDDRx |= (1<<X1 | 1<<X2 | 1<<X3); //bascule les colonnes en sorties
	keyboardPORTx |= (1<<X1 | 1<<X2 | 1<<X3); //active les sorties des colonnes
}
uint8_t readKeyboardPhase1()
{
	return keyboardPINx & (1<<X1 | 1<<X2 | 1<<X3);
}
uint8_t readKeyboardPhase2()
{
	return keyboardPINx & (1<<Y1 | 1<<Y2 | 1<<Y3 | 1<<Y4);
}