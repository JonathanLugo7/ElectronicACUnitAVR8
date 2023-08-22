//0x4A4C676F
/*
 * threeLevelSwitch.h
 *
 * Created: 3/1/2019 3:34:08 p. m.
 *  Author: IoT SolucioneX
 */ 


#ifndef THREELEVELSWITCH_H_
#define THREELEVELSWITCH_H_


//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"


//-- Defines --//

// Air Dist. Motor movement
typedef enum tagTLPS_STATE { 
   TLPSS_OFF = 0, 
   TLPSS_ON 
} TLPS_STATE;


// --- Functions prototype ---//

void TLPSInit(void);
void TLPSSetState(TLPS_STATE);


#endif /* THREELEVELSWITCH_H_ */
//0x4A4C676F