/*
 * EEPROM_fncs.h
 *
 * Created: 17/5/2018 3:35:05 p. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef EEPROM_FNCS_H_
#define EEPROM_FNCS_H_


// -------- Includes --------- //
#include <avr/eeprom.h>
#include "HAL/config.h"


// -------- Defines --------- //


// -------- API --------- //

//Load data from EEPROM to data structure

// Read operation
void EEPROMRead_block(uint16_t address, void * block, size_t size);
uint8_t EEPROMRead_byte(uint16_t address);
uint16_t EEPROMRead_word(uint16_t address);
uint32_t EEPROMRead_dword(uint16_t address);
float EEPROMRead_float(uint16_t address);

// Write operation
void EEPROMWrite_block(uint16_t address, void * block, size_t size);
void EEPROMWrite_byte(uint16_t address, uint8_t value);
void EEPROMWrite_word(uint16_t address, uint16_t value);
void EEPROMWrite_dword(uint16_t address, uint32_t value);
void EEPROMWrite_float(uint16_t address, float value);


#endif /* EEPROM_FNCS_H_ */