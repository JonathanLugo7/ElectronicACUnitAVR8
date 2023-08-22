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


//Buffer for sprintf(...)
#define MAX_BUFFER 128

//USART Control and Status Register C [UCSR0C]
//Mode of operation: [UCSR0C]->|UMSELn1:7|UMSELn0:6|
//        Asynchronous USART:       0         0
//         Synchronous USART:       0         1
//                  Reserved:       1         0
//        Master SPI (MSPIM):       1         1
#define USART_OPMODE_MASK   ((1 << UMSEL01) | (1 << UMSEL01))
typedef enum tagUSART_OPMODE { 
   USART_OPMODE_ASYNCHRONOUS = 0x00,
   USART_OPMODE_SYNCHRONOUS  = 0x40,
   // USART_OPMODE_RESERVED  = 0x80,
   USART_OPMODE_MASTER_SPI   = 0xC0
}
USART_OPMODE;

//Parity Mode: [UCSR0C]->|UPMn1:5|UPMn0:4|
//            Disabled:     0       0
//            Reserved:     0       1
//       Enabled. Even:     1       0
//        Enabled. Odd:     1       1
#define USART_PARITY_MODE_MASK   ((1 << UPM01) | (1 << UPM00))
typedef enum tagUSART_PARITY_MODE {
   USART_PARITY_DISABLE     = 0x00,
   //USART_PARITY_RESERVED  = 0x10,
   USART_PARITY_EVEN        = 0x20,
   USART_PARITY_ODD         = 0x30 
} 
USART_PARITY_MODE;


//Stop Bit: [UCSR0C]->|USBSn:3|
#define USART_STOP_BIT_MASK   0x08
typedef enum tagUSART_STOP_BIT { 
   USART_1STOP_BIT,
   USART_2STOP_BIT 
} 
USART_STOP_BIT;

//                  UCSR0B       UCSR0C
//Character Size: |UCSZn2:2|UCSZn1:2|UCSZn0:1|
//         5-bit:     0        0        0 
//         6-bit:     0        0        1 
//         7-bit:     0        1        0 
//         8-bit:     0        1        1 
//      Reserved:     1        0        0 
//      Reserved:     1        0        1 
//      Reserved:     1        1        0
//         9-bit:     1        1        1 
#define USART_CHAR_SIZE_MASK        ((1 << UCSZ01) | (1 << UCSZ00))
#define USART_CHAR_SIZE_9BIT_MASK   ((1 << UCSZ01) | UCSZ00)
typedef enum tagUSART_CHAR_SIZE { 
   USART_CSZ_5BIT        = 0x00,
   USART_CSZ_6BIT        = 0x02,
   USART_CSZ_7BIT        = 0x04,
   USART_CSZ_8BIT        = 0x06,
   //USART_CSZ_RESERVED  = 0x00,
   USART_CSZ_9BIT        = 0x0E     //The 9-bit is determinate by UCSRxB, be can use this
                                    //mask to define the 9bit cz and 8bit cz in UCSRxC
                                    //0x0E=b1110)
} 
USART_CHAR_SIZE;

// Enable/Disable RX/TX modules
//                     UCSR0B       
//   Receiver Enable: |RXENn:4|
//Transmitter Enable: |TXENn:3|
typedef enum tagUSART_ENABLE_MODE { 
   USART_TX, 
   USART_RX, 
   USART_BOTH 
} USART_MODE;


//--- Function Prototypes ---//


static inline void USARTEnableMode(USART_MODE mode) {

	//Enable USART module for TX & RX
	if (mode == USART_TX)
      UCSR0B |= (1 << TXEN0);

	if (mode == USART_RX)
		UCSR0B |= (1 << RXEN0);

   if (mode == USART_BOTH)
      UCSR0B |= ((1 << RXEN0) | (1 << TXEN0));
}

static inline void USARTDisableMode(USART_MODE mode) {

   //Enable USART module for TX & RX
   if (mode == USART_TX)
      UCSR0B &= ~(1 << TXEN0);

   if (mode == USART_RX)
      UCSR0B &= ~(1 << RXEN0);

   if (mode == USART_BOTH)
      UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));
}

static inline void USARTSetOpMode(USART_OPMODE opMode) {

	//Unset == USART_OPMODE_ASYNCHRONOUS
	UCSR0C &= ~(USART_OPMODE_MASK);
	if (opMode != USART_OPMODE_ASYNCHRONOUS) {
      UCSR0C |= opMode;
   }      
}

static inline void USARTSetParityMode(USART_PARITY_MODE parityMode) {

	//Unset == USART_PARITY_MODE_DISABLE
	UCSR0C &= ~(USART_PARITY_MODE_MASK);
	if (parityMode != USART_PARITY_DISABLE) {
      UCSR0C |= parityMode;
   }   
}

static inline void USARTSetStopBit(USART_STOP_BIT stopBit) {

	//Unset == USART_1STOP_BIT
	UCSR0C &= ~(USART_STOP_BIT_MASK);
	if (stopBit == USART_2STOP_BIT)
	   UCSR0C |= (1 << USBS0);
}

static inline void USARTSetCharSize(USART_CHAR_SIZE charSize) {

	//Unset == USART_CSZ_5BIT
	UCSR0C &= ~(USART_CHAR_SIZE_MASK);  
	UCSR0B &= ~(1 << UCSZ02);  //9-bit en UCSRnB

	if (charSize == USART_CSZ_5BIT)
      return;

	if (charSize == USART_CSZ_9BIT) {
      UCSR0B |= (1 << UCSZ02);
      UCSR0C |= (USART_CSZ_8BIT);

      return;
   }

   //CSZ6..8-bit
   UCSR0C |= charSize;
}

static inline void USARTFlush(void) {
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
   uint8_t tmp;
#pragma GCC diagnostic pop

   while (UCSR0A & (1 << RXC0)) {
      tmp = UDR0;
   }
}

//USART Prototypes
void     USARTInit(USART_OPMODE, 
                   USART_PARITY_MODE,
                   USART_STOP_BIT, 
                   USART_CHAR_SIZE);

uint16_t USARTReceiveData(void);
void     USARTTransmitData(uint16_t);
void     USARTPrintString(const char chrStr[]);


#endif /* USART_H_ */
