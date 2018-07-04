/*
 * eeprom.h
 *
 * Created: 16/06/2018 18:09:01
 *  Author: CDT
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "avr/eeprom.h"
#include "IRremote.h"

#define KEY_FIELD_SIZE 5 // taille des enregistrements

void saveCode(decode_results *dec_results, uint8_t offset);
void getCode(decode_results *dec_results, uint8_t offset);



#endif /* EEPROM_H_ */