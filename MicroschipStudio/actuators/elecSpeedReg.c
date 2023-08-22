/*
 * elecSpeedReg.c
 *
 * Created: 21/10/2018 9:04:43 p. m.
 *  Author: IoT SolucioneX
 */ 

#include "elecSpeedReg.h"
#include "rtos/tasks.h"
#include "EEPROM/EEPROM_fncs.h"
#include "EEPROM/EEPROM_address.h"


#if defined(DEBUG) || defined(DEBUG_ESR)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Global local variables ---//
static uint16_t g_speedOCR2[ESR_MAX_SPEED];  //Lookup table Electronic Speed Regulator OCR2x values vs speed

// Lookup OCRx value for electronic speed regulator operation:
//
// MANUAL. Index = (unitState.Speed * 2) - 1. Example: unitState.Speed = 4 -> Index = (4 * 2) - 1 = 7
// AUTOmatic. Index = (tempSensorsInfo.Passenger - 18) + 1. Example: tempSensorsInfo.Passenger = 24 -> Index = (24 - 18) + 1 = 7
// ---------------------------------------------------------------------
// Lookup Index Table  | 0| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|
// ---------------------------------------------------------------------
// Temperature [18-32] | 0|18|19|20|21|22|23|24|25|26|27|28|29|30|31|32|
// ---------------------------------------------------------------------
// Speed [0-8]         | 0| 1|--| 2|--| 3|--| 4|--| 5|--| 6|--| 7|--| 8|
// ---------------------------------------------------------------------


//--- API Helpers ---//
static inline void PWMTimerInit(void) {
   ESR_PWM_COUNTER = 0;

   // See elecSpeedReg.h for correct Output Compare Register configuration
   // PWM setup:
   //    Clock prescaler: No Prescaler
   //    Mode: Fast PWM - Mode 3
   //    Output Compare Match: CLEAR OC0x on Compare Match, SET OC0x at BOTTOM (non-inverting mode)

#if defined (__AVR_ATmega324P__)
   TCCR0A = 0x00;
   TCCR0B = 0x00;

   TCCR0A |= (ESR_PWM_COMPARE_OUTPUT_MODE | ESR_PWM_WAVE_FORM_MODE);  
   TCCR0B |= (ESR_CLOCK_PRESCALER | ESR_PWM_WAVE_FORM_MODE_5_7);
#else
   TCCR0  = (ESR_PWM_COMPARE_OUTPUT_MODE | ESR_PWM_WAVE_FORM_MODE | ESR_CLOCK_PRESCALER);
#endif                           
}

//--- API implementation ---//

void ESRInit(void) {
   // Setup PWM on Timer0 output A
   PWMTimerInit();

   // Load Timer0 PWM OCRx values for FAN motor controller
   g_speedOCR2[ESR_SPEED_0]  = 0;
   g_speedOCR2[ESR_SPEED_1]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED1);
   g_speedOCR2[ESR_SPEED_2]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED2);
   g_speedOCR2[ESR_SPEED_3]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED3);
   g_speedOCR2[ESR_SPEED_4]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED4);
   g_speedOCR2[ESR_SPEED_5]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED5);
   g_speedOCR2[ESR_SPEED_6]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED6);
   g_speedOCR2[ESR_SPEED_7]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED7);
   g_speedOCR2[ESR_SPEED_8]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED8);
   g_speedOCR2[ESR_SPEED_9]  = EEPROMRead_byte(EEADDRSS_ESR_SPEED9);
   g_speedOCR2[ESR_SPEED_10] = EEPROMRead_byte(EEADDRSS_ESR_SPEED10);
   g_speedOCR2[ESR_SPEED_11] = EEPROMRead_byte(EEADDRSS_ESR_SPEED11);
   g_speedOCR2[ESR_SPEED_12] = EEPROMRead_byte(EEADDRSS_ESR_SPEED12);
   g_speedOCR2[ESR_SPEED_13] = EEPROMRead_byte(EEADDRSS_ESR_SPEED13);
   g_speedOCR2[ESR_SPEED_14] = EEPROMRead_byte(EEADDRSS_ESR_SPEED14);
   g_speedOCR2[ESR_SPEED_15] = EEPROMRead_byte(EEADDRSS_ESR_SPEED15);

#if defined(DEBUG)   
   USARTPrintString("ESR-Init\n");
#endif

#if defined(DEBUG_ESR)
   for (uint8_t i = 0; i < ESR_MAX_SPEED; i++) {   
      sprintf(str, "ESR-Spd: [%d]-[0x%02X]\n", i, g_speedOCR2[i]);
      USARTPrintString(str);
   }
#endif

   // DDRx=1, PIN is output for PWM
   ESR_DDR |= ESR_PWM_OUTPUT_CHANNEL;
}

void ESRUpdateSpeedInfo(pESR_SPEED_INFO speedInfo, uint8_t speed) {

   // Calculate SOURCE --->>
   speedInfo->SpeedSource = ESR_PWM_COUNTER;

   // Calculate TARGET --->>

   // Set the ESR OCR2x value for the new PWM duty cycle for blower speed
   speedInfo->SpeedTarget = g_speedOCR2[speed];

   // Where to speed up<->down?
   speedInfo->esrMove = ESR_SPEED_NONE;
   if (speedInfo->SpeedTarget < speedInfo->SpeedSource) {
      speedInfo->esrMove = ESR_SPEED_DOWN;
   }
   else if (speedInfo->SpeedTarget > speedInfo->SpeedSource) {
      speedInfo->esrMove = ESR_SPEED_UP;
   }      
}

/* ***
   FUNCTION: void ADMCTask(pTASK task)
   DESCRIPTION: Air Distribution Motor task callback function,
                Check motor moving every ADM_MAX_TIME_MOVING value defined in ms. 

                #define ADM_MAX_TIME_MOVING  10

   PARAMETERS: pTASK task. TASK structure
   RETURN: void
*** */
void ESRTask(pTASK task) {

   pESR_SPEED_INFO esrSpeedInfo = (pESR_SPEED_INFO) task->parameter;
   if (esrSpeedInfo == NULL) {
      return;
   }

   if (esrSpeedInfo->esrMove == ESR_SPEED_UP) {
      esrSpeedInfo->SpeedSource++;
   }
   else {
      esrSpeedInfo->SpeedSource--;
   }

   // If we reach the target speed, then, stop task
   if (esrSpeedInfo->SpeedSource == esrSpeedInfo->SpeedTarget) {
      task->status = TS_IDLE;
   }

   // New PWM Duty Cycle
   ESR_PWM_COUNTER = esrSpeedInfo->SpeedSource;

#if defined(DEBUG_ESR)
   sprintf(str, "ESR-Tsk. Src: [0x%02X] Tgt: [0x%02X]\n", esrSpeedInfo->SpeedSource, esrSpeedInfo->SpeedTarget);
   USARTPrintString(str);
#endif
}
