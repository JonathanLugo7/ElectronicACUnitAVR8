/*
 * EEPROM_data.c
 *
 * Created: 10/2/2017 1:08:30 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

//-- Includes --//
#include "EEPROM_data.h"
#include "EEPROM_fncs.h"
#include "EEPROM_address.h"

#ifdef DEBUG_TASK
#include "comms/usart.h"
static char str[MAX_BUFFER];
#endif

//--- DEBUG_TASK Only Functions Body ---//

//
//This file is just for create the EEPROM .eep data file. This data is used for the application 
//to control the UI and do the Thermistor R/T Calculators. The first 5 bytes are the default values 
//from starting from nothing, the next 5 bytes are the working state saving every time the Unit go Off
//and the rest are the Steinhart-Hart coefficients A, B and C for the Outside Mirror, Passenger 
//Compartment and Top/Bottom blend air NTC sensors
//

#define CREATE_EEPROM
#undef CREATE_EEPROM
#ifdef CREATE_EEPROM


//////////////////////////////////////////////////////////////////////////
// Electronic Speed Regulator Timer OCR2x values for PWM speed controller
//
// Dec. 255: 100% PMW Duty Cycle - FULL Speed
// AUTOmatic intermediate speed
// Dec. 230:  90% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec. 204:  80% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec. 179:  70% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec. 253:  60% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec. 128:  50% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec. 102:  40% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec.  77:  30% PMW Duty Cycle
// AUTOmatic intermediate speed
// Dec.   0:   0% PMW Duty Cycle - STOP
//////////////////////////////////////////////////////////////////////////
uint8_t EEMEM esrSpeed15 = 0xFF;                 //Dec.: 255. EEPROM Address: (0x28). SPEED 8
uint8_t EEMEM esrSpeed14 = 0xF5;                 //Dec.: 245. EEPROM Address: (0x27)
uint8_t EEMEM esrSpeed13 = 0xEB;                 //Dec.: 235. EEPROM Address: (0x26). SPEED 7
uint8_t EEMEM esrSpeed12 = 0xE1;                 //Dec.: 225. EEPROM Address: (0x25)
uint8_t EEMEM esrSpeed11 = 0xD8;                 //Dec.: 216. EEPROM Address: (0x24). SPEED 6
uint8_t EEMEM esrSpeed10 = 0xCE;                 //Dec.: 206. EEPROM Address: (0x23)
uint8_t EEMEM esrSpeed9  = 0xC4;                 //Dec.: 196. EEPROM Address: (0x22). SPEED 7
uint8_t EEMEM esrSpeed8  = 0xBA;                 //Dec.: 186. EEPROM Address: (0x21)
uint8_t EEMEM esrSpeed7  = 0xB1;                 //Dec.: 177. EEPROM Address: (0x20). SPEED 4
uint8_t EEMEM esrSpeed6  = 0xA7;                 //Dec.: 167. EEPROM Address: (0x1F)
uint8_t EEMEM esrSpeed5  = 0x9E;                 //Dec.: 158. EEPROM Address: (0x1E). SPEED 3
uint8_t EEMEM esrSpeed4  = 0x94;                 //Dec.: 148. EEPROM Address: (0x1D)
uint8_t EEMEM esrSpeed3  = 0x8A;                 //Dec.: 138. EEPROM Address: (0x1C). SPEED 2
uint8_t EEMEM esrSpeed2  = 0x77;                 //Dec.: 119. EEPROM Address: (0x1B)
uint8_t EEMEM esrSpeed1  = 0x64;                 //Dec.: 100. EEPROM Address: (0x1A). SPEED 1


//////////////////////////////////////////////////////////////////////////
// Air Dist. Motor Potentiometer values for Motor Position
//////////////////////////////////////////////////////////////////////////
uint16_t EEMEM admWndShield = 870;              //                       (0x18)
uint16_t EEMEM admFeet = 590;                   //                       (0x16)
uint16_t EEMEM admFrontFeet = 375;              //                       (0x14)
uint16_t EEMEM admFront = 170;                  //                       (0x12)

uint8_t EEMEM LastStateWrk = 0x00;              //                       (0x11)
uint8_t EEMEM SpeedWrk = 0x06;                  //                       (0x10)
uint8_t EEMEM TempWrk = 0x22;                   //                       (0x0F)
uint8_t EEMEM AirIntakeMotorWrk = 0x00;         //                       (0x0E)
uint8_t EEMEM CockBlendMotorWrk = 0x00;         //                       (0x0D)
uint8_t EEMEM AirDistMotorWrk = 0x00;           //                       (0x0C)
uint8_t EEMEM RecirculateWrk = 0x01;            //                       (0x0B)
uint8_t EEMEM EconomicWrk = 0x00;               //                       (0x0A)
uint8_t EEMEM AutoWrk = 0x01;                   //                       (0x09)

//////////////////////////////////////////////////////////////////////////
// LastStatus==UNIT_STATUS_OFF.  See unit.h for valid values
// Speed==UNIT_SPEED_4.          See unit.h for valid values
// Temp==UNIT_TEMP_24C.          See unit.h for valid values
// AirIntakeMotor==0x00.         No implemented
// CockBlendMotor==0x00.         No implemented
// AirDistMotor==ADM_FRONT.      See adm.h for valid values 
// Recirculate==UNIT_RECI_ON.    See unit.h for valid values
// Economic==UNIT_ECON_OFF.      See unit.h for valid values
// Auto==UNIT_AUTO_ON.           See unit.h for valid values
//////////////////////////////////////////////////////////////////////////

uint8_t EEMEM LastState  = 0x00;                //                       (0x08)
uint8_t EEMEM Speed = 0x04;                     //                       (0x07)
uint8_t EEMEM Temp = 0x18;                      //                       (0x06)
uint8_t EEMEM AirIntakeMotor = 0x00;            //                       (0x05)
uint8_t EEMEM CockBlendMotor = 0x00;            //                       (0x04)
uint8_t EEMEM AirDistMotor = 0x00;              //                       (0x03)
uint8_t EEMEM Recirculate = 0x01;               //                       (0x02)
uint8_t EEMEM Economic = 0x00;                  //                       (0x01) 
uint8_t EEMEM Auto = 0x01;                      // |First EEPROM Address (0x00) ^

//New values from here, down to up...


#endif //CREATE_EEPROM

#ifdef DEBUG_EEPROM

void EEPROMSaveDefaultData(void) {
   //This is the default UnitState for AUTOmatic unit function. 
   //This values are load in UNIT_STATE struct from the EEPROM data. EEPROM address: 8:0
   EEPROMWrite_byte(EEADDRSS_US_AUTOMATIC, 0x01);             //0x01: AUTO=On
   EEPROMWrite_byte(EEADDRSS_US_ECONOMIC, 0x00);              //0x00: ECON=Off
   EEPROMWrite_byte(EEADDRSS_US_RECIRCULATE, 0x01);           //0x01: RECI=On
   EEPROMWrite_byte(EEADDRSS_US_AIR_DIST_MOTOR, 0x08);        //0x08: Air Distribution Motor FRONT position
   EEPROMWrite_byte(EEADDRSS_US_COCK_BLEND_MOTOR, 0x00);      //0x00: Cock&Blender Motor CLOSED position (No implemented)
   EEPROMWrite_byte(EEADDRSS_US_AIR_INTAKE_MOTOR, 0x00);      //0x00: Air intake motor CLSED position (No implemented)
   EEPROMWrite_byte(EEADDRSS_US_TEMPERATURE, 0x18);           //0x18: 24 �C Temperature
   EEPROMWrite_byte(EEADDRSS_US_SPEED, 0x03);                 //0x03: Air fan motor 2nd Speed
   EEPROMWrite_byte(EEADDRSS_US_LAST_STATE, 0x00);            //0x00: Last status. 0:OFF, 1:ON, ...

   //This is the working UnitState, is save when unit go off. EEPROM address: 17:9
   EEPROMWrite_byte(EEADDRSS_US_AUTOMATIC_WRK, 0x00);         //0x00: AUTO=Off
   EEPROMWrite_byte(EEADDRSS_US_ECONOMIC_WRK, 0x00);          //0x00: ECON=Off
   EEPROMWrite_byte(EEADDRSS_US_RECIRCULATE_WRK, 0x00);       //0x00: RECI=Off
   EEPROMWrite_byte(EEADDRSS_US_AIR_DIST_MOTOR_WRK, 0x00);    //0x00: Air Distribution Motor FRONT position
   EEPROMWrite_byte(EEADDRSS_US_COCK_BLEND_MOTOR_WRK, 0x00);  //0x00: Cock&Blender Motor CLOSED position (No implemented)
   EEPROMWrite_byte(EEADDRSS_US_AIR_INTAKE_MOTOR_WRK, 0x00);  //0x00: Air intake motor CLSED position (No implemented)
   EEPROMWrite_byte(EEADDRSS_US_TEMPERATURE_WRK, 0x00);       //0x00: 24 �C Temperature
   EEPROMWrite_byte(EEADDRSS_US_SPEED_WRK, 0x00);             //0x00: Air fan motor 2nd Speed
   EEPROMWrite_byte(EEADDRSS_US_LAST_STATE_WRK, 0x00);        //0x00: Last status. 0:OFF, 1:ON, ...
   
   //Potentiometer values for reading the Air Distribution Motor position
   EEPROMWrite_word(EEADDRSS_ADM_ADC_FRONT, 0x006E);           //Dec. 110: Position   A=0�
   EEPROMWrite_word(EEADDRSS_ADM_ADC_FRONT_FEET, 0x0177);      //Dec. 375: Position A-B=60�
   EEPROMWrite_word(EEADDRSS_ADM_ADC_FEET, 0x0253);            //Dec. 595: Position A-C=113� +/-1
   EEPROMWrite_word(EEADDRSS_ADM_ADC_WINDSHLD, 0x0393);        //Dec. 915: Position A-D=185�

   //This is the OCR2x values for the PWM %DutyCycle
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED1, 0x10);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED2, 0x20);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED3, 0x30);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED4, 0x40);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED5, 0x50);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED6, 0x60);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED7, 0x70);    //
   EEPROMWrite_byte(EEADDRSS_ESR_SPEED8, 0xFF);    //Dec. 256: 100%
}

void EEPROMPrint(void)
{
   USARTPrintString("\n\nEEPROM [\n");

   uint8_t byte;
   for (uint16_t i = 0 ; i < E2END; i++) {
      byte = eeprom_read_byte((uint8_t *) i);

      sprintf(str, "0x%0X ", byte);
      USARTPrintString(str);

      if (i > 1 && 0 == i % 20) {
         USARTPrintString("\n");
      }
   }

   USARTPrintString("\n]\n");
}

#endif