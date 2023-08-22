/*
 * lamps.h
 *
 * Created: 12/9/2019 8:00:09 p. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef LAMPS_H_
#define LAMPS_H_


//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"


// -------- LCD Lamps Defines --------- //

//LCD display lamps pins
#define LCD_LAMP_MASKS    ((1 << LCD_LAMP_TEMPERATURE) | (1 << LCD_LAMP_SPEED))

//LCD's lamps state (ON|OFF)
typedef enum tagLAMPS_STATE {
   LAMP_TEMPERATURE_ON  = 0x01,
   LAMP_TEMPERATURE_OFF = 0x02,
   LAMP_SPEED_ON        = 0x04,
   LAMP_SPEED_OFF       = 0x08
} LAMPS_STATE;


// -------- LCD's Lamps Functions Prototypes --------- //

void LampsInit(void);
void LampsSetState(LAMPS_STATE);


#endif /* LAMPS_H_ */