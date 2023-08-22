/*
 * UnitModel.c
 *
 * Created: 24/10/2017 12:49:20 a.m.
 *  Author: IoT SolucioneX
 */ 

#include "unit.h"
#include "EEPROM/EEPROM_fncs.h"
#include "EEPROM/EEPROM_address.h"

#if defined DEBUG_TASK
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif

//--- Globals local variables ---//


//--- API Implementation ---//

/* ***
   FUNCTION: void UnitInit(void)
   DESCRIPTION: Initialize Unit controller data. This function load from EEPROM memory the
                last unit operating state

   PARAMETERS: void
   RETURN: void
*** */
void UnitInit(pUNIT_STATE pUnitState, pADM_POSITION_INFO pPosInfo, 
              pESR_SPEED_INFO pSpeedInfo, pTEMP_SENSORS_INFO pSensorInfo) {
   
   // Initialize data structures 
   memset(pUnitState, 0, sizeof(UNIT_STATE));
   memset(pPosInfo, 0, sizeof(ADM_POSITION_INFO));
   memset(pSpeedInfo, 0, sizeof(ESR_SPEED_INFO));
   memset(pSensorInfo, 0, sizeof(TEMP_SENSORS_INFO));

   // Unit resetting
   pUnitState->Status = US_RESET;

   // Load unit last state from EEPROM data. From AUTOmatic or Working last state
   pUnitState->Auto = EEPROMRead_byte(EEADDRSS_US_AUTOMATIC_WRK);
   pUnitState->Economic = EEPROMRead_byte(EEADDRSS_US_ECONOMIC_WRK);
   pUnitState->Recirculate = EEPROMRead_byte(EEADDRSS_US_RECIRCULATE_WRK);
   pUnitState->AirDistMotor = EEPROMRead_byte(EEADDRSS_US_AIR_DIST_MOTOR_WRK);
   pUnitState->SelectedTemp = EEPROMRead_byte(EEADDRSS_US_TEMPERATURE_WRK);
   pUnitState->Speed = EEPROMRead_byte(EEADDRSS_US_SPEED_WRK);

   // Not implemented yet!
   //pUnitState->CockBlendMotor = EEPROMRead_byte(EEADDRSS_US_COCK_BLEND_MOTOR_WRK);
   //pUnitState->AirIntakeMotor = EEPROMRead_byte(EEADDRSS_US_AIR_INTAKE_MOTOR_WRK);
}

/* ***
   FUNCTION: void UnitSaveState(pUNIT_STATE pUnitState)
   DESCRIPTION: This function save to EEPROM memory the last unit operating state

   PARAMETERS: pUNIT_STATE
   RETURN: void
*** */
void UnitSaveState(pUNIT_STATE pUnitState) {

   // This is unit dirty state
   EEPROMWrite_byte(EEADDRSS_US_LAST_STATE_WRK, pUnitState->Status);

   // Last operating unit state
   EEPROMWrite_byte(EEADDRSS_US_AUTOMATIC_WRK, pUnitState->Auto);
   EEPROMWrite_byte(EEADDRSS_US_ECONOMIC_WRK, pUnitState->Economic);
   EEPROMWrite_byte(EEADDRSS_US_RECIRCULATE_WRK, pUnitState->Recirculate);
   EEPROMWrite_byte(EEADDRSS_US_TEMPERATURE_WRK, pUnitState->SelectedTemp);
   EEPROMWrite_byte(EEADDRSS_US_SPEED_WRK, pUnitState->Speed);
   EEPROMWrite_byte(EEADDRSS_US_AIR_DIST_MOTOR_WRK, pUnitState->AirDistMotor);
}

