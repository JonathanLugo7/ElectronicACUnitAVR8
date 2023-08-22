/*
 * lamps.c
 *
 * Created: 12/9/2019 8:00:23 p. m.
 *  Author: IoT SolucioneX
 */ 

//-- Includes --//
#include "lamps.h"


#ifdef DEBUG_TASK
#include "comms/usart.h"
#endif


//--- Global locals variables ---//


 /* ***
   FUNCTION: LCDLampsInit()
   DESCRIPTION: Config led driver PCF2112CT ports

   PARAMETERS: void
   RETURN: void
*** */
void LampsInit(void) {
   
   //Set LCD lamps Port low
   LCD_LAMP_PORT &= ~(LCD_LAMP_MASKS);    //T1:T2->Base Temperature and Speed LCD lamp

   //Set LCD lamps port DDRx=1 as output
   LCD_LAMP_DDR |= LCD_LAMP_MASKS;        //T1:T2->Base Temperature and Speed LCD lamp

   //Power off
   LampsSetState(LAMP_TEMPERATURE_OFF | LAMP_SPEED_OFF);

   #ifdef DEBUG_TASK
      USARTPrintString("<Lamps: Init>\n\n");
   #endif
}


 /* ***
   FUNCTION: LampsSetState()
   DESCRIPTION: Set LCD's lamps states (ON|OFF)

   PARAMETERS: LAMPS_STATE
   RETURN: void
*** */
void LampsSetState(LAMPS_STATE lampsState) {

   if ((lampsState & LAMP_TEMPERATURE_ON) == LAMP_TEMPERATURE_ON) {
      LCD_LAMP_PORT |= (1 << LCD_LAMP_TEMPERATURE);
   }

   if ((lampsState & LAMP_TEMPERATURE_OFF) == LAMP_TEMPERATURE_OFF) {
      LCD_LAMP_PORT &= ~(1 << LCD_LAMP_TEMPERATURE);
   }

   if ((lampsState & LAMP_SPEED_ON) == LAMP_SPEED_ON) {
      LCD_LAMP_PORT |= (1 << LCD_LAMP_SPEED);
   }

   if ((lampsState & LAMP_SPEED_OFF) == LAMP_SPEED_OFF) {
      LCD_LAMP_PORT &= ~(1 << LCD_LAMP_SPEED);
   }
 }
