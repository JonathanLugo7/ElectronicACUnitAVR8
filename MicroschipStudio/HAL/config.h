/*
 * config.h
 *
 * Created: 29/3/2018 2:00:21 p. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

//--- Includes ---//
#include "clock.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef DEBUG
#include <stdlib.h>
#include <stdio.h>
#endif

#include "common.h"

#endif /* CONFIG_H_ */