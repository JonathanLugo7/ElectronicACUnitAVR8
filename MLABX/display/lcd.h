/*
 * LCD.h
 *
 * Created: 12/12/2016 2:46:09 a.m.
 *  Author: IoT SolucioneX
 */ 

#ifndef LCD_H_
#define LCD_H_

//-- Includes --//
#include "HAL/config.h"
#include "HAL/pinouts.h"


// -------- LCD Defines --------- //

//
// PCF2112CT Pin out Configuration
//
//                   --------_--------
//  Clock Burst In -|1              40|- Data In Enable - DLEN
//             Vdd -|2              39|- Data In
//      Oscillator -|3              38|- Backplane Driver Output
//             Vss -|4              37|- N/C
//             S32 -|5              36|- S1
//             S31 -|6              35|- S2
//             S30 -|7              34|- S3
//             S29 -|8              33|- S4
//             S28 -|9              32|- S5
//             S27 -|10             31|- S6
//             S26 -|11             30|- S7
//             S25 -|12             29|- S8
//             S24 -|13             28|- S9
//             S23 -|14             27|- S10
//             S22 -|15             26|- S11
//             S21 -|16             25|- S12
//             S20 -|17             24|- S13
//             S19 -|18             23|- S14
//             S18 -|19             22|- S15
//             S17 -|20             21|- S16
//                   -----------------
//

//PCF2112CT pins
#define LCD_MASKS         ((1 << LCD_DATA) | (1 << LCD_CLOCK_IN) | (1 << LCD_DLEN))

//LCD Display Constants                   // Decimal  Description
#define LCD_CLEAR          0x00           //       0  Clear LCD display, all segments off
#define LCD_DIGIT_MASK     0x7F           //     127  For clean LCD display digit byte, only 7 bits

//
//LCD DIGIT display are the 1st and 2nd byte of data of uint32_t of LCDSendDataAsm
//LCD Display Digits Constants            // Decimal      Segments           Digit
#define LCD_0              0x7B           //     123  S1+S2+S4+S5+S6+S7      0
#define LCD_1              0x0A           //      10  S2+S4                  1
#define LCD_2              0x57           //      87  S1+S2+S3+S5+S7         2
#define LCD_3              0x1F           //      31  S1+S2+S3+S4+S5         3
#define LCD_4              0x2E           //      46  S2+S3+S4+S6            4
#define LCD_5              0x3D           //      61  S1+S3+S4+S5+S6         5
#define LCD_6              0x7D           //     125  S1+S3+S4+S5+S6+S7      6
#define LCD_7              0x0B           //      11  S1+S2+S4               7
#define LCD_8              0x7F           //     127  S1+S2+S3+S4+S5+S6+S7   8
#define LCD_9              0x3F           //      63  S1+S2+S3+S4+S5+S6      9

//LCD Display Letters Constants UPERCASE  // Decimal      Segments           Letter
#define LCD_A              0x6F           //     111  S1+S2+S3+S4+S6+S7      A
#define LCD_B              0x7F           //     127  S1+S2+S3+S4+S5+S6+S7   B
#define LCD_C              0x71           //     113  S1+S5+S6+S7            C
#define LCD_D              0x5B           //      91  S1+S2+S4+S5+S7         D
#define LCD_E              0x75           //     117  S1+S3+S5+S6+S7         E
#define LCD_F              0x65           //     101  S1+S3+S6+S7            F
#define LCD_G              0x79           //     121  S1+S4+S5+S6+S7         G
#define LCD_H              0x6E           //     110  S2+S3+S4+S6+S7         H
#define LCD_I              0x60           //      10  S6+S7                  I
#define LCD_J              0x5A           //      90  S2+S4+S5+S7            J
#define LCD_K              0x76           //     118  S2+S3+S5+S6+S7         K
#define LCD_L              0x70           //     112  S5+S6+S7               L
#define LCD_M              0x49           //      73  S1+S4+S7               M
#define LCD_N              0x6B           //     107  S1+S2+S4+S6+S7         N
#define LCD_O              0x7B           //     123  S1+S2+S4+S5+S6+S7      O
#define LCD_P              0x67           //     103  S1+S2+S3+S6+S7         P
#define LCD_Q              0x37           //      55  S1+S2+S3+S5+S6         Q
#define LCD_R              0x63           //      99  S1+S2+S6+S7            R
#define LCD_S              0x3D           //      61  S1+S3+S4+S5+S6         S
#define LCD_T              0x0B           //      11  S1+S2+S4               T
#define LCD_U              0x7A           //     122  S2+S4+S5+S6+S7         U
#define LCD_V              0x66           //     102  S2+S3+S6+S7            V
#define LCD_W              0x7E           //     176  S2+S3+S4+S5+S6+S7      W
#define LCD_X              0x2C           //      44  S3+S4+S6               X
#define LCD_Y              0x3E           //      62  S2+S3+S4+S5+S6         Y
#define LCD_Z              0x57           //      87  S1+S2+S3+S5+S7         Z

