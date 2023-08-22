/*
 * Common.h
 *
 * Created: 8/7/2016 2:11:45 a. m.
 *  Author: IoT SolucioneX
 */ 

#ifndef COMMON_H_
#define COMMON_H_


#ifndef _NOP
#define _no_operation() do { __asm__ volatile ("nop"); } while (0)
#endif

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

// Pack four individuals byte into 32-bit, MSB first
#define PACK32(msb, b3, b2, lsb) ( ((uint32_t) msb << 24) | \
                                   ((uint32_t) b3  << 16) | \
                                   ((uint32_t) b2  << 8)  | \
                                               lsb )

#define FALSE        0
#define TRUE         1

#define MCU_RESET_CAUSE_POR (1 << PORF)
#define MCU_RESET_CAUSE_EXT (1 << EXTRF)
#define MCU_RESET_CAUSE_BOR (1 << BORF)
#define MCU_RESET_CAUSE_WDT (1 << WDRF)


//--- Functions prototypes ---//


#endif /* COMMON_H_ */