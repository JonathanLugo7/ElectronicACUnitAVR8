/* ***

   Buttons.c

   Created: 10/7/2016 3:54:52 a. m.
   Author: IoT SolucioneX

*** */ 

//--- Includes ---//
#include "keypad.h"
#include "HAL/config.h"
#include "rtos/tasks.h"


#if defined(DEBUG) || defined(DEBUG_KYPD)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Globals local variables ---//
static KEY_ID  g_keyPressed = KEYPAD_NO_KEY_PRESS;
static uint8_t g_dirty = 0;


// --- Keypad helpers ---//

/*
//
// Lookup table for key code. Operation: (ROW * TOTAL_COLUMNS) + COL
//                           Example:   (2  *  4) + 1 = 9 = KEY_FRONT
//
// NOTE: See Electronic A/A Unit Keypad layout in keypad.h
//       Zero base index
static const uint8_t const g_KeyLookupTable[KEYPAD_ROWS * KEYPAD_COLS] PROGMEM = {
   //COL0            COL1              COL2              COL3
   KEY_TEMP_MINUS,   KEY_SPEED_MINUS,  KEY_SPEED_PLUS,   KEY_TEMP_EXTERN,  //ROW0
   0,                KEY_RECIRCULATE,  KEY_OFF,          KEY_FEET,         //ROW1
   0,                KEY_FRONT_FEET,   KEY_FRONT,        KEY_WINDSHIELD,   //ROW2
   0,                KEY_TEMP_PLUS,    KEY_ECONOMICS,    KEY_AUTO,         //ROW3
};
*/

#if DEBUG_KYPD

/* ***
   FUNCTION: char* KeypadDescription(KEY_ID key)
   DESCRIPTION: Get key pressed read name

   PARAMETERS: KEY_ID: key
   RETURN: char*: Key description
*** */
static char *KeypadDescription(KEY_ID key) {

   static char desc[10] = { '\0' };

   if (key == KEY_TEMP_MINUS) strcpy(desc, "TEMP-");
   if (key == KEY_SPEED_MINUS) strcpy(desc, "SPEED-");
   if (key == KEY_SPEED_PLUS) strcpy(desc, "SPEED+");
   if (key == KEY_TEMP_EXTERN) strcpy(desc, "EXT");
   if (key == KEY_RECIRCULATE) strcpy(desc, "RECI");
   if (key == KEY_OFF) strcpy(desc, "OFF");
   if (key == KEY_FEET) strcpy(desc, "FEET");
   if (key == KEY_FRONT_FEET) strcpy(desc, "FRNT+FEET");
   if (key == KEY_FRONT) strcpy(desc, "FRNT");
   if (key == KEY_WINDSHIELD) strcpy(desc, "WNDSH");
   if (key == KEY_TEMP_PLUS) strcpy(desc, "TEMP+");
   if (key == KEY_ECONOMICS) strcpy(desc, "ECO");
   if (key == KEY_AUTO) strcpy(desc, "AUTO");
   if (key == KEYPAD_NO_KEY_PRESS) strcpy(desc, "NO_KEY");

   return desc;
}

#endif


