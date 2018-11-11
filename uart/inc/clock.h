#ifndef __CLOCK_H__
#define __CLOCK_H__
#include "project.h"

extern void system_init(PREDIV_ATTR hse_prediv, PLLMUX_ATTR pllmux, PLLSRC_ATTR pllsrc, AHBDIV_ATTR ahb_div, SYSTEMSOURCE_ATTR system_source, APB1HCLK_ATTR apb1_div);
extern void enable_clock_gpio(PORT port);
extern void enable_clock_uart(void);

#endif
