/*
 * eeprom.c
 *
 * Created: 16/06/2018 18:17:58
 *  Author: CDT
 */ 
#include "eeprom.h"

void saveCode(decode_results *dec_results, uint8_t offset)
{
	switch(dec_results->decode_type) // le stockage en mémoire EEPROM dépend du protocole mais est d'une taille fixe de 5 octets
	{
		case NEC:
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)((dec_results->value&0xFF000000)>>24));
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)((dec_results->value&0xFF00)>>8));
			break;
		case NEC_EXT:
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+1), (uint8_t)((dec_results->value&0xFF000000)>>24));
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)((dec_results->value&0xFF0000)>>16));
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)((dec_results->value&0xFF00)>>8));	
			break;		
		case RC5:
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)((dec_results->value&0x3C0)>>6));
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)(dec_results->value&0x3F));
			break;
		case SONY:
			eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+1), (uint8_t)(dec_results->bits));
			if(dec_results->bits == 12)
			{	
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)(dec_results->value&0x1F));
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)((dec_results->value&0xFE0)>>5));
			}
			else if(dec_results->bits == 15)
			{
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)(dec_results->value&0xFF));
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)((dec_results->value&0x7F00)>>8));
			}
			else if(dec_results->bits == 20)
			{
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2), (uint8_t)((dec_results->value&0x1F00)>>8));
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3), (uint8_t)((dec_results->value&0xFE000)>>13));
				eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE+4), (uint8_t)(dec_results->value&0xFF));
			}
			break;
		default:
			return;
	}
	eeprom_update_byte((uint8_t*)(offset*KEY_FIELD_SIZE), (uint8_t)(dec_results->decode_type));
}
void getCode(decode_results *dec_results, uint8_t offset)
{
	dec_results->decode_type=eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE));
	uint8_t addressHigh = eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE+1));
	uint8_t addressLow = eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE+2));
	uint8_t command = eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE+3));
	uint8_t extend;
	
	switch(dec_results->decode_type)
	{
		case NEC:
			dec_results->bits = NEC_BITS;			
			dec_results->value = ((uint32_t)(addressLow))<<24 | ((uint32_t)(~addressLow&0xFF))<<16 | ((uint16_t)(command&0xFF))<<8 | ((~command)&0xFF);
			break;
		case NEC_EXT:
			dec_results->bits = NEC_BITS;			
			dec_results->value = ((uint32_t)(addressHigh))<<24 | ((uint32_t)(addressLow&0xFF))<<16 | ((uint16_t)(command&0xFF))<<8 | ((~command)&0xFF);
			break;
		case RC5:
			dec_results->bits = MIN_RC5_SAMPLES;
			dec_results->value = ((uint16_t)(addressLow))<<6 | command;
			break;
		case SONY:
			dec_results->bits=eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE+1));
			extend=eeprom_read_byte((uint8_t*)(offset*KEY_FIELD_SIZE+4));
			
			if(dec_results->bits == 12)
				dec_results->value = ((uint16_t)(command))<<5 | addressLow;
			else if(dec_results->bits == 15)
				dec_results->value = ((uint16_t)(command))<<8 | addressLow;
			else if(dec_results->bits == 20)
				dec_results->value = ((uint32_t)(command))<<13 | ((uint16_t)addressLow)<<8 | extend;
			break;
		default:
			dec_results->decode_type=UNKNOWN;
			break;
	}
}