/*
 * HackIRRemote.c
 *
 * Created: 30/05/2018 12:49:52
 * Author : CDT
 */ 
#include "systick.h"
#include "screens.h"
#include "keyboard.h"
#include "IRlib/IRremote.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "lcdpcf8574.h"



int main(void)
{
	uint16_t  keyboardRef;
	DDRD |= 1<<6; // initialisation de la broche pour l'émission en sortie.
	initSysTick(); // initialisation du systick global
	sei(); // activation des interruptions
	lcd_init(LCD_DISP_ON); // initialisation de l'écran
	lcd_led(0); // allumage du backlight
	
	updatePtr = updateMain; // Initialise le pointeur de fonction globale avec la fonction du menu principal
	
	
	marqueTime16(&keyboardRef); // initialisation de la référence de temps pour la lecture du clavier
	while(1)
	{
		if(elapsedTime16(&keyboardRef)>2) // 20ms
		{
			processKeyboard();
			marqueTime16(&keyboardRef);
		}
		if(ChangedScreen) // lorsqu'on change de menu on remet à zéro ChangedScreen après l'appel de l'update du menu courant
		{
			updatePtr();
			ChangedScreen=0;
		}
		else
			updatePtr();
		render(); // Affichage de l'écran
		clearKeys(); // Réinitialisation des flag keyboard
	}
	
	
}

// Routines d'interruptions

ISR(TIMER0_COMPA_vect)
{
	ir_interruptService(); // Appel de la fonction d'acquisition
}
ISR(TIMER2_COMPA_vect)
{
	incSysTick(); // Incrémentation du systick
}

