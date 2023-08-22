/*
 * USART.c
 *
 * Created: 7/7/2016 12:38:51 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */ 

//--- Includes ---//
#include "usart.h"

static inline void USARTEnableMode(USART_MODE mode) {
   if (mode == UEM_TX) {
      UCSRB |= (1 << TXEN);
   }

   if (mode == UEM_RX) {
      UCSRB |= (1 << RXEN);
   }

   if (mode == UEM_BOTH) {
      UCSRB |= ((1 << RXEN) | (1 << TXEN));
   }
}

static inline void USARTDisableMode(USART_MODE mode) {
   if (mode == UEM_TX) {
      UCSRB &= ~(1 << TXEN);
   }

   if (mode == UEM_RX) {
      UCSRB &= ~(1 << RXEN);
   }

   if (mode == UEM_BOTH) {
      UCSRB &= ~((1 << RXEN) | (1 << TXEN));
   }
}

static inline void USARTSetFrameFormat(USART_OPMODE opMode, USART_PARITY_MODE parityMode, 
                                       USART_STOP_BIT stopBit, USART_CHAR_SIZE charSize) {

   uint8_t frame = 0;

   if (opMode != UOM_ASYNCHRONOUS) {
      frame |= opMode;
   }

   if (parityMode != UPM_DISABLE) {
      frame |= parityMode;
   }

   if (stopBit == USB_2BIT) {
      frame |= USART_STOP_2BIT;
   }

   if (charSize == UCSZ_5BIT) {
      // UCSZ2=UCSZ1=UCSZ0=0
   }
   else if (charSize == UCSZ_9BIT) {
      UCSRB |= (1 << UCSZ2);
      frame |= UCSZ_8BIT;
   }
   else {
      frame |= charSize;  //6..8-bit
   }

   // For ATmega16A. The UBRRH Register shares the same I/O location as the UCSRC register, If URSEL is zero during 
   // a write operation, the UBRRH value will be updated, otherwise, UCSRC register
   UCSRC = ((1 << URSEL) | frame);
}

//--- API Implementations ---///

/* ***
   FUNCTION: void USARTInit(USART_OPMODE opMode, USART_PARITY_MODE parityMode, USART_STOP_BIT stopBit, USART_CHAR_SIZE charSize)
   DESCRIPTION: Initialize USART communications module.

   PARAMETERS: USART_OPMODE opMode. ASYNCHRONOUS, SYNCHRONOUS or MASTER_SPI
               USART_PARITY_MODE parityMode.DISABLE, EVEN or ODD
               USART_STOP_BIT stopBit. 1_STOP_BIT, 2_STOP_BIT
               USART_CHAR_SIZE charSize. CSZ_5BIT, CSZ_6BIT, CSZ_7BIT, CSZ_8BIT or CSZ_9BIT

   RETURN: void
*** */
void USARTInit(USART_OPMODE opMode, USART_PARITY_MODE parityMode, USART_STOP_BIT stopBit, USART_CHAR_SIZE charSize) {  

   // Set in <util/setbaud.h>
   // UBRRxH = UBRRH_VALUE;
   // UBRRxL = UBRRL_VALUE; 
   // #if USE_2X
   //    UCSRxA |= (1 << U2X0);
   // #else
   //    UCSRxA &= ~(1 << U2X0);
   // #endif

   // Baud rate calculation Asynchronous
   // Normal Mode (U2Xn = 0).  BAUD  = (Fcpu / 16 * UBRRn) + 1
   //                          UBRRn = (Fcpu / 16 * BAUD) � 1
   // Double Speed (U2Xn = 1). BAUD  = (Fcpu / 8 * UBRRn) + 1
   //                          UBRRn = (Fcpu / 8 * BAUD) � 1
   // Example: U2Xn=0. UBBRn = 160000000 / 16 * 19200 - 1 = 51
   // UBRRxH = (uint8_t) (UBRR >> 8);
   // UBRRxL = (uint8_t) UBRR;

   // Set 38.4K as default Baud Rate. See Table 19-11 at the ATmega324-PA data sheet for default defined 
   // values for Fcpu.
   //
   // This value is calculate for Fcpu=8MHz and U2Xn=0. UBRR = (8000000 / (16 * 38400)) - 1 = 12,020833.
   //  -------------------------------------------------------------------------------------------------------------
   // |                | U2Xn = 0	                                   | U2Xn = 1                                   | 
   // | Bit Rate (bps) |--------------------------------------------------------------------------------------------
   // |                | UBRR (Dec)	| UBRR (Hex)	| Bit Rate	| Error | UBRR (Dec)	| UBRR (Hex) | Bit Rate | Error |
   //  -------------------------------------------------------------------------------------------------------------
   // |      38.4K     |    12      |     0x0C     | 38.462K   | 0.2%  |     25     |    0x19    |  38.462K |  0.2% |
   //  -------------------------------------------------------------------------------------------------------------

   // Don't use double speed
   UCSRA &= ~(1 << U2X);

   // Setup Baud rate
   UBRRH = 0x00;
   UBRRL = 0x0C;

   // Config module
   USARTEnableMode(UEM_TX);
   USARTSetFrameFormat(opMode, parityMode, stopBit, charSize);
}

