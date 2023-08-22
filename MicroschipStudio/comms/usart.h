/*
 * USART.h
 *
 * Created: 7/7/2016 12:39:02 a. m.
 *  Author: IoT SolucioneX
 */ 

#ifndef USART_H_
#define USART_H_


//--- Includes ---//
#include "HAL/config.h"


// Buffer for sprintf(...)
#define MAX_BUFFER 128

#if defined (__AVR_ATmega324P__)
#define UDR          UDR0
#define UCSRA        UCSR0A
#define MPCM         MPCM0
#define U2X          U2X0
#define UPE          UPE0
#define DOR          DOR0
#define FE           FE0
#define UDRE         UDRE0
#define TXC          TXC0
#define RXC          RXC0
#define UCSRB        UCSR0B
#define TXB8         TXB80
#define RXB8         RXB80
#define UCSZ2        UCSZ02
#define TXEN         TXEN0
#define RXEN         RXEN0
#define UDRIE        UDRIE0
#define TXCIE        TXCIE0
#define RXCIE        RXCIE0
#define UCSRC        UCSR0C
#define UCPOL        UCPOL0
#define UCSZ0        UCSZ00
#define UCSZ1        UCSZ10
#define USBS         USBS0
#define UPM0         UPM00
#define UPM1         UPM01
#define UBRRL        UBRR0L        
#define UBRRH        UBRR0H
#define URSEL        0x00
#endif

// Enable/Disable RX/TX modules
//                      UCSR0B
//    Receiver Enable: |RXENn:4|
// Transmitter Enable: |TXENn:3|
typedef enum tagUSART_ENABLE_MODE {
   UEM_TX,
   UEM_RX,
   UEM_BOTH
} USART_MODE;

// USART Control and Status Register C [UCSR0C]
//     Mode of operation: [UCSR0C]->|UMSELn1:7|UMSELn0:6|
//    Asynchronous USART:       0         0
//     Synchronous USART:       0         1
//              Reserved:       1         0
//    Master SPI (MSPIM):       1         1
typedef enum tagUSART_OPMODE {
   UOM_ASYNCHRONOUS = 0x00,
   UOM_SYNCHRONOUS  = 0x40,      // 0b0100.0000
   // UOM_RESERVED  = 0x80,      // 0b1000.0000
#if defined (__AVR_ATmega324P__)
   UOM_MASTER_SPI   = 0xC0       // 0b1100.0000
#endif
} USART_OPMODE;

//Parity Mode: [UCSRxC]->|UPMn1:5|UPMn0:4|
//            Disabled:     0       0
//            Reserved:     0       1
//       Enabled. Even:     1       0
//        Enabled. Odd:     1       1
typedef enum tagUSART_PARITY_MODE {
   UPM_DISABLE     = 0x00,
   // UPM_RESERVED = 0x10,       // 0b0001.0000
   UPM_EVEN        = 0x20,       // 0b0010.0000
   UPM_ODD         = 0x30        // 0b0011.0000
} USART_PARITY_MODE;

// Stop Bit: [UCSRxC]->|USBSn:3|
#define USART_STOP_2BIT    0x08
typedef enum tagUSART_STOP_BIT {
   USB_1BIT,
   USB_2BIT
} USART_STOP_BIT;

//                   UCSR0B       UCSR0C
// Character Size: |UCSZn2:2|UCSZn1:2|UCSZn0:1|
//          5-bit:     0        0        0 
//          6-bit:     0        0        1 
//          7-bit:     0        1        0 
//          8-bit:     0        1        1 
//       Reserved:     1        0        0 
//       Reserved:     1        0        1 
//       Reserved:     1        1        0
//          9-bit:     1        1        1 
typedef enum tagUSART_CHAR_SIZE { 
   UCSZ_5BIT        = 0x00,
   UCSZ_6BIT        = 0x02,    // 0b0000.0010
   UCSZ_7BIT        = 0x04,    // 0b0000.0100
   UCSZ_8BIT        = 0x06,    // 0b0000.0110
   // UCSZ_RESERVED = 0x00,
   UCSZ_9BIT        = 0x0E     // The 9-bit is determinate by UCSRxB, be can use this mask to define the 9bit 
                               // and 8bit in UCSRxC, 0x0E=bxxxx1110)
} USART_CHAR_SIZE;


//--- Function Prototypes ---//

static inline void USARTFlush(void) {
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
   uint8_t tmp = 0;
#pragma GCC diagnostic pop

   while (UCSRA & (1 << RXC)) {
      tmp = UDR;
   }
}

// USART Prototypes
void USARTInit(USART_OPMODE, USART_PARITY_MODE, USART_STOP_BIT, USART_CHAR_SIZE);
uint16_t USARTReceiveData(void);
void USARTTransmitData(uint16_t);
void USARTPrintString(const char chrStr[]);


#endif /* USART_H_ */
