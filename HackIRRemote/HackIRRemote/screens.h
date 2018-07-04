/*
 * menu.h
 *
 * Created: 14/06/2018 14:27:26
 *  Author: CDT
 */ 


#ifndef SCREENS_H_
#define SCREENS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcdpcf8574.h"
#include "keyboard.h"
#include "IRremote.h"
#include "eeprom.h"
#include "systick.h"

extern char ScreenBuf[2][17]; // Back buffer de l'�cran 2*(16+1 pour le carct�re '\0')
extern uint8_t Refresh; // Flag global de mise � jour de l'�cran
extern uint8_t ChangedScreen; // Flag global qui indique le changement de menu


extern void (*updatePtr)(void); // Pointeur de fonction global

// d�termine le nouvel index qui sert � la selection d'un item d'un menu
uint8_t updateIndex(uint8_t *index, uint8_t maxItem);
// Fonction qui sert � afficher un protocole
void displayProtocol(decode_results *dec_results);
// Fonction de mise � jour de l'�cran
void render();

//Main Menu
void updateMain();
//Spy/Rec Menu
void updateSpyRec();
//Saved
void updateSaved();
//play Menu
void updatePlay();


#endif /* SCREENS_H_ */