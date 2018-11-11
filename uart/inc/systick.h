#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "project.h"

extern void systick_init(void);
extern void start_systick(unsigned int value);
extern unsigned int get_flag_systick(void);
extern void delay_ms_systick(unsigned int time);
extern void delay_us_systick(unsigned int time);

#endif
