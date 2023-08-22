/*
 * Borad.c
 *
 * Created: 11/7/2016 3:00:04 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

//--- Includes ---//
#include "board.h"
#include "adc.h"
#include "display/lcd.h"
#include "display/led.h"
#include "actuators/airDistMotor.h"
#include "actuators/elecSpeedReg.h"
#include "actuators/threeLevelSwitch.h"
#include "actuators/lamps.h"
#include "keypad/keypad.h"

#if defined DEBUG || DEBUG_TASK
#include "comms/usart.h"
#endif


//--- API Implementation ---//


/* ***
   FUNCTION: void BoardInit(void)
   DESCRIPTION: Initialize Hardware Abstraction Layer HAL of the unit 

   PARAMETERS: void
   RETURN: void
*** */
void BoardInit(void) {

   // define DEBUG_TASK: For task operation debug
   // define DEBUG: For SignalR operation debug
   #if defined DEBUG || DEBUG_TASK
      //Baud: 38.4k. Frame 8N1 (8bit, No Parity, 1 Bit Stop)
      USARTInit(USART_OPMODE_ASYNCHRONOUS, USART_PARITY_DISABLE, USART_1STOP_BIT, USART_CSZ_8BIT);
      USARTPrintString("\n<BoardInit>\nElectronic A/C Fiat Tempra Controller\n\n");
   #endif

   //HAL initialization
   ADCInit(ADC_PRESCALER_DIV128, ADC_VREF_AREF); //ADC 62.5KHz. Vref=AVcc=5.0V. Fcpu=8MHz. 8000000/128=62500Hz=62.5kHz

   //Display
   LEDInit();        //LED driver MM5481N module
   LCDInit();        //LCD driver PCF2112CT module
   LampsInit();      //LCD lamps driver module

   //Actuators
   ADMInit();        //Air Distribution Motor H-Bridge L293D module
   TLPSInit();       //Three Level Pressure Switch H-Bridge L293D module
   ESRInit();        //Electronic Speed Regulator driver PWM output
   
   //Inputs
   KeypadInit();     //Keypad matrix buttons module
}
