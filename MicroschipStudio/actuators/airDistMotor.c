/*
 * AirDistMotor.c
 *
 * Created: 3/8/2016 6:31:49 p. m.
 *  Author: IoT SolucioneX
 */ 

//--- Includes ---//
#include "airDistMotor.h"
#include "rtos/tasks.h"
#include "EEPROM/EEPROM_fncs.h"
#include "EEPROM/EEPROM_address.h"


#if defined(DEBUG) || defined(DEBUG_ADM)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Global local variables ---//
static uint16_t g_positionAdc[ADM_MAX_POSITION];   // Lookup table Air Dist. Motor ADC potentiometer value vs position


//--- API Helpers ---//

static void ADMMoveLeft(void) {
   // 1A->HIGH and 2A->LOW
   ADM_PORT |=  (1 << ADM_L293D_1A);
   ADM_PORT &= ~(1 << ADM_L293D_2A);
   _no_operation();
}

static void ADMMoveRight(void) {
   // 1A->LOW and 2A->HIGH
   ADM_PORT |=  (1 << ADM_L293D_2A);
   ADM_PORT &= ~(1 << ADM_L293D_1A);
   _no_operation();
}

static void ADMStop(void) {
   //                1A->LOW                2A->LOW
   ADM_PORT &= ~((1 << ADM_L293D_1A) | (1 << ADM_L293D_2A));
   _no_operation();
}


//--- API implementation ---//

void ADMInit(void) {
   
   ADM_PORT &= ~ADM_INPUT_MASK;     // L293D.A1 and L293D.A2 LOW (Output LOW)
   ADM_DDR  |= ADM_INPUT_MASK;      // DDRx=1, PIN as output
   _no_operation();

   // Load ADC position values for the Air Dist. Motor
   g_positionAdc[ADM_FRONT] = EEPROMRead_word(EEADDRSS_ADM_ADC_FRONT);
   g_positionAdc[ADM_FRONT_FEET] = EEPROMRead_word(EEADDRSS_ADM_ADC_FRONT_FEET);
   g_positionAdc[ADM_FEET] = EEPROMRead_word(EEADDRSS_ADM_ADC_FEET);
   g_positionAdc[ADM_WINDSHIELD] = EEPROMRead_word(EEADDRSS_ADM_ADC_WINDSHLD);

#if defined(DEBUG)
   USARTPrintString("ADM-Init\n");
#endif

#if defined(DEBUG_ADM)
   sprintf(str, "ADM-FRNT: [%d]\n", g_positionAdc[ADM_FRONT]);
   USARTPrintString(str);
   sprintf(str, "ADM-FRNT_FT: [%d]\n", g_positionAdc[ADM_FRONT_FEET]);
   USARTPrintString(str);
   sprintf(str, "ADM-FT: [%d]\n", g_positionAdc[ADM_FEET]);
   USARTPrintString(str);
   sprintf(str, "ADM-WNDSHLD: [%d]\n\n", g_positionAdc[ADM_WINDSHIELD]);
   USARTPrintString(str);
#endif
}

void ADMUpdatePositionInfo(pADM_POSITION_INFO positionInfo, ADM_POSITION admPosition) {

   // Read ADM potentiometer (Source)
   uint16_t adc = ADCReadAsValue(AN3_AIR_DIST_MOTOR);
   positionInfo->adcPositionSource = adc;
   positionInfo->adcRunningTime = 0;

   // Calculate target --->>

   // Set the ADC value for the new motor position
   positionInfo->adcPositionTarget = g_positionAdc[admPosition];

   // Where to move?   
   if (positionInfo->adcPositionTarget < positionInfo->adcPositionSource) {
      // Target position > Source, move Counter Clock
      positionInfo->admMove = ADM_MOVE_RIGHT;
   }
   else if (positionInfo->adcPositionTarget > positionInfo->adcPositionSource) {
      // Target position < Source, move Counterless Clock
      positionInfo->admMove = ADM_MOVE_LEFT;
   }      
   else {
      positionInfo->admMove = ADM_MOVE_NONE;
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
void ADMTask(pTASK task) {
   ADMStop();

   pADM_POSITION_INFO positionInfo = (pADM_POSITION_INFO) task->parameter;
   if (positionInfo == NULL) {
      return;
   }

   // Air Dist. Motor POTentiometer reading
   uint16_t ui16AdcPot = ADCReadAsValue(AN3_AIR_DIST_MOTOR);

   // Left or Right??
   int16_t i16Stop = 0;
   if (positionInfo->admMove == ADM_MOVE_LEFT) {
      i16Stop = positionInfo->adcPositionTarget - ui16AdcPot;
      ADMMoveLeft();
   }
   else {
      i16Stop = ui16AdcPot - positionInfo->adcPositionTarget;
      ADMMoveRight();
   }

   // If actual motor position +/- the new position or if time elapsed is more than 10secs 
   // this is an error "Emergency Stop!" :(
   // 2000=20s. 20s=(20s*1000ms)=20000ms/10ms=2000times, this check is called every N..ms times
   if (i16Stop <= ADM_ADC_OFFSET || (++positionInfo->adcRunningTime) >= ADM_MAX_TIME_MOVING) {
      ADMStop();
      task->status = TS_IDLE; 
   }

#if defined(DEBUG_ADM)
   sprintf(str, "ADM-Tsk. Src: [%d] Tgt: [%d] Pot: [%d]\n", positionInfo->adcPositionSource, positionInfo->adcPositionTarget, ui16AdcPot);
   USARTPrintString(str);
#endif
}
