/*
 * UnitModel.h
 *
 * Created: 24/10/2017 12:49:05 a.m.
 *  Author: IoT SolucioneX
 */ 

#ifndef UNIT_H_
#define UNIT_H_

// -------- Includes --------- //
#include "HAL/config.h"
#include "actuators/airDistMotor.h"
#include "actuators/elecSpeedReg.h"
#include "actuators/threeLevelSwitch.h"


// -------- Defines --------- //

// Unit controller status
typedef enum tagUNIT_STATUS { 
   US_OFF = 0,
   US_ON = 1,
   US_RUNNING = 2,
   US_PREV_ON = 3,
   US_PREV_OFF = 4,
   US_RESET = 5
} UNIT_STATUS;

#define UNIT_AUTO_OFF         0x00     // A/C AUTOmatic On/Off
#define UNIT_AUTO_ON          0x01     //
#define UNIT_ECON_OFF         0x00     // A/C Economics On/Off
#define UNIT_ECON_ON          0x01     //
#define UNIT_RECI_OFF         0x00     // A/C Recirculating On/Off
#define UNIT_RECI_ON          0x01     //
#define UNIT_ADM_MOVE_OFF     0x00     // Air Dist. Motor move On/Off
#define UNIT_ADM_MOVE_ON      0x01     //

// Unit flags states
#define UNIT_FLAG_OFF         0x00
#define UNIT_FLAG_ON          0x01

// Temperature display.                Temperature in Celsius degree
#define UNIT_TEMP_LOW         0x11  // 17  LO Temperature < 18°C
#define UNIT_TEMP_18C         0x12  // 18  18°C
#define UNIT_TEMP_19C         0x13  // 19  19°C
#define UNIT_TEMP_20C         0x14  // 20  20°C
#define UNIT_TEMP_21C         0x15  // 21  21°C
#define UNIT_TEMP_22C         0x16  // 22  22°C
#define UNIT_TEMP_23C         0x17  // 23  23°C
#define UNIT_TEMP_24C         0x18  // 24  24°C
#define UNIT_TEMP_25C         0x19  // 25  25°C
#define UNIT_TEMP_26C         0x1A  // 26  26°C
#define UNIT_TEMP_27C         0x1B  // 27  27°C
#define UNIT_TEMP_28C         0x1C  // 28  28°C
#define UNIT_TEMP_29C         0x1D  // 29  29°C
#define UNIT_TEMP_30C         0x1E  // 30  30°C
#define UNIT_TEMP_31C         0x1F  // 31  31°C
#define UNIT_TEMP_32C         0x20  // 32  32°C
#define UNIT_TEMP_HIGH        0x21  // 33  HI Temperature > 32°C

// State structure for read/write EEPROM saved data for keep last state and default state of the Electronic A/C Unit
typedef struct tagUnitState {
   UNIT_STATUS Status;              // Unit State
   uint8_t Auto;                    // AUTOmatic ON/OFF
   uint8_t Economic;                // ECONomic ON/OFF
   uint8_t Recirculate;             // RECIrculate ON/OFF
   uint8_t SelectedTemp;            // Passenger selected temperature
   uint8_t Speed;                   // Select fan speed
   uint8_t AirDistMotor;            // Selected Air Distribution Motor position
   uint8_t CockBlendMotor;          // Cock & Blended motor position     //No implemented yet!
   uint8_t AirIntakeMotor;          // Air Intake Flap motor position    //No implemented yet!
   TLPS_STATE ThreeLevelSwitch;     // Car Compressor state

   struct {
      uint8_t fUI: 1;
      uint8_t fAirDistMotor: 1;
      uint8_t fCockBlendMotor: 1;   // No implemented yet!
      uint8_t fAirIntakeMotor: 1;   // No implemented yet!
      uint8_t fPassengerTemp: 1;
      uint8_t fSpeed: 1;
      uint8_t fExtTemp: 1;
   } flags;

} UNIT_STATE, *pUNIT_STATE;


// Temp. sensors readings
typedef struct tagTempSensorsInfo {
   int8_t  TopBlended;              // Top Blended. From -30°C to 50°C
   int8_t  BottomBlended;           // Bottom Blended. From -30°C to 50°C
   int8_t  OutsideMirror;           // Outside Mirror. From -30°C to 50°C
   int8_t  Passenger;               // Passenger Fan. From -20°C to 50°C
} TEMP_SENSORS_INFO, *pTEMP_SENSORS_INFO;


// -------- Functions Prototypes --------- //
void UnitInit(pUNIT_STATE, pADM_POSITION_INFO, pESR_SPEED_INFO, pTEMP_SENSORS_INFO);
void UnitOn(pUNIT_STATE);
void UnitOff(pUNIT_STATE);
void UnitAutomatic(pUNIT_STATE);
void UnitRecirculate(pUNIT_STATE);
void UnitEconomic(pUNIT_STATE);
void UnitTempInc(pUNIT_STATE);
void UnitTempDec(pUNIT_STATE);
void UnitExternTemp(pUNIT_STATE);
void UnitSpeedInc(pUNIT_STATE);
void UnitSpeedDec(pUNIT_STATE);
void UnitAirDistMotor(pUNIT_STATE, ADM_POSITION);
void UnitLastState(pUNIT_STATE);
void UnitSaveState(pUNIT_STATE);


#endif /* UNIT_H_ */