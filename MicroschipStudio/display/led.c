/*
 * LED.c
 *
 * Created: 25/11/2016 3:18:57 p.m.
 *  Author: IoT SolucioneX
 */ 

//-- Includes --//
#include "led.h"


#if defined(DEBUG) || defined(DEBUG_LED)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


/* ***
   FUNCTION: extern static void LEDSendDataAsm(uint32_t);
   DESCRIPTION: Send data to the MM5481N trough the serial bus lines. This function
                is written in assembly, see MM5481N_asm.s to see the description.

   PARAMETERS: uint32_t
   RETURN: void
*** */
extern void LEDSendDataAsm(uint32_t);


/* ***
   FUNCTION: LEDSendData()
   DESCRIPTION: Send data to the MM5481n LED driver. This function pack
                the fourth bytes of the MM4581x data frame and then call
                the assembler code to show LED info

               LSB                                                    MSB
   PARAMETERS: uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4
   RETURN: void
*** */
void LEDSendData(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
   LEDSendDataAsm(PACK32(byte4, byte3, byte2, byte1));
}

/* ***
   FUNCTION: LedsInit()
   DESCRIPTION: Config led driver MM5481N ports
                
   PARAMETERS: void
   RETURN: void
*** */
void LEDInit(void) {
   // Set LED Port low
   LED_PORT &= ~LED_MASKS;                //MM5481x serial data lines
   LED_PORT |= (1 << LED_DATA_ENABLE);    //Set HIGH MM5481x.DATA_ENABLE active low

   // Set LCD port DDRx=1 as output
   LED_DDR |= LED_MASKS;                  //Set LED PORT has output. MM5481x serial data lines

#if defined(DEBUG)
    USARTPrintString("LED-Init\n");
#endif
}

void LEDClear(void) {
   LEDSendData(LED_CLEAR, LED_CLEAR, LED_CLEAR, LED_CLEAR);
}
