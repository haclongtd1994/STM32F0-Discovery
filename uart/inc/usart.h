#ifndef __USART_H__
#define __USART_H__
#include "project.h"

extern void usart_init(void);
extern char usart_send_byte(unsigned char data);
extern char usart_send_string(unsigned char *str);

#endif