/* ***
   FUNCTION: KEY_ID KeypadScan(void)
   DESCRIPTION: Set HIGH (1) each row in PORTB0:3 for keypad column scan PORTB4:7

   PARAMETERS: void
   RETURN: KEY_ID - KeyCodeInfo.
           0xFF for no key press
*** */
static KEY_ID KeypadScan(void) {

   uint8_t keyID = KEYPAD_NO_KEY_PRESS;   // Key pressed code name   
   uint8_t keyPressed  = 0;               // Key pressed scanned
   uint8_t keyDebounce = 0;               // Key pressed scanned for de-bounce

   // Set rows output LOW (Low nibble: 0bxxxx-0000)
   // Set columns input HIGH with pull up (High nibble: 0b1111-xxxx)
   KEYPAD_PORT = 0xF0;

   // Set keypad port as input (High Z state: 0b0000-0000)                                                       
   KEYPAD_DDR &= ~(KEYPAD_COLS_MASK | KEYPAD_ROWS_MASK);    
   _no_operation();

   // For each row, test every column...
   for (uint8_t row = 0; row < KEYPAD_ROWS; row++) {

      KEYPAD_PORT |= (0x01 << row);    // Set row[i] pin HIGH. (Low nibble: 0bxxxx-0001 -> 0bxxxx-1000)
      KEYPAD_DDR  |= (0x01 << row);    // Set row[i] pin as output
      _no_operation();                 // For port sync. See datasheet

      // ..., test every column!
      for (uint8_t col = 0; col < KEYPAD_ROWS; col++) {

         _delay_us(KEYPAD_SCAN_DELAY);                // Stay HIGH for nN us.
         keyPressed = (KEYPAD_PIN & (0x10 << col));   // Read PINx for key pressed (0b0001-xxxx -> 0b1000-xxxx) 
         
         // Key pressed? De-bounce
         if (keyPressed) {
            
            // Read PINx for key pressed after de-bounce delay
            _delay_us(KEYPAD_DEBOUNCE_DELAY);
            keyDebounce = (KEYPAD_PIN & (0x10 << col));

            // Key de-bounce?
            if (keyDebounce) {

               // Is the same key?
               if (keyPressed == keyDebounce) {

                  // Get key code ID, we use this formula (Row * TOTAL_COLUMNS) + Column
                  // keyID = pgm_read_byte(&g_KeyLookupTable[(row * KEYPAD_COLS) + col]);
                  keyID = (row * KEYPAD_COLS) + col;  

                  // Let main() task process this key
                  break;
               }
            }
         }
      }  // END: for (uint8_t col = 0; col < KEYPAD_COLS; col++) 

      // Continue with other column
      KEYPAD_PORT &= ~(0x01 << row);
      KEYPAD_DDR  &= ~(0x01 << row);
      _no_operation();

      if (keyID != KEYPAD_NO_KEY_PRESS) {
         break;
      }

   }  // END: for (uint8_t row = 0; row < KEYPAD_ROWS; row++) 

   // We got the key or NO_KEY_PRESSED
   return keyID;
}


// --- Keypad API Implementation ---// 

/* ***
   FUNCTION: void KeypadInit(void)
   DESCRIPTION: Initialize keypad HAL

   PARAMETERS: void
   RETURN: void
*** */
void KeypadInit(void) {

   // Rows as outputs and Columns as inputs with external 8.2K pull-down resistors
   KEYPAD_PORT = 0x00;  // Set port as low

   // I/O digital configuration
   // DDRx=0 and PORTx=1 Input with Pull-Up enable
   // DDRx=0 and PORTx=0 Input with Pull-Down
   // DDRx=1             Output

   // Columns are in PORTx7..4 as input, no internal pull-up
   // Rows are in PORTx3..0 as output
   KEYPAD_DDR &= ~(KEYPAD_COLS_MASK | KEYPAD_ROWS_MASK);
   _no_operation();

#if defined(DEBUG)
    USARTPrintString("KYPD-Init\n");
#endif
}

/* ***
   FUNCTION: void KeypadTask(pTASK task)
   DESCRIPTION: Keypad scan task callback function

   PARAMETERS: pTASK task. TASK structure
   RETURN: void
*** */
void KeypadTask(pTASK task) {

   static uint8_t prevState = KEYPAD_KEYUP;

   KEY_ID keyCode = KeypadScan();

   // Save last key ID, don't let the same key pressed over and over, let stay in push down mode until key is release
   if (keyCode != KEYPAD_NO_KEY_PRESS) {
      if (prevState == KEYPAD_KEYUP) {
         g_keyPressed = keyCode;
         prevState = KEYPAD_KEYDOWN;

         g_dirty = 1;
      }
   }
   else {
      if (prevState == KEYPAD_KEYDOWN) {
         g_keyPressed = KEYPAD_NO_KEY_PRESS;
         prevState = KEYPAD_KEYUP;
      }
   }

#if defined(DEBUG_KYPD)
    if (keyCode != KEYPAD_NO_KEY_PRESS) {
        sprintf(str, "KYPD-Tsk. [0x%02X]: %s\n", keyCode, KeypadDescription(keyCode));
        USARTPrintString(str);
    }
#endif
}

/* ***
   FUNCTION: KEY_ID KeypadGetLastKey(void)
   DESCRIPTION: Keypad get last key pressed

   PARAMETERS: pTASK task. TASK structure
   RETURN: KEY_ID. Key code or NO_KEY_PRESSED
*** */
KEY_ID KeypadGetLastKey(void) {
   uint8_t k = (g_dirty ? g_keyPressed : KEYPAD_NO_KEY_PRESS);     
   
   // Clean last key pressed
   g_dirty = 0;
   
   return k;
}
