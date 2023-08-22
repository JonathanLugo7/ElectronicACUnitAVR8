/*
 * TempSensor.c
 *
 * Created: 4/3/2017 4:03:39 a.m.
 *  Author: IoT SolucioneX
 */ 

//-- Includes --//
#include "tempSensor.h"
#include "rtos/tasks.h"
#include "ui/unit.h"
#include "hal/adc.h"


#if defined(DEBUG) || defined(DEBUG_TMPSNS)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Local functions implementation ---//

/* ***
   FUNCTION: float TSGetTemperatureBeta(uint16_t tsChannel, uint16_t fixedR0, uint16_t nominalR0, uint16_t Bcoefficient)
   DESCRIPTION: Calculate temperature from sensor input

   PARAMETERS: uint16_t tsChannel: ADC Sensor channel
               uint16_t fixedR0: Fixed NTC resistor
               uint16_t nominalR0: Nominal NTC resistor
               uint16_t Bcoefficient: Beta coefficient NTC fixed resistor
   RETURN: float: Temperature in Celsius degree
*** */
static float TSGetTemperatureBeta(uint16_t tsChannel, uint16_t fixedR0, uint16_t nominalR0, uint16_t Bcoefficient) {
   
   // Read NTC temp sensor from ADC channel
   uint16_t tsADC = ADCReadAsValue(tsChannel);

   // Get NTC read voltage as resistor
   // Equation. Rntc = FIXED_RESISTOR / ((1023/ADC) - 1)
   float Rntc = fixedR0 / ((ADC_RESOLUTION / tsADC) - 1);
   float fTemp = 0.0;
  
   fTemp = Rntc / nominalR0;                          // Rntc/R0
   fTemp = log(fTemp);                                // ln(Rntc/R0)
   fTemp /= Bcoefficient;                             // 1/B * ln(Rntc/R0) == ln(Rntc/R0)/B
   fTemp += 0.00335401643468052993459667952373f;      // 1/T0 + 1/B * ln(R/R0). 1/T0==1/(25+273.15)==1/298.15==0,00335402...
   fTemp = 1/fTemp;                                   // Inverse -> 1/T=1/T0+1/B*ln(R/R0) -> T = 1 / ( 1/T0 + 1/B*ln(R/R0) )
   fTemp -= 273.15;                                   // From Kelvin to Celsius

   return fTemp;
}


//--- Functions implementation ---//


/* ***
   FUNCTION: int8_t TSPassenger(void)
   DESCRIPTION: Read passenger compartment air temperature sensor

   PARAMETERS: void
   RETURN: uint8_t: Temperature in Celsius degrade. From: [-30°..50°] C / [-22°..122°] F
*** */
int8_t TSPassenger(void) {
   return (int8_t) TSGetTemperatureBeta(AN0_TEMP_SENS_PASSENGER, TS_PASSENGER_FIXED_R0, TS_PASSENGER_NOMINAL_R0_25C, TS_PASSENGER_B25_50);
}

/* ***
   FUNCTION: int8_t TSOutsideMirror(void)
   DESCRIPTION: Read outside mirror air temperature sensor

   PARAMETERS: void
   RETURN: uint8_t: Temperature in Celsius degrade. From: [-30°..50°] C / [-22°..122°] F
*** */
int8_t TSOutsideMirror(void) {
   return (int8_t) TSGetTemperatureBeta(AN1_TEMP_SENS_OUTSIDE, TS_OUTSIDE_FIXED_R0, TS_OUTSIDE_NOMINAL_R0_25C, TS_OUTSIDE_B25_50);
} 

/* ***
   FUNCTION: int8_t TSBottomBlended(void)
   DESCRIPTION: Read bottom blended air temperature sensor

   PARAMETERS: void
   RETURN: uint8_t: Temperature in Celsius degrade. From: [-30°..50°] C / [-22°..122°] F
*** */
int8_t TSBottomBlended(void) {
   return (int8_t) TSGetTemperatureBeta(AN2_TEMP_SENS_BOTTOM_BLENDED, TS_BTM_BLENDED_FIXED_R0, TS_BTM_BLENDED_NOMINAL_R0_25C, TS_BTM_BLENDED_B25_50);
}

/* ***
   FUNCTION: int8_t TSTopBlended(void)
   DESCRIPTION: Read top blended air temperature sensor

   PARAMETERS: void
   RETURN: uint8_t: Temperature in Celsius degrade. From: [-30°..50°] C / [-22°..122°] F
*** */
int8_t TSTopBlended(void) {
   return (int8_t) TSGetTemperatureBeta(AN5_TEMP_SENS_TOP_BLENDED, TS_TOP_BLENDED_FIXED_R0, TS_TOP_BLENDED_NOMINAL_R0_25C, TS_TOP_BLENDED_B25_50);
}

/* ***
   FUNCTION: int8_t TSElectronicSpeedRegulator(void)
   DESCRIPTION: Read electronic speed regulator built-in temperature sensor
                Not implemented!

   PARAMETERS: void
   RETURN: uint8_t: Temperature in Celsius degrade. From: [-30°..50°] C / [-22°..122°] F
*** */
int8_t TSElectronicSpeedRegulator(void) {
   return (int8_t) TSGetTemperatureBeta(AN4_TEMP_SENS_ELEC_SPEED_REG, 0, 0, 0);
}

/* ***
   FUNCTION: void TempSensorsTask(pTASK task)
   DESCRIPTION: Temperature sensors task
                Read Top, Bottom, Passenger and Outside mirror temperature sensors for automatic temperature controls

   PARAMETERS: pTASK task. UNIT_STATE model unit controller 
   RETURN: void
*** */
void TempSensorsTask(pTASK task) {
   // Get task parameter
   pTEMP_SENSORS_INFO pSensorInfo = (pTEMP_SENSORS_INFO) task->parameter;
   if (pSensorInfo == NULL) {
      return;
   }

   // Read NTC sensors
   pSensorInfo->Passenger = TSPassenger();
   pSensorInfo->OutsideMirror = TSOutsideMirror();
   pSensorInfo->BottomBlended = TSBottomBlended();
   pSensorInfo->TopBlended = TSTopBlended();

#if defined(DEBUG_TMPSNS)
    sprintf(str, "TMP_SENS-Task. Passgr: [%d] Outs Mirror: [%d] Bottom Blnd: [%d] Top Blnd: [%d]\n", pSensorInfo->Passenger, pSensorInfo->OutsideMirror, pSensorInfo->BottomBlended, pSensorInfo->TopBlended);
    USARTPrintString(str);
#endif
}

/* ***
   FUNCTION: void ExtTempTask(pTASK task)
   DESCRIPTION: Extern Temperature task
                Show extern temperature info when central unit is <OFF>

   PARAMETERS: pTASK task. UNIT_STATE model for automatic controller 
   RETURN: void
*** */
void ExtTempTask(pTASK task) {
   // Get task parameter
   pUNIT_STATE pUnitState = (pUNIT_STATE) task->parameter;
   if (pUnitState == NULL) {
      return;
   }

   // Stop Aperiodic task
   task->status = TS_IDLE;

   // SIGNAL: Extern Temperature display changed
   pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}
