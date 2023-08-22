/*
 * UnitUI.h
 *
 * Created: 7/12/2016 1:55:24 a.m.
 *  Author: IoT SolucioneX
 */ 


#ifndef UNITUI_H_
#define UNITUI_H_


//--- Includes ---//
#include "HAL/config.h"
#include "unit.h"


//--- Defines ---//

//Display structure for read/write EEPROM saved data for keep display info of the Electronic A/A Unit
typedef struct tagUnitUI {
   //LCD Display UI info. 32bit of data
   uint8_t LCDDigit1;
   uint8_t LCDDigit2;
   uint8_t LCDSymbols;
   uint8_t LCDSpeed;
   //LED Display UI info. 32bit
   uint8_t LEDStatus;
   uint8_t LEDAirDistMotor;
   uint8_t LEDOn;
   uint8_t LEDDummy;    //MM5481 LED Display Driver 9 LEDs only
} UNIT_UI, *pUNIT_UI;


// -------- Functions Prototypes --------- //

void UnitUIUpdate(pUNIT_STATE, pTEMP_SENSORS_INFO);


#endif /* UNITUI_H_ */