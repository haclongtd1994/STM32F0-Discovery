#include "string.h"
#include "project.h"
volatile unsigned int state;
volatile unsigned char rx_data;
unsigned char data[64];
unsigned char temp=0;

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
  system_init(PREDIV_1, PLL_MUX_12, HSI_DIV_2, DIV_1, SOURCE_PLL, APB1_HCLK_1);
  systick_init();
  //SET CLOCK AND INIT PIN OUTPUT
  enable_clock_gpio(PORT_C);
  enable_clock_gpio(PORT_A);
  enable_clock_uart();
  init_gpio_pin(LD3_PIN, OUTPUT, PORT_C);
  init_gpio_pin(LD4_PIN, OUTPUT, PORT_C);
  init_gpio_pin(Button_A0, INPUT, PORT_A);
  //INIT USART
  init_gpio_pin(TX_PIN, ALTERNATE, PORT_A);
  init_gpio_pin(RX_PIN, ALTERNATE, PORT_A);
  init_alt_pin(TX_PIN, 1, PORT_A);
  init_alt_pin(RX_PIN, 1, PORT_A);
  usart_init();
  //INIT Interrupt
  enable_interrupt_UART1();
  enable_interrupt_EXTI(Button_A0, RISING, PORT_A, 5, 0x01u);

  usart_send_string("Hello my computer!");
  while(1)
  {
    if(state==1){
      set_led_on(LD3_PIN, PORT_C);
      set_led_on(LD4_PIN, PORT_C);
      delay_ms_systick(1000);
      set_led_off(LD3_PIN, PORT_C);
      set_led_off(LD4_PIN, PORT_C);
      delay_ms_systick(1000);
    }
    if(rx_data!=0){
      if(rx_data == 47){
        usart_send_string(data);
        temp = 0;
      }
      data[temp] = (unsigned char)rx_data;
      temp++;
      rx_data = 0;
    }
  }
}
