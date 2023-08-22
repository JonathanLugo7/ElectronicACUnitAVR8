/*
 * ElectronicACUnitAVR8.c
 *
 * Created: 27/1/2017 12:41:17 a.m.
 *  Author: IoT SolucioneX
 */ 

//-- Includes --//
#include "main.h"
#include "HAL/board.h"
#include "rtos/timers.h"
#include "rtos/tasks.h"
#include "ui/unit.h"
#include "ui/unitUI.h"
#include "keypad/keypad.h"
#include "actuators/airDistMotor.h"
#include "actuators/threeLevelSwitch.h"
#include "actuators/elecSpeedReg.h"
#include "sensors/tempSensor.h"
#include "actuators/lamps.h"
#include "display/lcd.h"
#include "display/led.h"


#ifdef DEBUG_TASK
//#include "EEPROM/EEPROM_data.h"
#endif

#if defined DEBUG
#include "comms/usart.h"
char str[MAX_BUFFER];
#endif

//--- Tasks callback function prototype ---//
extern void KeypadTask(pTASK task);
extern void TempSensorsTask(pTASK task);
extern void ADMTask(pTASK task);
extern void ESRTask(pTASK task);
extern void ExtTempTask(pTASK task);


//--- MAIN task ---//
int main(void) {

   //--- Initialize Electronic A/A Unit ---//

   // Disable JTAG port. Fuse Disabled
   // MCUCSR |=(1<<JTD);
   // MCUCSR |=(1<<JTD);

   BoardInit();   // HAL module. Execute before calling any other HAL function, like USART, ADC, etc...

   /*** TEST PINs *

   // SET as output
   DDRA = 0xFF;
   DDRB = 0xFF;
   DDRC = 0xFF;
   DDRD = 0xFF;

   sprintf(str, "DDRA: [0x%02X] - DDRB: [0x%02X] - DDRC: [0x%02X] - DDRD: [0x%02X]\n", DDRA, DDRB, DDRC, DDRD);
   USARTPrintString(str);

   while (1) {
		PORTA = 0x00;	// LOW
		PORTB = 0x00;	// LOW
		PORTC = 0x00;	// LOW
		PORTD = 0x00;	// LOW
		sprintf(str, "Low. PORTA: [0x%02X] - PORTB: [0x%02X] - PORTC: [0x%02X] - PORTD: [0x%02X]\n", PORTA, PORTB, PORTC, PORTD);
		USARTPrintString(str);
		sprintf(str, "Low. PINA: [0x%02X] - PINB: [0x%02X] - PINC: [0x%02X] - PIND: [0x%02X]\n", PINA, PINB, PINC, PIND);
		USARTPrintString(str);
		_delay_ms(5000);

		PORTA = 0xFF;	// HIGH
		PORTB = 0xFF;	// HIGH
		PORTC = 0xFF;	// HIGH
		PORTD = 0xFF;	// HIGH

		sprintf(str, "High. PORTA: [0x%02X] - PORTB: [0x%02X] - PORTC: [0x%02X] - PORTD: [0x%02X]\n", PORTA, PORTB, PORTC, PORTD);
		USARTPrintString(str);
		sprintf(str, "High. PINA: [0x%02X] - PINB: [0x%02X] - PINC: [0x%02X] - PIND: [0x%02X]\n", PINA, PINB, PINC, PIND);
		USARTPrintString(str);
		_delay_ms(5000);
   }
   *** */

   TimerInit();   // Time counting and task scheduling module
   TaskInit();    // Tasks module

   // Unit controller and model setup
   UNIT_STATE           unitState;
   ADM_POSITION_INFO    admPosInfo;
   ESR_SPEED_INFO       esrSpeedInfo;
   TEMP_SENSORS_INFO    tempSensorsInfo;
   UnitInit(&unitState, &admPosInfo, &esrSpeedInfo, &tempSensorsInfo);

   // working variables
   KEY_ID key = KEYPAD_NO_KEY_PRESS;
   uint8_t esrSpeed = 0;
   tTime timer = TimerNow();

   // Create tasks (SIGNALed IDLE by default)
   tTaskId tskKey = TaskCreate("Keypad_Task", TimerNow(), TRE_HUNDRED_MSECOND, TT_PERIODIC, &KeypadTask, NULL);
   tTaskId tskTS = TaskCreate("TempSensors_Task", TimerNow(), TRE_ONE_SECOND, TT_PERIODIC, &TempSensorsTask, &tempSensorsInfo);
   tTaskId tskESR = TaskCreate("ElecSpeedReg_Task", TimerNow(), TRE_TEN_MSECOND, TT_APERIODIC, &ESRTask, &esrSpeedInfo);
   tTaskId tskADM = TaskCreate("AirDistMotor_Task", TimerNow(), TRE_TEN_MSECOND, TT_APERIODIC, &ADMTask, &admPosInfo);
   tTaskId tskExtTemp = TaskCreate("ExternTemp_Task",  TimerNow(), TRE_TEN_SECONDS, TT_APERIODIC, &ExtTempTask, &unitState);

   // Startup periodic tasks (Keypad, Temp Sensors, others...)
   TaskSetStatus(tskKey, TS_READY);
   TaskSetStatus(tskTS, TS_READY);

   // Set unit in last state mode
   UnitLastState(&unitState);

   // Prepare for SLEEP the CPU in power save mode
   set_sleep_mode(SLEEP_MODE_IDLE);

   // Enable global interrupt for scheduling
   sei();

   // main() loop task
   while (1) {

      // Process tasks and sleep if not more tasks active, if is possible :(
      RunScheduler();

      // Process the key press button that change the UI and set new operating mode
      key = KeypadGetLastKey();
      if (key != KEYPAD_NO_KEY_PRESS) {
         switch (key) {
            case KEY_OFF:
               UnitOff(&unitState);          //Process OFF key first
               break;
            case KEY_TEMP_MINUS:             //<| Temperature
               UnitTempDec(&unitState);
               break;
            case KEY_TEMP_PLUS:              //Temperature |>
               UnitTempInc(&unitState);
               break;
            case KEY_SPEED_MINUS:            //<| Speed
               UnitSpeedDec(&unitState);
               break;
            case KEY_SPEED_PLUS:             //Speed |>
               UnitSpeedInc(&unitState);
               break;
            case KEY_TEMP_EXTERN:            //Extern Temp. =|
               UnitExternTemp(&unitState);
               break;
            case KEY_AUTO:                   //Automatic A/A
               UnitAutomatic(&unitState);
               break;
            case KEY_ECONOMICS:              //Economics A/A
               UnitEconomic(&unitState);
               break;
            case KEY_RECIRCULATE:            //Recirculate A/A
               UnitRecirculate(&unitState);
               break;
            case KEY_WINDSHIELD:             //AirDistMotor: Windshield
               UnitAirDistMotor(&unitState, ADM_WINDSHIELD);
               break;
            case KEY_FRONT:                  //AirDistMotor: Front
               UnitAirDistMotor(&unitState, ADM_FRONT);
               break;
            case KEY_FRONT_FEET:             //AirDistMotor: Front+Feet
               UnitAirDistMotor(&unitState, ADM_FRONT_FEET);
               break;
            case KEY_FEET:                   //AirDistMotor: Feet
               UnitAirDistMotor(&unitState, ADM_FEET);
               break;
            default:
               break;
         }

         // Save modified unit state in EEPROM memory
         UnitSaveState(&unitState);
      }

      //--- Main unit controller task ---//

      // Update UI?
      if (unitState.flags.fUI) {
         unitState.flags.fUI = UNIT_FLAG_OFF;

         #ifdef DEBUG
            // Send unit state data for SignalR debug application
            sprintf(str, "US|%d|%d|%d|%d|%d|%d|%d|%d|\n", unitState.Status,
                                                          unitState.Auto,
                                                          unitState.Economic,
                                                          unitState.Recirculate,
                                                          unitState.AirDistMotor,
                                                          unitState.SelectedTemp,
                                                          unitState.Speed,
                                                          unitState.flags.fExtTemp);
            USARTPrintString(str);
         #endif

         // Display extern temperature for about 10 seconds
         if (unitState.flags.fExtTemp) {
            TaskSetStatus(tskExtTemp, TS_READY);
         }

         // If Air Dist. Motor position changed
         if (unitState.flags.fAirDistMotor) {
            unitState.flags.fAirDistMotor = UNIT_FLAG_OFF;

            ADMUpdatePositionInfo(&admPosInfo, unitState.AirDistMotor);
            if (admPosInfo.admMove) {
               TaskSetStatus(tskADM, TS_READY);
            }
         }

         // Blower speed changed. Turn on/off the electronic speed regulator?
         if (unitState.flags.fSpeed) {
            unitState.flags.fSpeed = UNIT_FLAG_OFF;
            
            esrSpeed = (unitState.Speed * 2) - 1;  // Adjust for speed lookup table. See elecSpeedReg.c
            if (unitState.Status == US_OFF) {
               esrSpeed = 0;  //Off
            }

            ESRUpdateSpeedInfo(&esrSpeedInfo, esrSpeed);
            if (esrSpeedInfo.esrMove) {
               TaskSetTimers(tskESR, TimerNow() + TRE_ONE_SECOND, 0);   //Run in the next 1s. Wait while user end setting new speed
               TaskSetStatus(tskESR, TS_READY);
            }
         }
         
         // Turn off compressor pulley
         if (unitState.Status == US_OFF) {
            unitState.ThreeLevelSwitch = TLPSS_OFF;
            TLPSSetState(TLPSS_OFF);
         }

         // Change UI
         UnitUIUpdate(&unitState, &tempSensorsInfo);
      }

      // Check normal working operation every 2 seconds
      if (TimerElapsed(timer) >= TRE_TWO_SECONDS) {

         if (unitState.Status == US_ON) {
            
            // Unit:OFF or ECONomics:ON or passenger temperature below selected temperature
            if ((unitState.Economic) || (tempSensorsInfo.Passenger < unitState.SelectedTemp)) {
               unitState.ThreeLevelSwitch = TLPSS_OFF;
            }
            else {
               unitState.ThreeLevelSwitch = TLPSS_ON;
            }

            // Compressor Pulley
            TLPSSetState(unitState.ThreeLevelSwitch);

            // If we are in AUTOmatic mode control automatic blower speed
            if (unitState.Auto) {
               esrSpeed = (tempSensorsInfo.Passenger - 18) + 1;  // Adjust for speed lookup table. See elecSpeedReg.c

               // Check index range. The unit is limit for operating temperature from 18 to 32 Celsius degree, lower or higher
               // temps. are show as LO/HI respectively, but temps. sensor still sense this, because of that we need validate
               // out of range values for lookup table. 
               // Example: Lower temp. tempSensorsInfo.Passenger = 16. esrSpeed = (16 - 18) + 1 = -1
               // Example: Higher temp. tempSensorsInfo.Passenger = 33. esrSpeed = (33 - 18) + 1 = 16
               if (esrSpeed <= 0) {
                  esrSpeed = ESR_SPEED_1;    //Set min. speed
               }

               if (esrSpeed >= ESR_MAX_SPEED) {
                  esrSpeed = ESR_SPEED_15;   //Set max. speed
               }

               ESRUpdateSpeedInfo(&esrSpeedInfo, esrSpeed);
               if (esrSpeedInfo.esrMove) {
                  TaskSetTimers(tskESR, TimerNow() + TRE_ONE_SECOND, 0);   //Run in the next 1s. Wait while user end setting new speed
                  TaskSetStatus(tskESR, TS_READY);
               }
            }
         }

         #ifdef DEBUG
            // Get voltage regulator info
            float fVref = ADCReadAsVoltage(AN6_L4947_VOLTAGE_REG);
            char strVref[6];
            
            // Transform Vref to string (like stdlib atof())
            dtostrf(fVref, 2, 3, strVref);

            // Send operation state data for SignalR debug application
            sprintf(str, "OS|%s|%d|%d|%d|%d|%d|\n", strVref,
                                                    unitState.ThreeLevelSwitch,
                                                    tempSensorsInfo.OutsideMirror,
                                                    tempSensorsInfo.Passenger,
                                                    tempSensorsInfo.TopBlended,
                                                    tempSensorsInfo.BottomBlended);
             USARTPrintString(str);
         #endif

         // Reload timer trigger
         timer = TimerNow();
      }
      
      // Save some power      
      cli();
      sleep_enable();
      sei();
      sleep_cpu();      // Goto Sleep CPU, Mimimimimimi!
      sleep_disable();
      sei();

   } // END while() {}
}
