/*
 * Pinouts.h
 *
 * Created: 22/2/2017 4:46:58 a.m.
 *  Author: IoT SolucioneX
 */ 

#ifndef PINOUTS_H_
#define PINOUTS_H_

//--- Includes ---//
#include <avr/io.h>


//ADC Analog Inputs
#define AN0_TEMP_SENS_PASSENGER           ADC_CHANNEL0      //Motor Fan Passenger NTC temperature sensor
#define AN1_TEMP_SENS_OUTSIDE             ADC_CHANNEL1      //Outside Mirror NTC temperature sensor
#define AN2_TEMP_SENS_BOTTOM_BLENDED      ADC_CHANNEL2      //Bottom Blended NTC temperature sensor
#define AN3_AIR_DIST_MOTOR                ADC_CHANNEL3      //Air Distribution Motor position potentiometer
#define AN4_TEMP_SENS_ELEC_SPEED_REG      ADC_CHANNEL4      //Electronic Speed Regulator NTC temperature sensor
#define AN5_TEMP_SENS_TOP_BLENDED         ADC_CHANNEL5      //Top Blended NTC temperature sensor
#define AN6_L4947_VOLTAGE_REG             ADC_CHANNEL6      //Voltage Regulator L4947.Vout
#define AN7_AIR_COCK_BLEND_MOTOR          ADC_CHANNEL7      //Air Cock & Blend Motor position potentiometer


//Push Buttons Ports Register, PORTC0:3 for Rows and PORTB4:7 for columns
#define KEYPAD_DDR                        DDRC              //Keypad DDR register
#define KEYPAD_PORT                       PORTC             //Keypad PORT register
#define KEYPAD_PIN                        PINC              //Keypad PIN register
//Pin definition:
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define KEYPAD_ROW0                       PINC0             //Row on PIN0.             PA0
#define KEYPAD_ROW1                       PINC1             //Row on PIN1.             PA1
#define KEYPAD_ROW2                       PINC2             //Row on PIN2.             PA2
#define KEYPAD_ROW3                       PINC3             //Row on PIN3.             PA3
#define KEYPAD_COL0                       PINC4             //Column on PIN4.          PA4
#define KEYPAD_COL1                       PINC5             //Column on PIN5.          PA5
#define KEYPAD_COL2                       PINC6             //Column on PIN6.          PA6
#define KEYPAD_COL3                       PINC7             //Column on PIN7.          PA7


//H-Bridge driver L293D for the Air Distribution Motor and Air Cock & Blend Motor
#define ADM_DDR                           DDRB              //L293D DDR register
#define ADM_PORT                          PORTB             //L293D PORT register
#define ADM_PIN                           PINB              //L293D PIN register
//Pin definition
//Air Dist. Motor                         ATMegaxxxxx                                  NEC uPD78C14
#define ADM_L293D_1A                      PINB5             //L293D(1).1A              PD0
#define ADM_L293D_2A                      PINB7             //L293D(1).2A              PD1
//Air Cock & Blend Motor                  ATMegaxxxxx                                  NEC uPD78C14
#define ACB_L293D_3A                      PINB5             //L293D(1).1A              PD2
#define ACB_L293D_4A                      PINB7             //L293D(1).2A              PD3
//Air Intake Motor                        ATMegaxxxxx                                  NEC uPD78C14
#define AIM_L293D_1A                      PINB5             //L293D(2).1A              PD4
#define AIM_L293D_2A                      PINB7             //L293D(2).2A              PD5


//LCD segments driver PCF21121CT pin outs
#define LCD_DDR                           DDRB              //PCF2112CT DDR register
#define LCD_PORT                          PORTB             //PCF2112CT PORT register
#define LCD_PIN                           PINB              //PCF2112CT PIN register
//Pin definition 
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define LCD_DLEN                          PINB0             //PCF2112CT.DLEN           PB0
#define LCD_CLOCK_IN                      PINB1             //PCF2112CT.CLOCK_BURST    PB1
#define LCD_DATA                          PINB2             //PCF2112CT.DATA           PB2


//LEDs driver MM5481N pin outs
#define LED_DDR                           DDRD              //MM5481N DDR register
#define LED_PORT                          PORTD             //MM5481N PORT register
#define LED_PIN                           PIND              //MM5481N PIN register
//Pin definition
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define LED_DATA                          PIND6             //MM5481N.DATA             PF0
#define LED_CLOCK_IN                      PIND5             //MM5481N.CLOCK_IN         PF1
#define LED_DATA_ENABLE                   PIND4             //MM5481N.DATA_ENABLE      PF2


//Bulbs transistors controller for Temperature and Speed LCD display pin outs
#define LCD_LAMP_DDR                      DDRD              //LCD display DDR register
#define LCD_LAMP_PORT                     PORTD             //LCD display PORT register
#define LCD_LAMP_PIN                      PIND              //LCD display PIN register
//Pin definition
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define LCD_LAMP_TEMPERATURE              PIND0             //Transistor NPN-T2.Base   PD7
#define LCD_LAMP_SPEED                    PIND7             //Transistor NPN-T1.Base   PC4


//Electronic Speed Regulator (ESR) for passenger compartment heating/ventilation
#define ESR_DDR                           DDRB              //ESR DDR register
#define ESR_PORT                          PORTB             //ESR PORT register
#define ESR_PIN                           PINB              //ESR PIN register
//Pin definition
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define ESR_PWM_PIN                       PINB3             //Timer/Compare0 output    OP Amp


//H-Bridge driver L293D for the Three Level Pressure Switch (TLPS) - "Compressor pulley driver"
#define TLPS_DDR                          DDRD              //TLPS DDR register
#define TLPS_PORT                         PORTD             //TLPS PORT register
#define TLPS_PIN                          PIND              //TLPS PIN register
//Pin definition 
//                                        ATMegaxxxxx                                  NEC uPD78C14
#define TLPS_L293D_3A                     PIND2             //L293D(2).1A              PD6


#endif /* PINOUTS_H_ */