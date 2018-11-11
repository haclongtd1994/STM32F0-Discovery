//check button if press: 1 , not press: 0

#include "project.h"

int check_button_polling(unsigned int pin, PORT port){
  if(read_reg(GPIO_IDR(port), (1<<pin))){
    delay(0x0f);
    if(read_reg(GPIO_IDR(port), (1<<pin))){
      while(read_reg(GPIO_IDR(port), (1<<pin)));
      return 1;
    }
  }
  return 0;
}
