/*
 * Keys.h
 *
 * Created: 10/7/2016 3:55:05 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

//--- Includes ---//
#include "HAL/pinouts.h"


//
//                 A/C Keypad layout
//
// Buttons: Temperature-, Speed-, Speed+, Exterior Temperature
//          Recirculate, Off, Feet, Front+Feet, Front, Windshield
//          Temperature+, Economics, Auto
// NOTE: N/C = Not Connected
//
//        Columns As Inputs external pull-down resistor
//                      PIN4         PIN5         PIN6         PIN7
//                       |            |            |            |
//                       |            |            |            |
//                       |            |            |            |
// R  PIN0 --------------|------------|------------|------------|
// o                   | |          | |          | |          | |
// w            Temp- |     Speed- |     Speed+ |     Ext.T. |  |
// s                   | |          | |          | |          | |
//                     --|          --|          --|          --|
//                       |            |            |            |
//    PIN1 --------------|------------|------------|------------|
//                     | |          | |          | |          | |
//             Recir. |        Off |       Feet |        N/C |  |
//                     | |          | |          | |          | |
//                     --|          --|          --|          --|
//                       |            |            |            |
//    PIN2 --------------|------------|------------|------------|
//                     | |          | |          | |          | |
//         Front+Feet |      Front |    WndShld |        N/C |  |
//                     | |          | |          | |          | |
//                     --|          --|          --|          --|
//                       |            |            |            |
//    PIN3 --------------|------------|------------|------------|
//                     | |          | |          | |          | |
//              Temp+ |    Econom. |       Auto |        N/C |  |
//                     | |          | |          | |          | |
//                     --|          --|          --|          --|
//                       |            |            |            |
//                       |            |            |            |
//                      8.2K         8.2K         8.2K         8.2K
//                       |            |            |            |
//                     -----        -----        -----        -----
//                      ---          ---          ---          ---
//                       -            -            -            -

// Numbers of rows and columns
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

// Keypad delays
#define KEYPAD_SCAN_DELAY     500   // Keypad scan delay for row in us _delay_us()
#define KEYPAD_DEBOUNCE_DELAY 750   // Button debounce in ms for _delay_us()

// Keyboard Rows Position. Index 0 base
#define KEY_ROW0     0              // Key in column 0
#define KEY_ROW1     1              // Key in column 1
#define KEY_ROW2     2              // Key in column 2
#define KEY_ROW3     3              // Key in column 3

// Keyboard Columns Position. Index 0 base
#define KEY_COL0     0              // Key in column 0
#define KEY_COL1     1              // Key in column 1
#define KEY_COL2     2              // Key in column 2
#define KEY_COL3     3              // Key in column 3

// Keypad Rows for KeypadScan() as outputs no pull-up
// NOTE: low port nibble for rows and high port nibble for columns
#define KEYPAD_ROWS_MASK ((1 << KEYPAD_ROW0) | (1 << KEYPAD_ROW1) | (1 << KEYPAD_ROW2) | (1 << KEYPAD_ROW3))

// Keyboard Columns for KeypadScan() as inputs. 
#define KEYPAD_COLS_MASK ((1 << KEYPAD_COL0) | (1 << KEYPAD_COL1) | (1 << KEYPAD_COL2) | (1 << KEYPAD_COL3))

// Total number of buttons in the keypad
#define KEYPAD_NUM_KEYS          13          

// Keypad key state
#define KEYPAD_KEYDOWN           0x00
#define KEYPAD_KEYUP             0x01

// Keypad key id numbers
typedef enum tagKEY_ID { 
   // KEY_ID              CODE         ROW x COL         BUTTON 
   KEY_TEMP_MINUS       = 0x00,     // Row1.Col1: [ <| Less Temperature ] 
   KEY_SPEED_MINUS      = 0x01,     // Row1.Col2: [ <| Less Speed ]
   KEY_SPEED_PLUS       = 0x02,     // Row1.Col3: [ More Speed |> ]
   KEY_TEMP_EXTERN      = 0x03,     // Row1.Col4: [ Ext. Temperature ]
   KEY_RECIRCULATE      = 0x04,     // Row2.Col1: [ Air Recirculate @ ]
   KEY_OFF              = 0x05,     // Row2.Col2: [ Off ]
   KEY_FEET             = 0x06,     // Row2.Col3: [ Air Dist.: Feet ]
   // KEY_RESERVED      = 0x07,     // Row2.Col4: N/C
   KEY_FRONT_FEET       = 0x08,     // Row3.Col1: [ Air Dist.: Front & Feet ] 
   KEY_FRONT            = 0x09,     // Row3.Col2: [ Air Dist.: Front ] 
   KEY_WINDSHIELD       = 0x0A,     // Row3.Col3: [ Air Dist.: Windshield ]
   // KEY_RESERVED      = 0x0B,     // Row3.Col4: N/C
   KEY_TEMP_PLUS        = 0x0C,     // Row4.Col1: [ More Temperature |> ]
   KEY_ECONOMICS        = 0x0D,     // Row4.Col2: [ Economics ]
   KEY_AUTO             = 0x0E,     // Row4.Col3: [ A/A Automatics ]
   // KEY_RESERVED      = 0x0F      // Row4.Col4: N/C
   KEYPAD_NO_KEY_PRESS  = 0x10      // Special key (Keep in last position)
} 
KEY_ID;


// -------- Keypad Functions Prototypes --------- //
void KeypadInit(void);
KEY_ID KeypadGetLastKey(void);


#endif /* KEYPAD_H_ */
