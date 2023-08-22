/*
 * config.h
 *
 * Created: 29/3/2018 2:00:21 p. m.
 *  Author: IoT SolucioneX
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

//--- Includes ---//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/atomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"


//--- Defines ---//
#undef F_CPU

//CPU Frequency. For Arduino Uno Board Fcpu = 16MHz
//For ATmega324PA Final Centralita is 16MHz external crystal oscillator
//For ATmega328P 8MHz internal calibrated oscillator
#ifndef F_CPU
#define F_CPU 8000000
#include <util/delay.h>
#endif


#endif /* CONFIG_H_ */