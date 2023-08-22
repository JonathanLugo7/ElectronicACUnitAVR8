//0x4A4C676F
/*
 * threeLevelSwitch.c
 *
 * Created: 3/1/2019 3:34:20 p. m.
 *  Author: IoT SolucioneX
 */ 


//--- Includes ---//
#include "threeLevelSwitch.h"


#if defined(DEBUG) || defined(DEBUG_TLPS)
#include "comms/usart.h"
#endif


//--- Global local variables ---//


//--- API implementation ---//

/* ***
   FUNCTION: void TLPSInit(void)
   DESCRIPTION: Set Three Level Pressure Switch L293D driver configuration

   PARAMETERS: void
   RETURN: void
*** */
void TLPSInit(void) {
   // Input HIGH H-Bridge L293D Output = HiZ
   TLPS_PORT |= (1 << TLPS_L293D_3A);

   // DDRx=1, PIN is output
   TLPS_DDR |= (1 << TLPS_L293D_3A);

#if defined(DEBUG)
   USARTPrintString("TLPS-Init\n");
#endif
}

/* ***
   FUNCTION: void TLPSSetState(TLPS_STATE state)
   DESCRIPTION: Set Three Level Pressure Switch L293D driver controller

   PARAMETERS: TLPS_STATE state. Three Level Pressure Switch state
   RETURN: void
*** */
void TLPSSetState(TLPS_STATE state) {
   // ON/OFF L293D output
   if (state == TLPSS_ON) {
      TLPS_PORT &= ~(1 << TLPS_L293D_3A);
   }
   else {
      TLPS_PORT |= (1 << TLPS_L293D_3A);
   }

   _no_operation();
}
