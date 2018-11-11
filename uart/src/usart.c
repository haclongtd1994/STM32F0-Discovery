#include "project.h"

void usart_init(void){
  unsigned int temp_reg;
  //Tat bo usart
  temp_reg = read_reg(USART_CR1,~(1<<0));
  write_reg(USART_CR1, temp_reg);
  //1 Start bit, 8 data bits, n stop bits
  temp_reg = read_reg(USART_CR1,~(1<<12));
  write_reg(USART_CR1, temp_reg);
  temp_reg = read_reg(USART_CR1,~(1<<28));
  write_reg(USART_CR1, temp_reg);
  //Parity control disabled
  temp_reg = read_reg(USART_CR1, ~(1<<10));
  write_reg(USART_CR1, temp_reg);
  //stop bit =1
  temp_reg = read_reg(USART_CR2, ~(0x3<<12));
  write_reg(USART_CR1, temp_reg);
  //Chon oversampling de tinh Baudrate
  temp_reg = read_reg(USART_CR1, ~(1<<15));
  write_reg(USART_CR1, temp_reg);
  //Tinh Baudrate: 8.000.000 / 9600 = 833 dec -> hex: 341u
  write_reg(USART_BRR, 0x341u);
  //Bat lai usart enable
  temp_reg = read_reg(USART_CR1,~(1<<0));
  temp_reg |= (1<<0);
  write_reg(USART_CR1, temp_reg);
  //Bat cho phep tx
  temp_reg = read_reg(USART_CR1,~(1<<3));
  temp_reg |= (1<<3);
  write_reg(USART_CR1, temp_reg);
  //Bat cho phep RX
  temp_reg = read_reg(USART_CR1,~(1<<2));
  temp_reg |= (1<<2);
  write_reg(USART_CR1, temp_reg);
}
char usart_send_byte(unsigned char data){
  unsigned int temp_reg;
  char state=0;
  temp_reg = read_reg(USART_ISR, (1<<7));
  if(temp_reg != 0){
    write_reg(USART_TDR, (unsigned int)data);
  }
  else state = -1;
  return state;
}

char usart_send_string(unsigned char *str){
  char state = 0;
  while(*str){
    if(usart_send_byte(*str) == 0){
      str++;
    }
    else state=-1;
  }
  return state;
}
