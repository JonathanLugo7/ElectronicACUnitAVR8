/*
 * ADC.c
 *
 * Created: 7/7/2016 3:28:57 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

#include "adc.h"

#ifdef DEBUG_TASK
#include "comms/usart.h"
#endif


//--- Local global variables ---//


//--- Local functions implementations ---//

static inline void ADCEnable(void) {

#if defined(PRR)
   //Enable Power Reduction ADC in PRR register
   PRR &= ~(1 << PRADC);
#endif

   //NOTE: Will take 25 ADC clock cycles settled first time
   ADCSRA |= (1 << ADEN);
}

static inline void ADCDisable(void) {

#if defined(PRR)
   //Disable Power Reduction ADC in PRR register
   PRR |= (1 << PRADC);
#endif

   ADCSRA &= ~(1 << ADEN);
}

static inline void ADCStartConversion(void) {
   ADCSRA |= (1 << ADSC);  //ADC = 0;
}

static inline void ADCSetVoltageReference(ADC_VOLTAGE_REF voltRef) {      
   ADMUX &= ~(ADC_VOLTAGE_VREF_MASK);  //Unset == ADC_VREF_AREF

   if (voltRef != ADC_VREF_AREF)
      ADMUX |= voltRef;                //Set new Voltage Reference
}

/* ***
   By default, the successive approximation circuitry requires an input clock 
   frequency between 50kHz and 200kHz to get maximum resolution. If a lower 
   resolution than 10 bits is needed, the input clock frequency to the ADC can be 
   higher than 200kHz to get a higher sample rate.
   
      ADPS2    ADPS1    ADPS0    Division Factor
       0        0        0            0
       0        0        1            2
       0        1        0            4
       0        1        1            8
       1        0        0           16
       1        0        1           32
       1        1        0           64
       1        1        1          128
*** */
static inline void ADCSetPrescaler(ADC_PRESCALER adcPrescaler) {
   ADCSRA &= ~(ADC_PRESCALER_MASK);    //Unset. adcPrescaler == ADC_PRESCALER_DIV0 == Fcpu/2
   ADCSRA |= adcPrescaler;             //Set Pre-scaler Clock
}

static inline void ADCEnableInterrupt(void) {
	ADCSRA |= (1 << ADIE);
}

static inline void ADCDisableInterrupt(void) {
	ADCSRA &= ~(1 << ADIE);
}

static inline void ADCSetChannel(ADC_CHANNEL channel) {         
   //Wait for any conversion in progress, ADSC==1, before change channel
   while (bit_is_set(ADCSRA, ADSC));

   //NOTE: We need to set ADMUX register, to do that we keep the higher nibble
   //(& 0xF0) and set the new ADC channel, (channel & 0x0F) to stay in ADC7..ADC0
   //NOTE: For read ADC channel ADC8 (Temperature), 1.1V and GND, use special functions
   ADMUX = ((ADMUX & 0xF0) | (channel & ADC_CHANNEL_MASK));
}

static inline void ADCSetAutoTrigger(ADC_AUTO_TRIGGER autoTrigger) {
   ADCSRA &= ~(ADC_AUTO_TRIGGER_MASK);    //Unset. autoTrigger==ADC_AUTOTRIGGER_FREERUNNING
   ADCSRA |= autoTrigger;              //Set new value
}

static inline void ADCEnableAutoTrigger(void) {
   ADCSRA |= (1 << ADATE);
}

static inline void ADCDisableAutoTrigger(void) {
   ADCSRA &= ~(1 << ADATE);
}

/* ***
   
   When this bit is written logic one, the digital input buffer on the corresponding ADC pin is 
   disabled. The corresponding PIN Register bit will always read as zero when this bit is set. 
   When an analog signal is applied to the ADC5...0 pin and the digital input from this pin is 
   not needed, this bit should be written logic one to reduce power consumption in the digital 
   input buffer.

*** */
#if defined(DIDR) || defined(DIDR0)
static inline void ADCDisableDigitalInputs(ADC_CHANNEL channel) {
   #if defined(DIDR0)
	   DIDR0 = channel;
   #elif defined(DIDR)
	   DIDR = channel;
   #endif
}
#endif

/* ***
   FUNCTION: uint8_t ADCRead8BitValue(ADC_CHANNEL adcChannel)
   DESCRIPTION: Read ADC channel 8-bit resolution

   NOTE: If we want LeftAdjustLeft and the result 10 bits resolution, call
         ADCSetLeftAdjustResult(ADC_LAR_LEFT) first then call ADCRead10BitValue()

   PARAMETERS: ADC_CHANNEL adcChannel
   RETURN: uint8_t. 8-bit ADC value
*** */
#ifdef ADC_8BITS_RESOLUTION
static uint8_t ADCRead8BitValue(ADC_CHANNEL channel) {
   ADCEnable();                              //Enable ADC module converter

   ADCSetLeftAdjustResult(ADC_LAR_LEFT);     //Left Adjust Result Register, 8-bit data resolution
   ADCSetChannel(channel);                   //Set ADC channel
   ADCStartConversion();                     //Start ADC conversion

   while (bit_is_set(ADCSRA, ADSC));         //Conversion in progress, ADSC==1, waiting...

   ADCDisable();                             //Disable ADC module converter

   //ADC value in ADCHigh register
   return ADCH;
}
#endif

