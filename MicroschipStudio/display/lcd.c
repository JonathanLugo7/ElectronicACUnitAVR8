/*
 * LCD.c
 *
 * Created: 12/12/2016 2:46:22 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

//-- Includes --//
#include <avr/pgmspace.h>
#include "lcd.h"


#if defined(DEBUG) || defined(DEBUG_LCD)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Global locals variables ---//

// LCD numbers lookup table
static const uint8_t const g_lcdNumbers[] PROGMEM = {
   //0      1      2      3      4      5      6      7      8      9
   LCD_0, LCD_1, LCD_2, LCD_3, LCD_4, LCD_5, LCD_6, LCD_7, LCD_8, LCD_9
};


/* ***
   FUNCTION: extern void LCDSendDataAsm(uint32_t)
   DESCRIPTION: Send data to the PCF2112CT trough the C-Bus serial lines. This function
                is written in assembly, see PCF2112CT_asm.s to see the description.

   PARAMETERS: uint32_t
   RETURN: void
*** */
extern void LCDSendDataAsm(uint32_t);


/* ***
   FUNCTION: LCDInit()
   DESCRIPTION: Config led driver PCF2112CT ports

   PARAMETERS: void
   RETURN: void
*** */
void LCDInit(void) {
   // Set LCD Port low
   LCD_PORT &= ~(LCD_MASKS);           // PCF2112CT C-Bus Lines

   // Set LCD port DDRx=1 as output
   LCD_DDR |= LCD_MASKS;               // Set LCD PORT has output. PCF2112CT C-Bus Lines

#if defined(DEBUG)
   USARTPrintString("LCD-Init\n");
#endif
}

/* ***
   FUNCTION: LCDSendData()
   DESCRIPTION: Send data to the PCF2112CT LCD driver. This function pack
                the fourth bytes of the PCF2112CT data frame and then call
                the assembler code to show LCD info

               LSB                                                    MSB
   PARAMETERS: uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4
   RETURN: void
*** */
void LCDSendData(uint8_t byte1, uint8_t byte2, uint8_t  byte3, uint8_t byte4) {
   LCDSendDataAsm(PACK32(byte4, byte3, byte2, byte1));
}

/* ***
   FUNCTION: void LCDClear(void)
   DESCRIPTION: Clear the LCD display. Send 0ul to LCDSendDataAsm is the equivalent
                to set off all the Segment in the PCF2112CT

   PARAMETERS: void
   RETURN: void
*** */
void LCDClear(void) {
   LCDSendData(LCD_CLEAR, LCD_CLEAR, LCD_CLEAR, LCD_CLEAR);
}

/* ***
   FUNCTION: uint8_t LCDNumberToDigit(uint8_t number)
   DESCRIPTION: Convert any number from 0..9 into LCD Segment Code 0..9

   PARAMETERS: uint8_t number. Number to convert
   RETURN: uint8_t. LCD Digit Code
*** */
uint8_t LCDNumberToDigit(uint8_t number) {
   // The g_lcdNumbers is ordered from 0 to 9, because of that any number from 0..9 is the index from 
   // g_lcdNumbers array
   return pgm_read_byte(&g_lcdNumbers[number]);
}
