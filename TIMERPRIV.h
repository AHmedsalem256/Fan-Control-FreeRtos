#ifndef TIMERPRIV_H
#define TIMERPRIV_H


#define TIMSK     *((volatile u8 *)0x59)

#define TCCR0    *((volatile u8 *)0x53)

#define TIFR      *((volatile u8 *)0x58)

#define SREG      *((volatile u8 *)0x5F)

#define TCNT0     *((volatile u8 *)0x52)

#define OCR0      *((volatile u8 *)0x5C)

#endif
