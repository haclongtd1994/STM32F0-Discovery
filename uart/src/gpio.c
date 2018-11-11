#include "gpio.h"

void init_gpio_pin(unsigned int pin, MODER moder, PORT port){
  unsigned int temp_reg;
  temp_reg = read_reg(GPIO_MODER(port), ~(0x03<<(pin*2)));
  temp_reg |= (moder<<(pin*2));
  write_reg(GPIO_MODER(port), temp_reg);
}
void set_led_on(unsigned int pin, PORT port){
  write_reg(GPIO_BSRR(port), (1<<pin));
}
void set_led_off(unsigned int pin, PORT port){
  write_reg(GPIO_BSRR(port), (1<<pin+16));
}
void init_alt_pin(unsigned int pin, unsigned int alt, PORT port){
  unsigned int temp_reg;
  if(pin<=7){
    temp_reg = read_reg(GPIO_AFRL(port),~ (0xf<<pin*4));
    temp_reg |= (alt<<pin*4);
    write_reg(GPIO_AFRL(port), temp_reg);
  }
  else if(pin>7&&pin<=15){
    temp_reg = read_reg(GPIO_AFRH(port),~ (0xf<<pin*4-32));
    temp_reg |= (alt<<pin*4-32);
    write_reg(GPIO_AFRH(port), temp_reg);
  }
  else  return;
}
