/*
 * keyboard.h
 *
 * Created: 15/06/2018 11:12:48
 *  Author: CDT
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>

#define X1 0
#define X2 1
#define X3 2

#define Y1 3
#define Y2 4
#define Y3 5
#define Y4 6

#define keyboardDDRx DDRB
#define keyboardPORTx PORTB
#define keyboardPINx PINB


#define KEY_NONE 0
#define KEY_1 (1<<X1 | 1<<Y1)
#define KEY_2 (1<<X2 | 1<<Y1)
#define KEY_3 (1<<X3 | 1<<Y1)
#define KEY_4 (1<<X1 | 1<<Y2)
#define KEY_5 (1<<X2 | 1<<Y2)
#define KEY_6 (1<<X3 | 1<<Y2)
#define KEY_7 (1<<X1 | 1<<Y3)
#define KEY_8 (1<<X2 | 1<<Y3)
#define KEY_9 (1<<X3 | 1<<Y3)
#define KEY_ASTERISK (1<<X1 | 1<<Y4)
#define KEY_0 (1<<X2 | 1<<Y4)
#define KEY_HASH (1<<X3 | 1<<Y4)

extern uint8_t PressedKeyCode;
extern uint8_t ReleasedKeyCode;

void processKeyboard();
void clearKeys();

void setKeyboardPhase1();
void setKeyboardPhase2();
uint8_t readKeyboardPhase1();
uint8_t readKeyboardPhase2();



#endif /* KEYBOARD_H_ */