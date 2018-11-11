#include "systick.h"

void systick_init(void){
  unsigned int temp_reg;

  write_reg(SYSTICK_CSR, 0x00000000u);//xoa cac setting trong thanh ghi control
  //CLK Source : Select processor source div = 1 => 48Mhz
  temp_reg = read_reg(SYSTICK_CSR, ~(1<<2));
  temp_reg |= (1<<2);
  write_reg(SYSTICK_CSR, temp_reg);

  write_reg(SYSTICK_CVR, 0x00000000u);
}
void start_systick(unsigned int value){
  unsigned int temp_reg;
  write_reg(SYSTICK_RVR, value);
  write_reg(SYSTICK_CVR, 0);

  temp_reg = read_reg(SYSTICK_CSR, ~(1<<0));
  temp_reg |= (1<<0);
  write_reg(SYSTICK_CSR, temp_reg);
}
unsigned int get_flag_systick(void){
  unsigned int temp_reg;

  temp_reg = read_reg(SYSTICK_CSR, (1<<16));
  temp_reg >>= 16;
  return temp_reg;
}
void delay_ms_systick(unsigned int time){
  start_systick(0xbb7f);//delay 1 ms for source clock = 48Mhz
  while(time--){
    write_reg(SYSTICK_CVR, 0);
    while(get_flag_systick() == 0);
  }
}
void delay_us_systick(unsigned int time){
  start_systick(0x2f);//delay 1 us for source clock = 48Mhz - tru cho thoi gian cai dat
  while(time--){
    write_reg(SYSTICK_CVR, 0);
    while(get_flag_systick() == 0);
  }
}
