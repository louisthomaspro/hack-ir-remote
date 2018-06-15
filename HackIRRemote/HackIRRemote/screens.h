/*
 * menu.h
 *
 * Created: 14/06/2018 14:27:26
 *  Author: CDT
 */ 


#ifndef SCREENS_H_
#define SCREENS_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lcdpcf8574.h"
#include "keyboard.h"

extern char ScreenBuf[2][17];
extern uint8_t Refresh;
extern uint8_t ChangedScreen;


extern void (*updatePtr)(void);


uint8_t updateIndex(uint8_t *index, uint8_t maxItem);
void render();

//Main menu
void updateMain();
//Rec/play
void updateSpyRec();


#endif /* SCREENS_H_ */