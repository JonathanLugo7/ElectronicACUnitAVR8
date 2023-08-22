
/*
 * MM5481N_asm.S
 *
 * Created: 22/2/2017 4:44:24 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


//#define _SFR_ASM_COMPAT 1
#define __SFR_OFFSET 0
#include <avr/io.h>
#include "HAL/pinouts.h"


//--- Defines ---///
#define BIT_POSITION    0x00        //Bit position=7-6-5-4-3-2-1-[0]
#define BIT_COUNTER     0x08        //Bit counter eight bits
#define LED_DELAY       0x08        //Clock HIGH and low delay. (tH=tL=950nS minimum)
                                    //At 8MHz, 1 clock pulse about 0.125uS
                                    //0.125uS * 8 = 1uS delay.

//Register as variables
delay    = 19                       //delay = register r19 
counter  = 20                       //counter = register r20


/* ***
   FUNCTION: void LEDSendDataASM(uint32_t)
   DESCRIPTION: Send serial data to the MM5481N LED driver. LED data is 32 bits unsigned long 
                passing as argument from C as uint32_t to assembler on the registers r25:r22.
                We are processing every byte from Less Significant Byte to Most Significant Byte
                and  from less significant bit to most significant bit too. MM5481x use serial 
                comunication with theses lines:
                   DATA_IN: leds
                   CLOCK: clock
                   ___________
                   DATA_ENABLE: active low data enable

                SEE: LEDs.h for MM5481N data frame format and datasheet for more info.

                NOTE:
                For enable transmission DATA_ENABLE must be low. If high, the shift register 
                sees zeroes clocked in.

   PARAMETERS: uint32_t ui32Data. First 32 bits of data, bits 33..34 not used in the MM5481N
               only in the MM5450x

   RETURN: void
*** */

.global LEDSendDataAsm

LEDSendDataAsm:
            cli                              ;Disable interrupts
            //Save working registers
            push  counter                    ;Save counter register (r20) in the stack
            //
            // National MM5481N IC led driver serial data communication
            //
            cbi   LED_PORT, LED_DATA_ENABLE  ;DATA_ENABLE is active low signal
            nop                              ;tDS: Set-up time
            //
            //Send START condition. A start bit of logical '1'
            //
            sbi   LED_PORT, LED_DATA         ;DATA HIGH
            nop                              ;tDH: Data Hold time
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tL: Clock low time (950nS)
            //
            // First byte of (uint32_t ui32Data) in r22 (LSB)
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte1:      sbrs  r22, BIT_POSITION          ;if (r22.bit0 == 1) skip else DATA = low
            cbi   LED_PORT, LED_DATA         ;Set DATA low. LED off
            sbrc  r22, BIT_POSITION          ;if (r25.bit0 == 0) skip else DATA = HIGH
            sbi   LED_PORT, LED_DATA         ;Set DATA HIGH. LED on
            // Data LED1..LED4               ;2..9 CLB pulses
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            lsr   r22                        ;Shift r25 one bit right to ask for the next bit
            dec   counter                    ;Decrement i (r20)
            brne  byte1                      ;if (i == 0) break else continue
            //
            // Second byte of (uint32_t ui32Data) in r23
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte2:      sbrs  r23, BIT_POSITION          ;if (r23.bit0 == 1) skip else DATA = low
            cbi   LED_PORT, LED_DATA         ;Set DATA low. LED off
            sbrc  r23, BIT_POSITION          ;if (r24.bit0 == 0) skip else DATA = HIGH
            sbi   LED_PORT, LED_DATA         ;Set DATA HIGH. LED on
            // Data LED5..LED8               ;10..17 CLB pulses
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            lsr   r23                        ;Shift r23 one bit right to ask for the next bit
            dec   counter                    ;Decrement i (r20)
            brne  byte2                      ;if (i == 0) break else continue
            //
            //Third byte of (uint32_t ui32Data) in r24
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte3:      sbrs  r24, BIT_POSITION          ;if (r24.bit0 == 1) skip else DATA = low
            cbi   LED_PORT, LED_DATA         ;Set DATA low. LED off
            sbrc  r24, BIT_POSITION          ;if (r24.bit0 == 0) skip else DATA = HIGH
            sbi   LED_PORT, LED_DATA         ;Set DATA HIGH. LED on
            // Data LED9..LED12              ;18..25 CLB pulses
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            lsr   r24                        ;Shift r24 one bit right to ask for another bit
            dec   counter                    ;Decrement i (r20)
            brne  byte3                      ;if (i == 0) break else continue
            //
            //Fourth byte of (uint32_t ui32Data) in r25 (MSB)
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte4:      sbrs  r25, BIT_POSITION          ;if (r25.bit0 == 1) skip else DATA = low
            cbi   LED_PORT, LED_DATA         ;Set DATA low. LED off
            sbrc  r25, BIT_POSITION          ;if (r22.bit0 == 0) skip else DATA = HIGH
            sbi   LED_PORT, LED_DATA         ;Set DATA HIGH. LED on
            // Data LED13..LED14             ;26..33 CLB pulses
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            lsr   r25                        ;Shift r22 one bit right to ask for another bit
            dec   counter                    ;Decrement i (r20)
            brne  byte4                      ;if (i == 0) break else continue
            //
            //The MM5481x drive 14 leds, while the MM5450x can drive 34 leds, we only send
            //32 bits of data for the MM5481x, for the MM5450x we need send one extra byte for
            //the other two led (LED33 and LED34), we ommited here
            //
            cbi   LED_PORT, LED_DATA         ;Set led 33 and 34 off (Default)
            //Clock 34
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            //Clock 35
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            //
            //After the 36th bit data is latched and transmit is complete
            //
            //Clock 36
            sbi   LED_PORT, LED_CLOCK_IN     ;CLOCK HIGH
            rcall LEDDelay                   ;tDH: Clock HIGH time (950nS)
            cbi   LED_PORT, LED_CLOCK_IN     ;CLOCK low
            rcall LEDDelay                   ;tDL: Clock low time (950nS)
            //End transmision
            sbi   LED_PORT, LED_DATA_ENABLE  ;DATA_ENABLE is active low signal
            sei                              ;Enable interrupts
            pop   counter                    ;Restore counter register (r20) from the stack
            ret                              ;return

LEDDelay:   push  delay                      ;Save delay register (r19) in the stack
            ldi   delay, LED_DELAY           ;Load delay time. 8MHz=0,125uS*10=1.25uS
dly:        dec   delay                      ;for (delay=delay_time; delay > 0; delay--) {
            brne  dly                        ;...}
            pop   delay                      ;Restore delay register (r19) from the stack
            ret                              ;return
