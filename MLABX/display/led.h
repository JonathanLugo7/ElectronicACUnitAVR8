/*
 * LEDs.h
 *
 * Created: 25/11/2016 3:18:43 p.m.
 *  Author: IoT SolucioneX
 */ 


#ifndef LEDS_H_
#define LEDS_H_

//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"


// -------- LED's Defines --------- //

//
// MM5481N Pin out Configuration
//
//                 ------_------
//  OUTPUT Bit 8 -|1          20|- OUTPUT Bit 9
//  OUTPUT Bit 7 -|2          19|- OUTPUT Bit 10
//  OUTPUT Bit 6 -|3          18|- OUTPUT Bit 11
//  OUTPUT Bit 5 -|4          17|- OUTPUT Bit 12
//  OUTPUT Bit 4 -|5          16|- OUTPUT Bit 13
//  OUTPUT Bit 3 -|6          15|- Vss (GND)
//  OUTPUT Bit 2 -|7          14|- OUTPUT Bit 14
//  OUTPUT Bit 1 -|8          13|- DATA_ENABLE (Active Low)
//   BRIGHT Ctrl -|9          12|- DATA
//           Vdd -|10         11|- CLOCK_IN
//                 -------------
//

#define LED_MASKS ((1 << LED_DATA) | (1 << LED_CLOCK_IN) | (1 << LED_DATA_ENABLE))

//MM5481N Data sheet: Using a format of a leading '1' followed by the 35 data bits allows data transfer
//without an additional load signal. NOTE: X means don't care bits.
//Data Package Format:
// ------------------------------------------------------------------------------------------------------------------
//| START | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31|32|33|34|5450|
// ------------------------------------------------------------------------------------------------------------------
//| START | X| X| X| X| 1| 2| 3| 4| X| X| X| X| 5| 6| 7| 8| X| X| X| X| 9|10|11|12| X| X| X| X|13|14| X| X| X| X|5481|
// ------------------------------------------------------------------------------------------------------------------
//         \_____________________/ \_____________________/ \_____________________/ \_____________________/ 
//                 BYTE 1                   BYTE2                   BYTE3                   BYTE4

//LEDs OUTPUT Bit position. MM5481 Data frame 34bits, we are using only 9 outputs LED9:1 in 4 bytes
//LED bit                           //Decimal  Binary    Description
#define LED_CLEAR          0x00     //      0  00000000  LEDs OFF
#define LED_AUTO           0x10     //     16  0001xxxx  LED 1 - 
#define LED_ECONOMICS      0x20     //     32  0010xxxx  LED 2  |_ Byte1
#define LED_RECIRCULATE    0x40     //     64  0100xxxx  LED 3  |
#define LED_OFF            0x80     //    128  1000xxxx  LED 4 -
#define LED_WINDSHIELD     0x10     //     16  0001xxxx  LED 5 -
#define LED_FRONT          0x20     //     32  0010xxxx  LED 6  |_ Byte2
#define LED_FRONT_FEET     0x40     //     64  0100xxxx  LED 7  |
#define LED_FEET           0x80     //    128  1000xxxx  LED 8 -
#define LED_ON             0x10     //     16  0001xxxx  LED 9 }   Byte3

//Change AirDistributionMotor LEDs
#define LED_ADM_MASK       (LED_WINDSHIELD | LED_FRONT | LED_FRONT_FEET | LED_FEET)

// -------- LED's Functions Prototypes --------- //

void LEDInit(void);
void LEDSendData(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void LEDClear(void);


#endif /* LEDS_H_ */