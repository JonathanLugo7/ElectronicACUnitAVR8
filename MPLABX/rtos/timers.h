/*
 * Timers.h
 *
 * Created: 28/2/2017 3:09:51 a.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

//--- Includes ---//


//--- Defines ---//

//Timer 2 setup
#define TIMER_CTC_MODE           ((1 << WGM21))
#define TIMER_OUTPUT_COMPARE_IEA ((1 << OCIE2A))
#define TIMER_DIV32_PRESCALER    ((1 << CS21) | (1 << CS20))      //Pre-scaler of Fcpu/32 = 8000000/32 = 250kHz
#define TIMER_MAX_TIME           0xFFFFFFFF                       //Max time before Counter rollover (32bit counter=4294967295ms)

//TimerRunEvery predefined timers
#define TRE_STOP                       0x0000                     //Dec.: No run
#define TRE_ONE_MSECOND                0x0001                     //1ms
#define TRE_TEN_MSECOND                TRE_ONE_MSECOND * 10       //10ms
#define TRE_TWENTY_MSECOND             TRE_ONE_MSECOND * 20       //20ms
#define TRE_FIFTY_MSECOND              TRE_ONE_MSECOND * 50       //50ms
#define TRE_HUNDRED_MSECOND            TRE_ONE_MSECOND * 100      //100ms
#define TRE_TWOHUNDRED_MSECOND         TRE_ONE_MSECOND * 200      //200ms=1/5s
#define TRE_TWOHUNDRED_HALF_MSECOND    TRE_ONE_MSECOND * 250      //250ms=1/4s
#define TRE_HALF_SECOND                TRE_ONE_MSECOND * 500      //500ms=1/2s
#define TRE_ONE_SECOND                 TRE_ONE_MSECOND * 1000     //1000ms=1s
#define TRE_TWO_SECONDS                TRE_ONE_SECOND * 2         //2000ms=2s
#define TRE_FIVE_SECONDS               TRE_ONE_SECOND * 5         //5000ms=5s
#define TRE_TEN_SECONDS                TRE_ONE_SECOND * 10        //10s=10000ms
#define TRE_HALF_MINUTE                TRE_ONE_SECOND * 30        //1/2min=30000ms
#define TRE_ONE_MINUTE                 TRE_ONE_SECOND * 60        //1min=60000ms


//---- Timer Types ---//
typedef uint32_t tTime;


//---- Functions Prototypes ---//

void  TimerInit(void);
tTime TimerNow(void);
tTime TimerElapsed(tTime since);


#endif /* TIMERS_H_ */
