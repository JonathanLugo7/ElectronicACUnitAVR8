/*
 * Timers.c
 *
 * Created: 28/2/2017 3:10:03 a.m.
 *  Author: IoT SolucioneX
 */ 

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "timers.h"

#ifdef DEBUG_TASK
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Global local variables ---//

static volatile tTime g_timeMills;      //Milliseconds counter from last boot


//--- Functions API implementations ---//

/* ***
   FUNCTION: void Timer2Init(void)
   DESCRIPTION: Use Timer2 for management tasks every 1ms the OCCR2A occurred
                Task Examples: Air Dist. Motor moving, Heartbeat LED Blink, etc...
                
   PARAMETERS: void
   RETURN: void
*** */
void TimerInit(void) {

   //Setup Timer for tasks timing
   TCCR2A |= TIMER_CTC_MODE;	            //Set Timer 2 in CTC Mode, Mode = 0x02
   TIMSK2 |= TIMER_OUTPUT_COMPARE_IEA;    //Timer2 OCCR2A Interrupt Enabled

   //Clear Timer on Compare Match (CTC) Mode setup
   TCNT2 = 0x06;     //Timer counter base
   OCR2A = 0xF9;     //OCRn  = ((Fcpu / CLKprescaler) * DesiredTimeInSeconds) - 1
                     //      = ((8000000 / 32) * 0.001 sec) - 1
                     //      = (250000 * 0.001) - 1
                     //      = 250 - 1 = 249 => 0xF9 hex
                     //OCR2A = 249dec = 1ms timer at 8MHz. 
                     //      = 1 / (8000000 / 32) = (1 / 250000) = 0.000004uS tick
                     //      = 0.000004uS * 249 = 0.0000996uS + 0.000004uS (IRQ set 1 clock cycle)
                     //      = 0.001uS * 1000 = 1ms


   //Start Timer
   TCCR2B |= TIMER_DIV32_PRESCALER;

   #ifdef DEBUG_TASK
      USARTPrintString("<Timer scheduler: Init>\n\n");
   #endif

}

/* ***
   FUNCTION: tTime Now(void)
   DESCRIPTION: Get timer ticks since startup 

   PARAMETERS: void
   RETURN: tTime. In milliseconds
*** */
tTime TimerNow(void) {
   tTime now = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	   now = g_timeMills;
	}

	return now;
}

/* ***
   FUNCTION: tTime Elapsed(tTime since)
   DESCRIPTION: Get elapsed time from since to Now()

   PARAMETERS: tTime.
   RETURN: tTime. In milliseconds
*** */
tTime TimerElapsed(tTime since) {
   tTime now = 0;

   //Disable interrupts
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      now = g_timeMills;
   }

   if (now >= since) {
      return (now - since);
   }

   //Rollover = unsigned long = 32bits
   //         = 0xFFFFFFFF     sec.   min. hrs. days
   //         = 4294967295ms / 1000 / 60 / 60 / 24 = 49.71 days running for a car!!
   return (now + (TIMER_MAX_TIME - since));
}


//--- Timers IRQs ---//

/* ***
   FUNCTION: ISR()
   DESCRIPTION: Timer2 Compare on register OCCR2A Interrupt Service Routine. Just decrement timing
                variables that gonna be used in main() tasks
   
   PARAMETERS: n/a
   RETURN: n/a
*** */
ISR(TIMER2_COMPA_vect, ISR_BLOCK) {

   //Volatile variables must be read from memory on every access and not from register
	tTime tmp = g_timeMills;

   //Increment counter
   g_timeMills = ++tmp;

   //Reset timer counter base
   TCNT2 = 0x06;   

   //Timer2 ISR wakeup automatic in SLEEP_MODE_PWR_SAVE mode
   //sleep_disable();
}