/* ***
   FUNCTION: void USARTTransmitData(uint16_t ui16Data)
   DESCRIPTION: Transmit data frame for USART channel

   PARAMETERS: uint16_t ui16Data. 5 to 9 bit of data to transmit
   RETURN: void
*** */
void USARTTransmitData(uint16_t ui16Data) {

   // Wait for TX buffer is transmitting
   while ( !(UCSRA & (1 << UDRE)) ) {
   }

   // If Data Frame is 9-bit, setup [UCSR0B:0]->TXB8: Transmit 9 Data Bit. If the 9-bit in data is 1, set TXB8 and 
   // discard MSB of data
   UCSRB &= ~(1 << TXB8);
   if (ui16Data & 0x0100 ) {
      UCSRB |= (1 << TXB8);
   }

   // UDRx with the LSByte of data. Frame 5..8 Data Bit
   UDR = ui16Data;
}

/* ***
   FUNCTION: uint16_t USARTReceiveData(void)
   DESCRIPTION: Receive data frame for USART channel

   PARAMETERS: void
   RETURN: uint16_t ui16Data. 5 to 9 bit of data to receive
*** */
uint16_t USARTReceiveData(void) {

   //Wait for RX buffer is receiving
   while ( !(UCSRA & (1 << RXC)) ) {
   }

   // If Data Frame is 9-bit, read [UCSR0B:1]->RXB8 first
   uint8_t ui8Status = UCSRA;
   uint8_t ui8HIGH = UCSRB;
   uint8_t ui8LOW = UDR;

   //Receive Error?
   if (ui8Status & ((1 << FE) | (1 << DOR) | (1 << UPE))) {
      return -1;
   }

   // [UCSRnB:1] has the 9-bit in the bit RXB8n, if is set=1, then add the 9-bit in the result
   ui8HIGH = (ui8HIGH >> 1) & 0x01;

   //UDRn with LSB, high with 9-bit??
   return ((ui8HIGH << 8) | ui8LOW);   
}

/* ***
   FUNCTION: uint16_t USARTReceiveData(void)
   DESCRIPTION: Receive data frame for USART channel

   PARAMETERS: void
   RETURN: uint16_t ui16Data. 5 to 9 bit of data to receive
*** */
void USARTPrintString(char const chrStr[]) {

   // If empty string = '\0'
   if (!*chrStr) {
      return;
   }

   while (*chrStr) {
      // If find the CR send first one LF. Windows/UNIX??
      if (*chrStr == '\n') {
         USARTTransmitData('\r');
      }

      USARTTransmitData(*chrStr++);
   }
}
