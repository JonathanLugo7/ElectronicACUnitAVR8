/*
 * CentralitaUI.c
 *
 * Created: 7/12/2016 1:55:59 a.m.
 *  Author: IoT SolucioneX
 */ 

#include "unitUI.h"
#include "display/led.h"
#include "display/lcd.h"
#include "actuators/lamps.h"


//--- Globals local variables ---//


//--- Local functions ---//


/* ***
   FUNCTION: static void UIUpdateLCD(void)
   DESCRIPTION: Display LCD info on the physical layer

   PARAMETERS: void
   RETURN: void
*** */
static void updateLCD(pUNIT_UI pUI) {
   LCDSendData(pUI->LCDDigit1,        // byte1=S8:1
               pUI->LCDDigit2,        // byte2=S16:9
               pUI->LCDSymbols,       // byte3=S24:17
               pUI->LCDSpeed);        // byte4=S32:25 
}

/* ***
   FUNCTION: static void UIUpdateLED(void)
   DESCRIPTION: Display LED info on the physical layer

   PARAMETERS: void
   RETURN: void
*** */
static void updateLED(pUNIT_UI pUI) {
   LEDSendData(pUI->LEDStatus,        // byte1=LED4:1
               pUI->LEDAirDistMotor,  // byte2=LED8:5
               pUI->LEDOn,            // byte3=LED12:9
               pUI->LEDDummy);        // byte4=LED14:13. Dummy byte
}

static void updateRoomTemp(pUNIT_UI pUI, uint8_t temp) {
   // Clean extern temperature symbols
   pUI->LCDSymbols &= ~(LCD_EXT | LCD_MINUS | LCD_HUNDREDS);

   // Show 'LO' or 'HI' message. (Right->Left)
   if (temp == UNIT_TEMP_LOW) {
      pUI->LCDDigit2 = LCD_L; pUI->LCDDigit1 = LCD_O;
   }
   else if (temp == UNIT_TEMP_HIGH) {
      pUI->LCDDigit2 = LCD_H; pUI->LCDDigit1 = LCD_I;
   }
   else {
      // Get DIGIT2:1 from selected temperature
      // Example formula: 43928 / 10000 = 4; 43928 % 10000 = 3928; 3928 /1000 = 3; 3928 %1000 = 928, etc...

      // Convert room temp to LCD digits
      pUI->LCDDigit2 = LCDNumberToDigit(temp / 10);  // Get Tens, only integer part
      pUI->LCDDigit1 = LCDNumberToDigit(temp % 10);  // Get Ones, is the rest from the MOD operation
   }
}

static void updateExternTemp(pUNIT_UI pUI, int8_t temp) {
   // Clean extern temperature symbols
   pUI->LCDSymbols &= ~(LCD_MINUS | LCD_HUNDREDS);
   pUI->LCDSymbols |= LCD_EXT;

   // Minus is special symbol
   if (temp < 0) {
      pUI->LCDSymbols |= LCD_MINUS;
      temp *= -1;
   }

   // Hundred is special symbol, truncate temp last two digits
   if (temp >= 100) {
      pUI->LCDSymbols |= LCD_HUNDREDS;
      temp %= 100;
   }

   // Convert outside mirror temp to LCD digits
   pUI->LCDDigit2 = LCDNumberToDigit(temp / 10);  // Get Tens, only integer part
   pUI->LCDDigit1 = LCDNumberToDigit(temp % 10);  // Get Ones, is the rest from the MOD operation
}


//--- API Implementation ---//


//--- UI Status functions ---//

/* ***
   FUNCTION: UIUpdate()
   DESCRIPTION: Update LEDs and LCD Display for UI interaction

   PARAMETERS: void
   RETURN: void
*** */
void UnitUIUpdate(pUNIT_STATE pUnitState, pTEMP_SENSORS_INFO pTempSensors)
{
   // Fresh canvas
   UNIT_UI ui;
   memset(&ui, 0, sizeof(UNIT_UI));

   LEDClear();
   LCDClear();

   // <-Unit status <ON> info->
   if (pUnitState->Status == US_ON) {
      // Display fixed LED and LCD symbols
      ui.LEDOn = LED_ON;
      ui.LCDSymbols = LCD_SPEED_SEP;

      // Turn off <OFF> LED
      ui.LEDStatus &= ~LED_OFF;

      // ->AUTOmatics On?
      ui.LCDSymbols &= ~(LCD_MANUAL | LCD_AUTO);
      if (pUnitState->Auto == UNIT_AUTO_ON) {
         ui.LEDStatus  |= LED_AUTO;       // Set on 'AUTO' LED (LED 1)
         ui.LCDSymbols |= LCD_AUTO;   
      }
      else {
         ui.LEDStatus  &= ~LED_AUTO;
         ui.LCDSymbols |= LCD_MANUAL;
      }   

      // ->ECOnomics On?
      ui.LEDStatus &= ~LED_ECONOMICS;   
      if (pUnitState->Economic == UNIT_ECON_ON) {
         ui.LEDStatus |= LED_ECONOMICS;  // Set on 'ECO' LED (LED 2)
      }

      // ->RECirculate On?
      ui.LEDStatus &= ~LED_RECIRCULATE;
      if (pUnitState->Recirculate == UNIT_RECI_ON) {
         ui.LEDStatus |= LED_RECIRCULATE; // Set on 'RECI' LED (LED 3)
      }

      // ->Air Distribution Motor Position info
      if (pUnitState->AirDistMotor == ADM_WINDSHIELD) {
         ui.LEDAirDistMotor = LED_WINDSHIELD;     // Set on LED WINDSHIELD (LED 5)
      }

      if (pUnitState->AirDistMotor == ADM_FRONT) {
         ui.LEDAirDistMotor = LED_FRONT;          // Set on LED FRONT (LED 6)
      }

      if (pUnitState->AirDistMotor== ADM_FRONT_FEET) {
         ui.LEDAirDistMotor = LED_FRONT_FEET;     // Set on LED FRONT/FEET (LED 7)
      }

      if (pUnitState->AirDistMotor == ADM_FEET) {
         ui.LEDAirDistMotor = LED_FEET;           // Set on LED FEET (LED 8)
      }
      
      // See lcd.h for speed display definition. LCD speed display = (2^Speed) - 1  
      ui.LCDSpeed =  ((1 << pUnitState->Speed) - 1);

      // Show Extern Temperature?
      if (pUnitState->flags.fExtTemp) {
         updateExternTemp(&ui, pTempSensors->OutsideMirror);
         pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;
      }
      else {
         updateRoomTemp(&ui, pUnitState->SelectedTemp);
      }

      // Update physic UI
      updateLED(&ui);
      updateLCD(&ui);

      // Set on LCD Temp and Speed display lamps
      LampsSetState(LAMP_TEMPERATURE_ON | LAMP_SPEED_ON);
   }
   else {   // Status <OFF>
      ui.LEDStatus |= LED_OFF;
      updateLED(&ui);

      // When unit is off and Extern Temp. is selected, show temperature info for 10s
      if (pUnitState->flags.fExtTemp) {
         pUnitState->flags.fExtTemp = UNIT_FLAG_OFF;

         updateExternTemp(&ui, pTempSensors->OutsideMirror);
         LampsSetState(LAMP_TEMPERATURE_ON);
         updateLCD(&ui);
      }
      else {
         LampsSetState(LAMP_TEMPERATURE_OFF | LAMP_SPEED_OFF);
      }
   }
}