//LCD Display Letters Constants lowercase // Decimal      Segments           Letter
#define LCD_a              0x5F           //      95  S1+S2+S3+S4+S5+S7      a
#define LCD_b              0x7C           //     124  S3+S4+S5+S6+S7         b
#define LCD_c              0x54           //      84  S3+S5+S7               c
#define LCD_d              0x5E           //      94  S2+S3+S4+S5+S7         d
#define LCD_e              0x77           //     119  S1+S2+S3+S5+S6+S7      e
#define LCD_f              0x65           //     101  S1+S3+S6+S7            f
#define LCD_g              0x3F           //      63  S1+S2+S3+S4+S5+S6      g
#define LCD_h              0x6C           //     108  S3+S4+S6+S7            h
#define LCD_i              0x08           //       8  S4                     i
#define LCD_j              0x1A           //      26  S2+S4+S5               j
#define LCD_k              0x6D           //     109  S1+S3+S4+S6+S7         k
#define LCD_l              0x60           //      96  S6+S7                  l
#define LCD_m              0x48           //      72  S4+S7                  m
#define LCD_n              0x4C           //      76  S3+S4+S7               n
#define LCD_o              0x56           //      92  S3+S4+S5+S7            o
#define LCD_p              0x67           //     103  S1+S2+S3+S6+S7         p
#define LCD_q              0x2F           //      47  S1+S2+S3+S4+S6         q
#define LCD_r              0x44           //      68  S3+S7                  r
#define LCD_s              0x3D           //      61  S1+S3+S4+S5+S6         s
#define LCD_t              0x74           //     116  S3+S5+S6+S7            t
#define LCD_u              0x58           //      88  S4+S5+S7               u
#define LCD_v              0x58           //      88  S4+S5+S7               v
#define LCD_w              0x32           //      50  S2+S5+S6               w
#define LCD_x              0x46           //      70  S2+S3+S7               x
#define LCD_y              0x3E           //      62  S2+S3+S4+S5+S6         y
#define LCD_z              0x57           //      87  S1+S2+S3+S5+S7         z

//LCD Display Constants no printable      // Decimal      Segments           Letter
#define LCD_SPACE          0x00           //       0      N/A                Space

//
//LCD Air Distribution Motor special symbols. Byte2:1
//
//LCD Display AirDistMotor Constants      // Decimal  Symbol
#define LCD_ADM_FRONT      0x0546         //    1350  ??
#define LCD_ADM_FRONT_FEET 0x1546         //    5446  ??
#define LCD_ADM_FEET       0x1446         //    5190  ??
#define LCD_ADM_WINDSHIELD 0x2E66         //   11878  ??


//LCD Symbols display are the 3rd byte of data of uint32_t of LCDSendDataAsm
//LCD Display Symbols Constants           // Decimal  LCD segment
#define LCD_MINUS          0x01           //       1  -                   
#define LCD_EXT            0x02           //       2  EXT
#define LCD_MANUAL         0x04           //       4  MANUAL
#define LCD_AUTO           0x08           //       8  AUTO
#define LCD_SPEED_SEP      0x10           //      16  | | | | | | | | |
#define LCD_HUNDREDS       0x20           //      32  1
#define LCD_SYMBOLS_MASK   0xFF           //For clean LCD display symbols byte
#define LCD_MODE_MASK      (LCD_MANUAL | LCD_AUTO) //For clean AUTO|MANUAL mode


//LCD SPEED bar display are the 4th byte of data of uint32_t of LCDSendDataAsm
//LCD Display Speed Constants       // Binary        Decimal    Symbol           LCD segment
#define LCD_SPEED_1        0x01     // b0000.0001    16777216   []                S25 
#define LCD_SPEED_2        0x03     // b0000.0011    50331648   [][]              S25+S26
#define LCD_SPEED_3        0x07     // b0000.0111   117440512   [][][]            S25+S26+S27
#define LCD_SPEED_4        0x0F     // b0000.1111   251658240   [][][][]          S25+S26+S27+S28
#define LCD_SPEED_5        0x1F     // b0001.1111   520093696   [][][][][]        S25+S26+S27+S28+S29
#define LCD_SPEED_6        0x3F     // b0011.1111  1056964608   [][][][][][]      S25+S26+S27+S28+S29+S30
#define LCD_SPEED_7        0x7F     // b0111.1111  2130706432   [][][][][][][]    S25+S26+S27+S28+S29+S30+S31
#define LCD_SPEED_8        0xFF     // b1111.1111  4278190080   [][][][][][][][]  S25+S26+S27+S28+S29+S30+S31+S32
#define LCD_SPEED_MASK     0xFF     //For clean LCD display speed byte

// -------- LED's Functions Prototypes --------- //

void LCDInit(void);
void LCDSendData(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void LCDClear(void);
uint8_t LCDNumberToDigit(uint8_t number);


#endif /* LCD_H_ */