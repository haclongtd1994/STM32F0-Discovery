#include "clock.h"

void system_init(PREDIV_ATTR hse_prediv, PLLMUX_ATTR pllmux, PLLSRC_ATTR pllsrc, AHBDIV_ATTR ahb_div, SYSTEMSOURCE_ATTR system_source, APB1HCLK_ATTR apb1_div){
  u32_t temp_reg;
  volatile u32_t timeout;
  //////////////////////////////////////Chuan bi de cau hinh//////////////////////////
  //tat cac ngat
  write_reg(RCC_CIR, 0x00000000u);
  //Tat bo dao dong noi HSI
  temp_reg = read_reg(RCC_CR,~ 0x00000001u);
  write_reg(RCC_CR, temp_reg);
  //Cho cho bo dao dong HSI tat
  timeout = 0xfff;
  do{
    temp_reg = read_reg(RCC_CR, 0x00000002u);
    timeout--;
  }while((temp_reg!=0)&&(timeout>0));
  //Tat bo PLL
  temp_reg = read_reg(RCC_CR,~ (1<<24));
  write_reg(RCC_CR, temp_reg);
  //Cho cho den khi PLL tat
  timeout = 0xffffffff;
  do{
    temp_reg = read_reg(RCC_CR, (1<<25));
    timeout--;
  }while((temp_reg!=0)&&(timeout>0));
  ////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////Cau hinh cac tham so truyen vao///////////////////////
  //Chon bo chia cho HSE
  temp_reg = read_reg(RCC_CFGR2, ~0xfffffff0u);
  temp_reg |= hse_prediv;
  write_reg(RCC_CFGR2, temp_reg);
  //Chon he so nhan cho PLL
  temp_reg = read_reg(RCC_CFGR, ~(0xf<<18));
  temp_reg |= pllmux<<18;
  write_reg(RCC_CFGR, temp_reg);
  //Chon nguon cap xung cho PLL
  temp_reg = read_reg(RCC_CFGR, ~(0x3<<15));
  temp_reg |= pllsrc<<15;
  write_reg(RCC_CFGR, temp_reg);
  //Bat lai xung cho PLL
  temp_reg = read_reg(RCC_CR,~ (1<<24));
  temp_reg |= (1<<24);
  write_reg(RCC_CR, temp_reg);
  //Cho cho den khi PLL bat
  timeout = 0xffffffff;
  do{
    temp_reg = read_reg(RCC_CR, (1<<25));
    timeout--;
  }while((temp_reg==0)&&(timeout>0));
  //Chon bo chia ahb_div
  temp_reg = read_reg(RCC_CFGR, ~(0xf<<4));
  temp_reg |= ahb_div<<4;
  write_reg(RCC_CFGR, temp_reg);
  //Chon lai nguon cap xung cho he thong
  temp_reg = read_reg(RCC_CFGR,~ (0x3<<0));
  temp_reg |= system_source<<0;
  write_reg(RCC_CFGR, temp_reg);
  //Cho cho he thong chon xung clock san sang
  timeout = 0xffffffff;
  do{
    temp_reg = read_reg(RCC_CFGR, (0x3<<2));
    timeout--;
  }while((temp_reg!=(system_source<<2))&&(timeout>0));
  //chon bo chia apb1s
  temp_reg = read_reg(RCC_CFGR, ~(0x7<<8));
  temp_reg |= apb1_div<<8;
  write_reg(RCC_CFGR, temp_reg);
  //Chon nguon cap cho bo usart
  temp_reg = read_reg(RCC_CFGR3, ~(0x3<<0));
  temp_reg |= 3<<0;
  write_reg(RCC_CFGR3, temp_reg);
}
void enable_clock_gpio(PORT port){
  unsigned int temp_reg;
  temp_reg = read_reg(RCC_AHBENR, ~(1<<(17 + (port))));
  temp_reg |= (1<<(17 + (port)));
  write_reg(RCC_AHBENR, temp_reg);
}
void enable_clock_uart(void){
  //enable clock for usart 1
  unsigned int temp_reg;
  temp_reg = read_reg(RCC_APB2ENR, ~(1<<14));
  temp_reg |= (1<<14);
  write_reg(RCC_APB2ENR, temp_reg);
}