/* ***
   FUNCTION: void UnitLastState(pUNIT_STATE pUnitState)
   DESCRIPTION: Setup unit to the last operating state

   PARAMETERS: pUNIT_STATE
   RETURN: void
*** */
void UnitLastState(pUNIT_STATE pUnitState) {

   // Read last state saved
   uint8_t lastState = EEPROMRead_byte(EEADDRSS_US_LAST_STATE_WRK);

   // If last state is ON, mean that ignition key was turned from MAR to STOP without pressing unit OFF button
   if (lastState == US_ON) {      
      pUnitState->Status = US_ON;   // Turn unit On

      // SIGNAL: Update Electronic Speed Regulator (Blower Speed)
      pUnitState->flags.fSpeed = UNIT_FLAG_ON;
      
      // SIGNAL: Update Air Dist. Motor position
      pUnitState->flags.fAirDistMotor = UNIT_FLAG_ON;
   }
   else { 
      pUnitState->Status = US_OFF;
   }

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitOff(void) 
   DESCRIPTION: Set off A/A Unit state

   PARAMETERS: void
   RETURN: void
*** */
void UnitOff(pUNIT_STATE pUnitState) {

   if (pUnitState->Status == US_ON) {
      pUnitState->Status = US_OFF;

      // SIGNAL: Unit controller state changed
      pUnitState->flags.fPassengerTemp = UNIT_FLAG_OFF;     //No temperature display
      pUnitState->flags.fAirDistMotor = UNIT_FLAG_OFF;      //ADM No move
      pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;           //No extern temperature display
      pUnitState->flags.fSpeed = UNIT_FLAG_ON;              //Shutdown electronic speed regulator
   }

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitAutomatic(void)
   DESCRIPTION: Change to AUTOmatic mode

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitAutomatic(pUNIT_STATE pUnitState) {
   
   // If previous status was on, toggle
   if (pUnitState->Status == US_ON) {
      pUnitState->Auto ^= (1 | pUnitState->Auto);
   }

   // Is AUTOmatic pUnitState? then, set AUTOmatic mode
   if (pUnitState->Auto) {
      pUnitState->Economic = EEPROMRead_byte(EEADDRSS_US_ECONOMIC);
      pUnitState->Recirculate = EEPROMRead_byte(EEADDRSS_US_RECIRCULATE);
      pUnitState->AirDistMotor = EEPROMRead_byte(EEADDRSS_US_AIR_DIST_MOTOR);
      pUnitState->SelectedTemp = EEPROMRead_byte(EEADDRSS_US_TEMPERATURE);
      pUnitState->Speed = EEPROMRead_byte(EEADDRSS_US_SPEED);

      //Not implemented yet!
      //pUnitState->CockBlendMotor = EEPROMRead_byte(EEADDRSS_US_COCK_BLEND_MOTOR); //Automatic function contolled by speed/temperature
      //pUnitState->AirIntakeMotor = EEPROMRead_byte(EEADDRSS_US_AIR_INTAKE_MOTOR); //Controlled by recirculate button and speed/temperature

      //SIGNAL: Air Distribution Motor position
      pUnitState->flags.fAirDistMotor = UNIT_FLAG_ON;
      pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;
   }

   //SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;
   
   //SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitEconomic(void)
   DESCRIPTION: Change to ECOnomics mode

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitEconomic(pUNIT_STATE pUnitState) {   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;
   
   // If previous status was on, toggle
   if (pUnitState->Status == US_ON) {
      pUnitState->Economic ^= (1 | pUnitState->Economic);
   }      
   else {
      pUnitState->Economic = UNIT_ECON_ON;
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;
   
   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitRecirculate(void)
   DESCRIPTION: Change to RECIRculate mode

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitRecirculate(pUNIT_STATE pUnitState) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;
   
   // If previous status was on, toggle
   if (pUnitState->Status == US_ON) {
      pUnitState->Recirculate ^= (1 | pUnitState->Recirculate);
   }
   else {
      pUnitState->Recirculate = UNIT_RECI_ON;
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitTempInc(void)
   DESCRIPTION: Increment passenger compartment temperature one unit 

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitTempInc(pUNIT_STATE pUnitState) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;
   
   // If previous status was on change temp
   if (pUnitState->Status == US_ON) {
      if (++pUnitState->SelectedTemp > UNIT_TEMP_HIGH) {
         pUnitState->SelectedTemp = UNIT_TEMP_HIGH;
      }

      // SIGNAL: Passenger Temperature changed
      pUnitState->flags.fPassengerTemp = UNIT_FLAG_ON;
      pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitTempDec(void)
   DESCRIPTION: Decrement passenger compartment temperature one unit 

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitTempDec(pUNIT_STATE pUnitState) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;
   
   // If previous status was on change temp
   if (pUnitState->Status == US_ON) {
      if (--pUnitState->SelectedTemp < UNIT_TEMP_LOW) {
         pUnitState->SelectedTemp = UNIT_TEMP_LOW;
      }

      // SIGNAL: Passenger Temperature changed
      pUnitState->flags.fPassengerTemp = UNIT_FLAG_ON;
      pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitExternTemp(void)
   DESCRIPTION: Show extern temperature info

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitExternTemp(pUNIT_STATE pUnitState) {
   
   pUnitState->flags.fExtTemp ^= (1 | pUnitState->flags.fExtTemp);

   //SIGNAL: Extern Temperature display
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitSpeedInc(void) 
   DESCRIPTION: Increment passenger compartment fan speed one unit. 
                Example: Actual Speed = 0b0000-0001 (0x01)
                         New Speed = 0b0000-0001 (0x01) << 1 = 0b0000-0010 (0x02)
                         New Speed = 0b0000-0010 (0x02) + 1 = 0b0000-0011 (0x03)

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitSpeedInc(pUNIT_STATE pUnitState) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;

   // If previous status was on change speed
   if (pUnitState->Status == US_ON) {
      if (pUnitState->Speed < ESR_SPEED_8) {
         pUnitState->Speed++;
      }
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitSpeedDec(void)
   DESCRIPTION: Decrement passenger compartment fan speed one unit. 
                Example: Actual Speed = 0b0000-0011 (0x03)
                         New Speed = 0b0000-0011 (0x03) >> 1 = 0b0000-0001 (0x01)

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
   RETURN: void
*** */
void UnitSpeedDec(pUNIT_STATE pUnitState) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;

   // If previous status was on change speed
   if (pUnitState->Status == US_ON) {
      if (pUnitState->Speed > ESR_SPEED_1) {
         pUnitState->Speed--;
      }
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}

/* ***
   FUNCTION: void UnitAirDistMotor(ADM_POSITION admPosition)
   DESCRIPTION: Set the Air Distribution Motor new position

   PARAMETERS: pUNIT_STATE pUnitState. Unit state
               uint8_t admPosition. ADM-Position = KEY_ADM-Position
                                    Example: ADM_FEET == KEY_FEET
   RETURN: void
*** */
void UnitAirDistMotor(pUNIT_STATE pUnitState, ADM_POSITION admPosition) {
   
   // Set AUTOmatic off
   pUnitState->Auto = UNIT_AUTO_OFF;
   
   if (pUnitState->AirDistMotor != admPosition) {
      pUnitState->AirDistMotor = admPosition;

      // SIGNAL: Air Distribution Motor position changed
      pUnitState->flags.fAirDistMotor = UNIT_FLAG_ON;
   }

   // SIGNAL: Unit controller state changed
   pUnitState->Status = US_ON;
   pUnitState->flags.fSpeed = UNIT_FLAG_ON;

   // SIGNAL: Update User Interface
   pUnitState->flags.fUI = UNIT_FLAG_ON;
}
