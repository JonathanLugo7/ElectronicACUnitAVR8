/*
 * ADC.h
 *
 * Created: 7/7/2016 3:28:40 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "config.h"

#if !defined(ADCL)
#error "ERROR: ADC module don't exist"
#endif


// -------- ADC Defines --------- //

// Ref. values
#define ADC_VREF_VALUE        5.0f        // Vref at 5.0V
#define ADC_SAMPLES           10          // ADC samples reading average
#define ADC_MAX_VALUE         1024        // ADC 10bit = 2^10=1024 Max. Values: 0..1023
#define ADC_RESOLUTION        1024.0f     // ADC 10bit = 2^10=1024
#define ADC_READ_DELAY        5           // In microseconds

// ADC Multiplexer Selection Register [ADMUX]
// Voltage Reference Selection: [ADMUX]->|REFS1:7|REFS0:6|
//                               AREF:      0       0
//                               AVcc:      0       1
//                               1.1V:      1       0
//                              2.56V:      1       1
#define ADC_VOLTAGE_VREF_MASK    ((1 << REFS1) | (1 << REFS0))
typedef enum tagADC_VOLTAGE_REF {
   ADC_VREF_AREF          = 0x00, 
   ADC_VREF_AVCC          = ((1 << REFS0)),                 // 0x40
   ADC_VREF_INTERNAL_1V1  = ((1 << REFS1)),                 // 0x80
   ADC_VREF_INTERNAL_2V56 = ((1 << REFS1) | (1 << REFS0))   // 0xC0
}
ADC_VOLTAGE_REF;

// Left Adjust Result: [ADMUX]->|ADLAR:5|
#define ADC_LEFT_ADJUST_RESULT_MASK   (1 << ADLAR)  
typedef enum tagADC_LEFT_ADJUST_RESULT {
   ADC_LAR_RIGHT, 
   ADC_LAR_LEFT
} 
ADC_LEFT_ADJUST_RESULT;

// Analog Channel Selection: ADMUX->|MUX[3...0]|
#define ADC_CHANNEL_MASK    ((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))
typedef enum tagADC_CHANNEL {
   ADC_CHANNEL0    = 0x00,
   ADC_CHANNEL1    = ((1 << MUX0)),
   ADC_CHANNEL2    = ((1 << MUX1)),
   ADC_CHANNEL3    = ((1 << MUX1) | (1 << MUX0)),
   ADC_CHANNEL4    = ((1 << MUX2)),
   ADC_CHANNEL5    = ((1 << MUX2) | (1 << MUX0)),
   ADC_CHANNEL6    = ((1 << MUX2) | (1 << MUX1)),
   ADC_CHANNEL7    = ((1 << MUX2) | (1 << MUX1) | (1 << MUX0)),
#if defined (__AVR_ATmega324P__) || \
    defined (__AVR_ATmega16A__)
   ADC0_ADC0_10X   = (1 << MUX3),
   ADC1_ADC0_10X   = ((1 << MUX3) | (1 << MUX0)),
   ADC0_ADC0_200X  = ((1 << MUX3) | (1 << MUX1)),
   ADC1_ADC0_200X  = ((1 << MUX3) | (1 << MUX1) | (1 << MUX0)),
   ADC2_ADC2_10X   = ((1 << MUX3) | (1 << MUX2)),
   ADC3_ADC2_10X   = ((1 << MUX3) | (1 << MUX2) | (1 << MUX0)),
   ADC2_ADC2_200X  = ((1 << MUX3) | (1 << MUX2) | (1 << MUX1)),
   ADC3_ADC2_200X  = ((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)),
   ADC0_ADC1_1X    = (1 << MUX4),
   ADC1_ADC1_1X    = ((1 << MUX4) | (1 << MUX0)),
   ADC2_ADC1_1X    = ((1 << MUX4) | (1 << MUX1)),
   ADC3_ADC1_1X    = ((1 << MUX4) | (1 << MUX1) | (1 << MUX0)),
   ADC4_ADC1_1X    = ((1 << MUX4) | (1 << MUX2)),
   ADC5_ADC1_1X    = ((1 << MUX4) | (1 << MUX2) | (1 << MUX0)),
   ADC6_ADC1_1X    = ((1 << MUX4) | (1 << MUX2) | (1 << MUX1)),
   ADC7_ADC1_1X    = ((1 << MUX4) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)),
   ADC0_ADC2_1X    = ((1 << MUX4) | (1 << MUX3)),
   ADC1_ADC2_1X    = ((1 << MUX4) | (1 << MUX3) | (1 << MUX0)),
   ADC2_ADC2_1X    = ((1 << MUX4) | (1 << MUX3) | (1 << MUX1)),
   ADC3_ADC2_1X    = ((1 << MUX4) | (1 << MUX3) | (1 << MUX1) | (1 << MUX0)),
   ADC4_ADC2_1X    = ((1 << MUX4) | (1 << MUX3) | (1 << MUX2)),
   ADC5_ADC2_1X    = ((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX0)),
   ADC_1V1_BANDGAP = ((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1)),
   ADC_GROUND      = ((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))
#elif defined (__AVR_ATmega328P__)
   ADC_TEMP_SENSE  = (1 << MUX3),
   // Reserved
   // Reserved
   // Reserved
   // Reserved
   // Reserved
   ADC_1V1_BANDGAP = ((1 << MUX3) | (1 << MUX2) | (1 << MUX1)),
   ADC_GROUND      = ((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))
#endif
} ADC_CHANNEL;

// ADC Control and Status Register A [ADCSRA]
// Clock Pre-scaler Selector: ADCSRA->|ADPS2:2|ADPS1:1|ADPS0:0|
#define ADC_PRESCALER_MASK    ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
typedef enum tagADC_PRESCALER {
   ADC_PRESCALER_DIV0   = 0x00,
   ADC_PRESCALER_DIV2   = ((1 << ADPS0)),
   ADC_PRESCALER_DIV4   = ((1 << ADPS1)),
   ADC_PRESCALER_DIV8   = ((1 << ADPS1) | (1 << ADPS0)),
   ADC_PRESCALER_DIV16  = ((1 << ADPS2)),
   ADC_PRESCALER_DIV32  = ((1 << ADPS2) | (1 << ADPS0)),
   ADC_PRESCALER_DIV64  = ((1 << ADPS2) | (1 << ADPS1)),
   ADC_PRESCALER_DIV128 = ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
}
ADC_PRESCALER;

// ADC Control and Status Register B [ADCSRB]
// Set ADC Auto Trigger Enable in [ADCSRA]->ADATE:5
// Auto Trigger Source: ADCSRB->|ADTS2:2|ADTS1:1|ADTS0:0|
#define ADC_AUTO_TRIGGER_MASK    ((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))
typedef enum tagADC_AUTO_TRIGGER {
   ADC_AT_FREERUNNING               = 0x00,
   ADC_AT_ANALOG_COMPARATOR         = ((1 << ADTS0)),
   ADC_AT_EXTERNAL_INT_REQUEST0     = ((1 << ADTS1)),
   ADC_AT_TMRCNTR0_COMPARE_MATCH_A  = ((1 << ADTS1) | (1 << ADTS0)),
   ADC_AT_TMRCNTR0_OVERFLOW         = ((1 << ADTS2)),
   ADC_AT_TMRCNTR1_COMPARE_MATCH_B  = ((1 << ADTS2) | (1 << ADTS0)),
   ADC_AT_TMRCNTR1_OVERFLOW         = ((1 << ADTS2) | (1 << ADTS1)),
   ADC_AT_TMRCNTR1_CAPTURE_EVENT    = ((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))
}
ADC_AUTO_TRIGGER;


//--- ADC Functions API prototypes ---//

void     ADCInit(ADC_PRESCALER, ADC_VOLTAGE_REF);
void     ADCSetLeftAdjustResult(ADC_LEFT_ADJUST_RESULT);
float    ADCReadAsVoltage(ADC_CHANNEL);
uint16_t ADCReadAsValue(ADC_CHANNEL);


#endif /* ADC_H_ */
