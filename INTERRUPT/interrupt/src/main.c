
#include "hw_stm32f051r8.h"

unsigned int led_state=0;
void led_on(unsigned int pinnumber);
void led_off(unsigned int pinnumber);
////////////////////////////////////////////////
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
void EXTI0_1_IRQHandler(void){
  unsigned int temp=0;//check pending
  temp = read_reg(EXTI_PR, (1<<0));
  if(temp == 0x01){
    led_state =! led_state;
  }
  //Xoa co Ngat ngoai vi
  temp = (1<<0);
  write_reg(EXTI_PR, temp);
  //Xoa ngat NVIC
  write_reg(NVIC_ICPR, (1<<5));
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
  tempreg = read_reg(GPIOC_MODER, ~(0x03<<16));
  tempreg |= (GPIOC_MODER_OUTPUT<<16);
  write_reg(GPIOC_MODER, tempreg);
  //set mode user button
  tempreg = read_reg(GPIOA_MODER, ~(0x03<<0));
  tempreg |= (GPIOA_MODER_INPUT<<0);
  write_reg(GPIOA_MODER, tempreg);
}
void init_interrupt(){
  //enable interrupt EXTI0
  unsigned int tempreg;
  tempreg = read_reg(EXTI_IMK, ~(1<<0));
  tempreg |= (1<<0);
  write_reg(EXTI_IMK, tempreg);

  tempreg = read_reg(EXTI_RTSR, ~(1<<0));
  tempreg |= (1<<0);
  write_reg(EXTI_RTSR, tempreg);
  //SYSCFG_EXTICR1
  tempreg = read_reg(SYSCFG_EXTICR1, ~(0x0F<<0));
  tempreg |= (0x00<<0);
  write_reg(SYSCFG_EXTICR1, tempreg);
  //NVIC
  tempreg = read_reg(NVIC_PRI1, ~(0xFF<<8));
  tempreg |= (0x01<<14);
  write_reg(NVIC_PRI1, tempreg);
  tempreg = read_reg(NVIC_ISER, ~(1<<5));
  tempreg |= (1<<5);
  write_reg(NVIC_ISER, tempreg);
  //enable global interrupts
  asm("cpsie i");
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
  unsigned int temp;
  enable_clock();
  init_pin();
  init_interrupt();
  while(1)
  {
    if(led_state==1){
      led_on(LED_PIN_2);
      led_on(LED_PIN);
      delay(0xff);
      led_off(LED_PIN_2);
      led_off(LED_PIN);
      delay(0xff);
    }
  }
}
