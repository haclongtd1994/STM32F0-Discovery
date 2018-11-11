#ifndef __GPIO_H__
#define __GPIO_H__
#include "project.h"

extern void init_gpio_pin(unsigned int pin, MODER moder, PORT port);
extern void set_led_on(unsigned int pin, PORT port);
extern void set_led_off(unsigned int pin, PORT port);
//setting all pin to alternal function.
void init_alt_pin(unsigned int pin, unsigned int alt, PORT port);


#endif
