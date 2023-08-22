//0x4A4C676F
/*
 * elecSpeedReg.h
 *
 * Created: 21/10/2018 9:04:28 p. m.
 *  Author: IoT SolucioneX
 */ 


#ifndef ELECSPEEDREG_H_
#define ELECSPEEDREG_H_


//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"


//-- Defines --//

//Max Electronic Speed Regulator speed controller
#define ESR_MAX_SPEED               16    //From 0 to 15

//Using Timer0 PWM output pin OCR0A
#define ESR_PWM_COUNTER             OCR0A

//Electronic Speed Regulator. Timer Pre-scaler
#define ESR_DIV_NOCLOCK            ~((1 << CS02) | (1 << CS01) | (1 << CS00))
#define ESR_DIV_NOPRESCALER         ((1 << CS00))
#define ESR_DIV8_PRESCALER          ((1 << CS01))
#define ESR_DIV32_PRESCALER         ((1 << CS01) | (1 << CS00))
#define ESR_DIV64_PRESCALER         ((1 << CS02))
#define ESR_DIV128_PRESCALER        ((1 << CS02) | (1 << CS00))
#define ESR_DIV256_PRESCALER        ((1 << CS02) | (1 << CS01))
#define ESR_DIV1024_PRESCALER       ((1 << CS02) | (1 << CS01) | (1 << CS00))

//Electronic Speed Regulator. PWM Compare Output Mode
#define ESR_PMW_MODE_DISCONECT_CHANNEL_A     ~((1 << COM0A1) | (1 << COM0A0))
#define ESR_PWM_MODE_TOGGLE_CHANNEL_A         ((1 << COM0A0))
#define ESR_PWM_MODE_CLEAR_SET_CHANNEL_A      ((1 << COM0A1))
#define ESR_PWM_MODE_SET_CLEAR_CHANNEL_A      ((1 << COM0A1) | (1 << COM0A0))

#define ESR_PMW_MODE_DISCONECT_CHANNEL_B     ~((1 << COM0B1) | (1 << COM0B0))
#define ESR_PWM_MODE_TOGGLE_CHANNEL_B         ((1 << COM0B0))
#define ESR_PWM_MODE_CLEAR_SET_CHANNEL_B      ((1 << COM0B1))
#define ESR_PWM_MODE_SET_CLEAR_CHANNEL_B      ((1 << COM0B1) | (1 << COM0B0))

//Electronic Speed Regulator. PWM Waveform generation mode
#define ESR_PWM_PHASE_CORRECT_MODE1_A  ((1 << WGM00))
#define ESR_PWM_PHASE_CORRECT_MODE1_B  ((0x00))
#define ESR_PWM_PHASE_CORRECT_MODE5_A  ((1 << WGM00))
#define ESR_PWM_PHASE_CORRECT_MODE5_B  ((1 << WGM02))
#define ESR_PWM_FAST_MODE3_A           ((1 << WGM01) | (1 << WGM00))
#define ESR_PWM_FAST_MODE3_B           ((0x00))
#define ESR_PWM_FAST_MODE7_A           ((1 << WGM01) | (1 << WGM00))
#define ESR_PWM_FAST_MODE7_B           ((1 << WGM02))

//Electronic Speed Regulator setup
#define ESR_PWM_OUTPUT_CHANNEL         (1 << ESR_PWM_PIN)

//Electronic Speed Regulator selected speed. For PWM Duty Cycle values see EEPROM_data.c
#define ESR_SPEED_0                 0x00
#define ESR_SPEED_1                 0x01
#define ESR_SPEED_2                 0x02
#define ESR_SPEED_3                 0x03
#define ESR_SPEED_4                 0x04
#define ESR_SPEED_5                 0x05
#define ESR_SPEED_6                 0x06
#define ESR_SPEED_7                 0x07
#define ESR_SPEED_8                 0x08
#define ESR_SPEED_9                 0x09
#define ESR_SPEED_10                0x0A
#define ESR_SPEED_11                0x0B
#define ESR_SPEED_12                0x0C
#define ESR_SPEED_13                0x0D
#define ESR_SPEED_14                0x0E
#define ESR_SPEED_15                0x0F
#define ESR_SPEED_UNDEFINED         0xFF

//Air Dist. Motor movement
typedef enum tagESR_SPEED_MOVE { 
   ESR_SPEED_NONE  = 0,
   ESR_SPEED_UP  = -1,
   ESR_SPEED_DOWN = 1
} ESR_SPEED_MOVE;

//Electronic Speed Regulator task data
typedef struct tagESRSpeedInfo {
   uint8_t SpeedSource;                // Actual Blower Speed. OCRx value
   uint8_t SpeedTarget;                // New Blower Speed. OCRx value
   ESR_SPEED_MOVE esrMove;             // If target <> source then where to speed Up<->down?
} ESR_SPEED_INFO, *pESR_SPEED_INFO;


// --- Functions prototype ---//

void ESRInit(void);
void ESRUpdateSpeedInfo(pESR_SPEED_INFO, uint8_t);


#endif /* ELECSPEEDREG_H_ */
//0x4A4C676F