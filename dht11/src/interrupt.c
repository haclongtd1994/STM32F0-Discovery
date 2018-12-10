#include "interrupt.h"
volatile unsigned int state=0;
volatile unsigned char rx_data;

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
void Interrupt_Extern_0(void){
  //interrupt for A0, B0, C0, D0, E0, F0
  if(read_reg(EXTI_PR, (1<<0))==0x01){
    state =! state;
  }
  //Xoa ngat EXTI va NVIC
  write_reg(EXTI_PR, (1<<0));
  write_reg(NVIC_ICPR, (1<<5));
}
void Interrupt_Uart_1_Function(void){
  //interrupt usart 1
  volatile unsigned int temp;
  temp = read_reg(USART_ISR, (1<<6));//Read Flag TC
  if(temp != 0){
    write_reg(USART_ICR, (1<<6));//clear flag TC
  }
  temp = read_reg(USART_ISR, (1<<5));
  if(temp != 0){
    rx_data = read_reg(USART_RDR, 0x000000ffu);
    write_reg(USART_RQR, (1<<3));
  }
}
/////////////////////////////////////////////////////////////////////////////

void enable_interrupt_EXTI(unsigned int pin, EXTI_Triger triger, PORT port, unsigned int id, unsigned int priority){
  if(pin>15) return;
  unsigned int temp_reg;
  ////////////////////////////Interrupt periph///////////////////////////////
  //EXTI_reg
  temp_reg = read_reg(EXTI_IMR, ~(1<<pin));
  temp_reg |= (1<<pin);
  write_reg(EXTI_IMR, temp_reg);
  if(triger == RISING){
    temp_reg = read_reg(EXTI_RTSR, ~(1<<pin));
    temp_reg |= (1<<pin);
    write_reg(EXTI_RTSR, temp_reg);
  }
  else if(triger==FALLING){
    temp_reg = read_reg(EXTI_FTSR, ~(1<<pin));
    temp_reg |= (1<<pin);
    write_reg(EXTI_FTSR, temp_reg);
  }
  //SYSCFG_reg
  if(pin<4){
    temp_reg = read_reg(SYSCFG_EXTICR1, ~((0x0f)<<(pin*4)));
    temp_reg |= port<<(pin*4);
    write_reg(SYSCFG_EXTICR1, temp_reg);
  }else if(pin<8&&pin>=4){
    temp_reg = read_reg(SYSCFG_EXTICR1, ~((0x0f)<<(pin*4)-16));
    temp_reg |= port<<(pin*4)-16;
    write_reg(SYSCFG_EXTICR1, temp_reg);
  }else if(pin<12&&pin>=8){
    temp_reg = read_reg(SYSCFG_EXTICR1, ~((0x0f)<<(pin*4)-32));
    temp_reg |= port<<(pin*4)-32;
    write_reg(SYSCFG_EXTICR1, temp_reg);
  }else if(pin>=12){
    temp_reg = read_reg(SYSCFG_EXTICR1, ~((0x0f)<<(pin*4)-48));
    temp_reg |= port<<(pin*4)-48;
    write_reg(SYSCFG_EXTICR1, temp_reg);
  }
  //////////////////////////////////////////////////////////////////////////
  /////////////////////NVIC/////////////////////////////////////////////////
  if(id<4){
    temp_reg = read_reg(NVIC_IPR0, ~((0xff)<<(id*8)));
    temp_reg |= priority<<(id*8)+6;
    write_reg(NVIC_IPR0, temp_reg);
  }else if(id<8&&id>=4){
    temp_reg = read_reg(NVIC_IPR1, ~((0xff)<<(id*8)-32));
    temp_reg |= priority<<(id*8)-32+6;
    write_reg(NVIC_IPR1, temp_reg);
  }else if(id<12&&id>=8){
    temp_reg = read_reg(NVIC_IPR2, ~((0xff)<<(id*8)-64));
    temp_reg |= priority<<(id*8)-64+6;
    write_reg(NVIC_IPR2, temp_reg);
  }else if(id>=12){
    temp_reg = read_reg(NVIC_IPR3, ~((0xff)<<(id*8)-96));
    temp_reg |= priority<<(id*8)-96+6;
    write_reg(NVIC_IPR3, temp_reg);
  }
  temp_reg = read_reg(NVIC_ISER, ~(1<<id));
  temp_reg |= (1<<id);
  write_reg(NVIC_ISER, temp_reg);
  ///////////////////////////////////////////////////////////////////////////
  //Enable global
  asm("cpsie i");
}
void enable_interrupt_UART1(void){
  unsigned int temp_reg;
  ////////////////////////////USART//////////////////////////////////////////
  ///////////////////////////ID ngat = 27///////////////////////////////////
  //xoa co ngat va tat truyen nhan du lieu
  write_reg(USART_RQR, 0xffffffffu);
  write_reg(USART_ICR, 0xffffffffu);
  //cho phep ngat tx khi truyen xong do bit TC bao
  temp_reg = read_reg(USART_CR1,~ (1<<6));
  temp_reg |= (1<<6);
  write_reg(USART_CR1, temp_reg);
  //cho phep ngat khi data ready.
  temp_reg = read_reg(USART_CR1,~ (1<<5));
  temp_reg |= (1<<5);
  write_reg(USART_CR1, temp_reg);
  //set interrupt
  temp_reg = read_reg(NVIC_ISER, ~(1<<27));
  temp_reg |= (1<<27);
  write_reg(NVIC_ISER, temp_reg);

  temp_reg = read_reg(NVIC_IPR6, ~(0xff<<24));
  temp_reg |= (0x00<<24);
  write_reg(NVIC_IPR6, temp_reg);
  ///////////////////////////////////////////////////////////////////////////
}
