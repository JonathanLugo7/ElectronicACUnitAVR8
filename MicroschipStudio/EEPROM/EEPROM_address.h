/*
 * EEPROM_address.h
 *
 * Created: 10/5/2018 11:50:12 p. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef EEPROM_ADDRESS_H_
#define EEPROM_ADDRESS_H_

// -------- Defines --------- //

// EEprom ADDReSS Unit State for automatic states. 1 byte
#define EEADDRSS_US_AUTOMATIC                0x00
#define EEADDRSS_US_ECONOMIC                 0x01
#define EEADDRSS_US_RECIRCULATE              0x02
#define EEADDRSS_US_AIR_DIST_MOTOR           0x03
#define EEADDRSS_US_COCK_BLEND_MOTOR         0x04
#define EEADDRSS_US_AIR_INTAKE_MOTOR         0x05
#define EEADDRSS_US_TEMPERATURE              0x06
#define EEADDRSS_US_SPEED                    0x07
#define EEADDRSS_US_LAST_STATE               0x08

// EEprom ADDReSS Unit State for WoRKing states. 1 byte
#define EEADDRSS_US_AUTOMATIC_WRK            0x09
#define EEADDRSS_US_ECONOMIC_WRK             0x0A
#define EEADDRSS_US_RECIRCULATE_WRK          0x0B
#define EEADDRSS_US_AIR_DIST_MOTOR_WRK       0x0C
#define EEADDRSS_US_COCK_BLEND_MOTOR_WRK     0x0D
#define EEADDRSS_US_AIR_INTAKE_MOTOR_WRK     0X0E
#define EEADDRSS_US_TEMPERATURE_WRK          0x0F
#define EEADDRSS_US_SPEED_WRK                0x10
#define EEADDRSS_US_LAST_STATE_WRK           0x11

// EEprom ADDReSS for Air Distribution Motor potentiometer values, reading from the ADC module (See Tempra Service Manual). 2 bytes
#define EEADDRSS_ADM_ADC_FRONT		         0x12
#define EEADDRSS_ADM_ADC_FRONT_FEET          0x14
#define EEADDRSS_ADM_ADC_FEET                0x16
#define EEADDRSS_ADM_ADC_WINDSHLD            0x18

// EEprom ADDReSS for Electronic Speed Regulator Timer2 OCR2x value for PWM duty cycle. 1 byte
#define EEADDRSS_ESR_SPEED1                  0x1A
#define EEADDRSS_ESR_SPEED2                  0x1B
#define EEADDRSS_ESR_SPEED3                  0x1C
#define EEADDRSS_ESR_SPEED4                  0x1D
#define EEADDRSS_ESR_SPEED5                  0x1E
#define EEADDRSS_ESR_SPEED6                  0x1F
#define EEADDRSS_ESR_SPEED7                  0x20
#define EEADDRSS_ESR_SPEED8                  0x21
#define EEADDRSS_ESR_SPEED9                  0x22
#define EEADDRSS_ESR_SPEED10                 0x23
#define EEADDRSS_ESR_SPEED11                 0x24
#define EEADDRSS_ESR_SPEED12                 0x25
#define EEADDRSS_ESR_SPEED13                 0x26
#define EEADDRSS_ESR_SPEED14                 0x27
#define EEADDRSS_ESR_SPEED15                 0x28


#endif /* EEPROM_ADDRESS_H_ */