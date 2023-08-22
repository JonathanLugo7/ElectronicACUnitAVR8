/*
 * AirDistMotor.h
 *
 * Created: 3/8/2016 6:31:30 p. m.
 *  Author: IoT SolucioneX
 */ 

#ifndef AIRDISTMOTOR_H_
#define AIRDISTMOTOR_H_

//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"
#include "HAL/adc.h"


//-- Defines --//

// AirDistMotor MASK
#define ADM_INPUT_MASK        ((1 << ADM_L293D_1A) | (1 << ADM_L293D_2A))

// ADC Channel Air Distribution Motor Potentiometer
#define ADM_COUNTER_CHECK     10       // Check motor position every n ms
#define ADM_EMERGENCY_STOP    25       // n seconds for Emergency stop

// Max time motor moving. (ns * 1000ms) / 10ms = n execution task before stop motor moving 
#define ADM_MAX_TIME_MOVING   (ADM_EMERGENCY_STOP * 1000) / ADM_COUNTER_CHECK    

// Air Distribution Motor Positions
typedef enum tagADM_POSITION { 
   ADM_FRONT = 0,      // Dec 0. FRONT position = KEY_FRONT
   ADM_FRONT_FEET,     // Dec 1. FRONT/FEET position = KEY_FRONT_FEET
   ADM_FEET,           // Dec 2. FEET position = KEY_FEET
   ADM_WINDSHIELD,     // Dec 3. WINDSHIELD position = KEY_WINDSHIELD
   ADM_UNDEFINED       // Dec 4. Indeterminate position
} ADM_POSITION;

// Air Dist. Motor movement
typedef enum tagADM_MOVE { 
   ADM_MOVE_NONE  = 0, 
   ADM_MOVE_LEFT  = -1, 
   ADM_MOVE_RIGHT = 1 
} ADM_MOVE;

/* See EEPROM_data.c/h 
#define ADM_ADC_FRONT         0x0064   // Dec. 100: Position   A=0°
#define ADM_ADC_FRONT_FEET    0x0177   // Dec. 375: Position A-B=60°
#define ADM_ADC_FEET          0x0253   // Dec. 595: Position A-C=113° +/-1
#define ADM_ADC_WINDSHIELD    0x0393   // Dec. 915: Position A-D=185°
*/

#define ADM_MAX_POSITION      0x04     // Dec. 4. Air Dist. Motor total positions
#define ADM_ADC_OFFSET        0x02     // Dec. 2. Air Dist. Motor ADC Potentiometer offset value

// Air Dist. Motor task data
typedef struct tagADMPositionInfo {
   uint16_t adcPositionSource;         // Actual Air Dist. Motor position ADC value, reading from ADM potentiometer
   uint16_t adcPositionTarget;         // (Start) Actual Air Dist. Motor position ADC value, reading from ADM potentiometer
   ADM_MOVE admMove;                   // If start <> end then where to move?
   uint16_t adcRunningTime;            // For emergency stop
} ADM_POSITION_INFO, *pADM_POSITION_INFO;


// --- Functions prototype ---//

void ADMInit(void);
void ADMUpdatePositionInfo(pADM_POSITION_INFO, ADM_POSITION);


#endif /* AIRDISTMOTOR_H_ */
