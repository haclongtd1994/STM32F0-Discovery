
#include "hw_stm32f051r8.h"



void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}
/////////////////////////////////////////////////////////////////////////////
void enable_clock(){
  unsigned int tempreg;
  tempreg = read_reg(RCC_AHBENR, ~(1<<19));
  tempreg |= (1<<19);
  write_reg(RCC_AHBENR, tempreg);

  tempreg = read_reg(RCC_AHBENR, ~(1<<17));
  tempreg |= (1<<17);
  write_reg(RCC_AHBENR, tempreg);
}
void init_pin(){
  //set mode led lc3
  unsigned int tempreg;
  tempreg = read_reg(GPIOC_MODER, ~(0x03<<18));
  tempreg |= (GPIOC_MODER_OUTPUT<<18);
  write_reg(GPIOC_MODER, tempreg);
  //set mode user button
  tempreg = read_reg(GPIOC_MODER, ~(0x03<<0));
  tempreg |= (GPIOA_MODER_INPUT<<0);
  write_reg(GPIOA_MODER, tempreg);
}
void led_on(unsigned int pinnumber){
  write_reg(GPIOC_BSRR, 1u << pinnumber);
}
void led_off(unsigned int pinnumber){
  write_reg(GPIOC_BSRR, 1u<<(pinnumber + 16u));
}

void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}

void main(void)
{
  unsigned int state_idr_reg;
  int led_state=0;
  enable_clock();
  init_pin();
  while(1)
  {
    //polling
    state_idr_reg = read_reg(GPIOA_IDR, 1<<0);
    if(state_idr_reg){
      if(led_state==1){
        led_on(LED_PIN);
        led_state=0;
      }
      else if(led_state == 0){
        led_off(LED_PIN);
        led_state=1;
      }

    }
    /*led_on(PC9_PIN);
    delay(0xff);
    led_off(PC9_PIN);
    delay(0xff);*/
  }
}
