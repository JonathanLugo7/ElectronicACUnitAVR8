
/*
 * PCF2112CT_asm.S
 *
 * Created: 22/2/2017 4:43:38 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


//#define _SFR_ASM_COMPAT 1
#define __SFR_OFFSET 0
#include <avr/io.h>
#include "HAL/pinouts.h"


//Bit position=7-6-5-4-3-2-1-[0]
#define BIT_POSITION    0x00        //Dec:0

// Bit counter eight bits
#define BIT_COUNTER     0x08        //Dec:8

//
//PCF2112CT Clock pulses description
//
//At 8MHz 1 clock pulse about 0.125uS
//0.125uS * 8 = 1uS delay HIGH time
//0.125uS * 24 = 3uS delay low time
//

//tWH: CLB HIGH time 1uS minimum
#define LCD_DELAY_HIGH  0x08        //Dec:8. Clock HIGH delay

//tWL: CLB low time 3uS minimum
#define LCD_DELAY_LOW   0x18        //Dec:24. Clock low delay

//Variables registers
counter = 19                       //counter = register r19
delay   = 20                       //delay = register r20


/* ***
   FUNCTION: void LCDSendDataAsm(uint32_t ui32Data)
   DESCRIPTION: Send data to the PCF2112CT LCD driver. LCD data is 32 bits unsigned long
                passing as argument from C as uint32_t to assembler on the registers r25:r22.
                We are processing every byte from Less Significant Byte to Most Significant Byte
                and from less significant bit to most significant bit too. The PCF2112CT use 
                C-Bus data frame for serial comunication with theses lines:
                   DATA: Data segments
                   CLB: Clock buster
                   DLEN: Data enable

                SEE: See LCDs.h for PCF2112CT data frame format and datasheet for more info.

   PARAMETERS: uint32_t ui32Data. 32 bits of data for 32 lcd segments.

   RETURN: void
*** */

.global LCDSendDataAsm

LCDSendDataAsm:
            cli                              ;Disable interrupts
            //Save working registers
            push  counter                    ;Save counter register (r19) in the stack
            //
            // NXP PCF2112Cx C-Bus serial data
            //
            cbi   LCD_PORT, LCD_DATA         ;Prepare leading zero bit
            nop
            sbi   LCD_PORT, LCD_DLEN         ;Set DLEN HIGH. Enable data transmit
            nop                              ;tSUEN: Enable setup time
            //
            // Send Leading zero bit
            //                               ;1 CLB pulse
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL   
                                             ;tHDDA: Data hold time
            //
            // First byte of (uint32_t ui32Data) in r22 (LSB)
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte1:      sbrs  r22, BIT_POSITION          ;if (r22.bit0 == 1) skip else DATA = low
            cbi   LCD_PORT, LCD_DATA         ;Set DATA low. LCD Segment off
            sbrc  r22, BIT_POSITION          ;if (r22.bit0 == 0) skip else DATA = HIGH
            sbi   LCD_PORT, LCD_DATA         ;Set DATA HIGH. LCD Segment on
            // Data LCD S25..S32             ;26..33 CLB pulses
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time
            lsr   r22                        ;Shift r22 one bit right to ask for another bit
            dec   counter                    ;Decrement i (r29)
            brne  byte1                      ;if (i == 0) break else continue
            //
            // Second byte of (uint32_t ui32Data) in r23
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte2:      sbrs  r23, BIT_POSITION          ;if (r23.bit0 == 1) skip else DATA = low
            cbi   LCD_PORT, LCD_DATA         ;Set DATA low. LCD Segment off
            sbrc  r23, BIT_POSITION          ;if (r23.bit0 == 0) skip else DATA = HIGH
            sbi   LCD_PORT, LCD_DATA         ;Set DATA HIGH. LCD Segment on
            // Data LCD S17..24              ;18..25 CLB pulses
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time
            lsr   r23                        ;Shift r23 one bit right to ask for another bit
            dec   counter                    ;Decrement i (r19)
            brne  byte2                      ;if (i == 0) break else continue
            //
            //Third byte of (uint32_t ui32Data) in r24
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte3:      sbrs  r24, BIT_POSITION          ;if (r24.bit0 == 1) skip else DATA = low
            cbi   LCD_PORT, LCD_DATA          ;Set DATA low. LCD Segment off
            sbrc  r24, BIT_POSITION          ;if (r24.bit0 == 0) skip else DATA = HIGH
            sbi   LCD_PORT, LCD_DATA          ;Set DATA HIGH. LCD Segment on
            // Data LCD S9..S16              ;10..17 CLB pulses
            sbi   LCD_PORT, LCD_CLOCK_IN      ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time
            cbi   LCD_PORT, LCD_CLOCK_IN      ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time
            lsr   r24                        ;Shift r24 one bit right to ask for the next bit
            dec   counter                    ;Decrement i (r19)
            brne  byte3                      ;if (i == 0) break else continue
            //
            //Fourth byte of (uint32_t ui32Data) in r25 (MSB)
            //
            ldi   counter, BIT_COUNTER       ;Dec:8 for (i=8; i > 0; i--) {...}
byte4:      sbrs  r25, BIT_POSITION          ;if (r25.bit0 == 1) skip else DATA = low
            cbi   LCD_PORT, LCD_DATA         ;Set DATA low. LCD Segment off
            sbrc  r25, BIT_POSITION          ;if (r25.bit0 == 0) skip else DATA = HIGH
            sbi   LCD_PORT, LCD_DATA         ;Set DATA HIGH. LCD Segment on            
            // Data LCD S1..S8               ;2..9 CLB pulses
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time
            lsr   r25                        ;Shift r25 one bit right to ask for the next bit
            dec   counter                    ;Decrement i (r19)
            brne  byte4                      ;if (i == 0) break else continue
            //
            // Load latches bit
            //
            sbi   LCD_PORT, LCD_DATA         ;Set DATA HIGH
            nop                              ;34 CLB pulse
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time (950nS)
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time (950nS)
            //
            // Disable
            //
            cbi   LCD_PORT, LCD_DATA         ;Set DATA low
            rcall LCDDelayL                  ;tSUDI
            cbi   LCD_PORT, LCD_DLEN         ;Set DLEN low
            rcall LCDDelayL                  ;tSULD
            //
            //  Load pulse
            //
                                             ;35 CLB pulse
            sbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK HIGH
            rcall LCDDelayH                  ;tDH: Clock HIGH time (950nS)
            cbi   LCD_PORT, LCD_CLOCK_IN     ;CLOCK low
            rcall LCDDelayL                  ;tDL: Clock low time (950nS)
            //
            //All C-Bus lines low
            //
            rcall LCDDelayL                  ;tBUSY
            //
            //End and return to C
            //
            sei                              ;Enable interrupts
            pop   counter                    ;Restore counter register (r19) from the stack
            ret                              ;return

LCDDelayH:  push  delay                      ;Save delay register (r20) in the stack
            ldi   delay, LCD_DELAY_HIGH      ;Load delay time. 8MHz=0,125uS*8=1uS
dlyH:       dec   delay                      ;for (delay=delay_time; delay > 0; delay--) {
            brne  dlyH                       ;...}
            pop   delay                      ;Restore delay register (r20) from the stack
            ret                              ;return

LCDDelayL:  push  delay                      ;Save delay register (r20) in the stack
            ldi   delay, LCD_DELAY_LOW       ;Load delay time. 8MHz=0,125uS*24=3uS
dlyL:       dec   delay                      ;for (delay=delay_time; delay > 0; delay--) {
            brne  dlyL                       ;...}
            pop   delay                      ;Restore delay register (r20) from the stack
            ret                              ;return
