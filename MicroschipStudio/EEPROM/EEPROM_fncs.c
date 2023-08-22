/*
 * EEPROM_fncs.c
 *
 * Created: 17/5/2018 3:36:57 p. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

//-- Includes --//
#include "EEPROM_fncs.h"


//--- API implementation ---//

/* ***
   FUNCTION: void EEPROMRead_block(const void * address, void * block, size_t size)
   DESCRIPTION: Read data from eeprom memory space and write into block memory space

   PARAMETERS: uint16_t address: eeprom memory start address
               void* block: Target block address to write eeprom data read
               size_t size: Size-of of memory block to read
   RETURN: void
*** */
void EEPROMRead_block(uint16_t address, void * block, size_t size) {
   eeprom_read_block(block, (const void *) address, size);
}

/* ***
   FUNCTION: void EEPROMWrite_block(const void * address, void * block, size_t size)
   DESCRIPTION: Write data from block memory space into eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
               void* block: Source block address to write to eeprom data
               size_t size: Size-of of memory block to read
   RETURN: void
*** */
void EEPROMWrite_block(uint16_t address, void * block, size_t size) {
   eeprom_update_block((const void *) address, block, size);
}

/* ***
   FUNCTION: uint8_t EEPROMRead_byte(uint8_t address)
   DESCRIPTION: Read unsigned char data from eeprom memory space

   PARAMETERS: uint8_t address: eeprom memory start address
   RETURN: float: eeprom data
*** */
uint8_t EEPROMRead_byte(uint16_t address) {
   return eeprom_read_byte((uint8_t *) address);
}

/* ***
   FUNCTION: void EEPROMWrite_byte(uint8_t address, uint8_t value)
   DESCRIPTION: Write unsigned char data to eeprom memory space

   PARAMETERS: uint8_t address: eeprom memory start address
               uint8_t value: Value to write into eeprom

   RETURN: void
*** */
void EEPROMWrite_byte(uint16_t address, uint8_t value) {
   eeprom_update_byte((uint8_t *) address, value);
}

/* ***
   FUNCTION: uint16_t EEPROMRead_word(uint16_t address)
   DESCRIPTION: Read int data from eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
   RETURN: float: eeprom data
*** */
uint16_t EEPROMRead_word(uint16_t address) {
   return eeprom_read_word((uint16_t *) address);
}

/* ***
   FUNCTION: void EEPROMWrite_float(uint16_t address, float value)
   DESCRIPTION: Write float data to eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
               float value: Value to write into eeprom
               
   RETURN: void
*** */
void EEPROMWrite_word(uint16_t address, uint16_t value) {
   eeprom_update_word((uint16_t *) address, value);
}

/* ***
   FUNCTION: uint32_t EEPROMRead_dword(uint32_t address)
   DESCRIPTION: Read long data from eeprom memory space

   PARAMETERS: uint32_t address: eeprom memory start address
   RETURN: float: eeprom data
*** */
uint32_t EEPROMRead_dword(uint16_t address) {
   return eeprom_read_dword((uint32_t *) address);
}

/* ***
   FUNCTION: void EEPROMWrite_float(uint16_t address, float value)
   DESCRIPTION: Write float data to eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
               float value: Value to write into eeprom
               
   RETURN: void
*** */
void EEPROMWrite_dword(uint16_t address, uint32_t value) {
   eeprom_update_dword((uint32_t *) address, value);
}

/* ***
   FUNCTION: float EEPROMRead_float(const float * address)
   DESCRIPTION: Read float data from eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
   RETURN: float: eeprom data
*** */
float EEPROMRead_float(uint16_t address) {
   return eeprom_read_float((float *) address);
}

/* ***
   FUNCTION: void EEPROMWrite_float(uint16_t address, float value)
   DESCRIPTION: Write float data to eeprom memory space

   PARAMETERS: uint16_t address: eeprom memory start address
               float value: Value to write into eeprom
               
   RETURN: void
*** */
void EEPROMWrite_float(uint16_t address, float value) {
   eeprom_update_float((float*) address, value);
}
