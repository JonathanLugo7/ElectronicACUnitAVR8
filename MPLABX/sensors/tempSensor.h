/*
 * TempSensor.h
 *
 * Created: 4/3/2017 4:03:25 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

//-- Includes --//
#include "HAL/config.h"


//-- Defines --//

//Fixed temperature resistance values from NTC->uMC.AnalogInput circuit diagram
#define TS_TOP_BLENDED_FIXED_R0        3920
#define TS_BTM_BLENDED_FIXED_R0        3920
#define TS_PASSENGER_FIXED_R0          1500
#define TS_OUTSIDE_FIXED_R0            16500

//Fixed nominal temperature resistance values from NTC at 25� C. See Fiat Tempra - Automatic Air Conditional Manual
#define TS_TOP_BLENDED_NOMINAL_R0_25C  10000
#define TS_BTM_BLENDED_NOMINAL_R0_25C  10000
#define TS_PASSENGER_NOMINAL_R0_25C    2200
#define TS_OUTSIDE_NOMINAL_R0_25C      10000

//Fixed temperature B25/50 B coefficient values. B = (ln(R1) � ln(R2)) / (1 / T1 - 1 / T2),
//                                               Ex.: B = ( ln(10000) - ln(3600) ) / ( (1/(25+273.05)) - (1/50+273.15)) )
//                                                    25� C = 10000 ohm. 25� C = 25+273.15� K = 298.15� K
//                                                    50� C = 36000 ohm. 50� C = 50+273.15� K = 323.15� K
#define TS_TOP_BLENDED_B25_50          3937
#define TS_BTM_BLENDED_B25_50          3937
#define TS_PASSENGER_B25_50            4006
#define TS_OUTSIDE_B25_50              3937


// --- Functions prototype ---//

int8_t TSOutsideMirror(void);
int8_t TSPassenger(void);
int8_t TSBottomBlended(void);
int8_t TSTopBlended(void);


#endif /* TEMPSENSOR_H_ */