#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "project.h"

extern volatile unsigned int state;
extern volatile unsigned char rx_data;


extern void enable_interrupt_EXTI(unsigned int pin, EXTI_Triger triger, PORT port, unsigned int id, unsigned int priority);
extern void enable_interrupt_UART1(void);

#endif