/* ***
   FUNCTION: uint16_t ADCRead10BitValue(ADC_CHANNEL adcChannel)
   DESCRIPTION: Read ADC channel 8-bit resolution

   PARAMETERS: ADC_CHANNEL adcChannel
   RETURN: uint16_t. 10-bit ADC value
*** */
static uint16_t ADCRead10BitValue(ADC_CHANNEL channel) {
   
   ADCEnable();                        //Enable ADC module converter
   ADCSetChannel(channel);             //Set ADC channel
   ADCStartConversion();               //Start ADC conversion
   
   while (bit_is_set(ADCSRA, ADSC));   //Conversion in progress, ADSC==1, waiting...

   uint16_t ui16AdcValue = 0;          //ADC conversion value

#if defined(ADC)
   ui16AdcValue = ADC;
#else
   //Read ADCLow first
	uint8_t adcLow = ADCL;
	uint8_t adcHigh = ADCH;

   //16 bit packing
   ui16AdcValue = ((uint16_t) adcHigh << 8) | adcLow;
#endif

   ADCDisable();                       //Disable ADC module converter

   return ui16AdcValue;   
}


//--- Functions API implementations ---//

/* ***
   FUNCTION: ADCInit(ADC_PRESCALER adcPrescaler, ADC_VOLTAGE_REF adcVoltRef) 
   DESCRIPTION: Initialize Analog to Digital Converter HAL

   PARAMETERS: ADC_PRESCALER adcPrescaler, ADC_VOLTAGE_REF adcVoltRef)
   RETURN: void
*** */
void ADCInit(ADC_PRESCALER prescaler, ADC_VOLTAGE_REF voltRef) {
   ADCSetVoltageReference(voltRef);    //Set Voltage Reference
   ADCSetPrescaler(prescaler);         //Set ADC Clock
   
   #ifdef DEBUG_TASK
      USARTPrintString("<ADCInit: Init>\n\n");
   #endif
}

/* ***
   Left Adjust Result   
   
   ADLAR = 0: Right Adjustment         
         X    X    X    X    X    X   ADC9 ADC8 = ADCH
      ADC7 ADC6 ADC5 ADC4 ADC3 ADC2 ADC1 ADC0 = ADCL

   ADLAR = 1: Left Adjustment
      ADC9 ADC8 ADC7 ADC6 ADC5 ADC4 ADC3 ADC2 = ADCH
      ADC1 ADC0  X    X    X    X    X    X   = ADCL
*** */
void ADCSetLeftAdjustResult(ADC_LEFT_ADJUST_RESULT leftAdjsRes) {
   //Default: Right Adjust 
   ADMUX &= ~(ADC_LEFT_ADJUST_RESULT_MASK);     //Unset
   if (leftAdjsRes == ADC_LAR_LEFT) {
      ADMUX |= (1 << ADLAR);
   }      
}

/* ***
   FUNCTION: uint16_t ADCReadAsValue(ADC_CHANNEL adcChannel)
   DESCRIPTION: Read ADC channel a return result as ADC value

   PARAMETERS: ADC_CHANNEL adcChannel
   RETURN: uint16_t. ADC Value 10 bit resolution
*** */
uint16_t ADCReadAsValue(ADC_CHANNEL channel) {
   //Consecutive readings and average conversion
   uint16_t adc = 0;
   for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
      adc += ADCRead10BitValue(channel);
      _delay_us(5);
   }

   adc /= ADC_SAMPLES;

   return adc;
}

/* ***
   FUNCTION: float ADCReadAsVoltage(ADC_CHANNEL adcChannel)
   DESCRIPTION: Read ADC channel a return result as voltage
                  
                ADC = (Vin * 1024) / Vref
                ...
                Vin = (ADC * Vref) / 1024

   PARAMETERS: ADC_CHANNEL adcChannel
   RETURN: float. ADC Voltage 10 bit resolution
*** */
float ADCReadAsVoltage(ADC_CHANNEL channel) {   
   uint16_t adc = ADCReadAsValue(channel);

   // return (adc * ADC_VREF_VALUE) / ADC_RESOLUTION;

   // Microchip AppNotes-00002447A.pdf
   // Vcc_value = ( 0x400 * 1.1 ) / (ADC_RES_L + ADC_RES_H * 0x100)
   //              0x400 = 1024
   //              1.1 = Vref
   //              ADC_RES_L + ADC_RES_H * 0x100 = ADC value
   return (ADC_VREF_VALUE * ADC_RESOLUTION) / adc;
}
