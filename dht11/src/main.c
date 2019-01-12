#include "string.h"
#include "stdio.h"
#include "project.h"

volatile unsigned int state;
unsigned int send=0;
volatile unsigned char rx_data=0;
unsigned char data[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char temp=0;
unsigned int start=0;
unsigned int fire=0;

struct div_t{
  int phandu;
  int chiahet;
};

struct div_t huminity;
struct div_t temperature;

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

struct div_t div(int data){
  struct div_t temp;
  int tam = data;
  temp.chiahet=0;
  while(tam>=10){
    temp.chiahet++;
    tam -= 10;
  }
  temp.phandu = tam;
  return temp;
}


void main(void)
{
  system_init(PREDIV_1, PLL_MUX_12, HSI_DIV_2, DIV_1, SOURCE_PLL, APB1_HCLK_1);
  systick_init();

  for(int m=0;m<20;m++){
    data[m] = 0;
  }
  start=0;temp=0;fire=0;send=0;state =0;
  //SET CLOCK AND INIT PIN OUTPUT
  enable_clock_gpio(PORT_C);
  enable_clock_gpio(PORT_A);
  enable_clock_gpio(PORT_B);

  enable_clock_uart();
  init_gpio_pin(GPIO_PIN, OUTPUT, PORT_C);
  init_gpio_pin(GPIO_PIN_2, OUTPUT, PORT_C);
  init_gpio_pin(Button_A0, INPUT, PORT_A);
  //INIT USART
  init_gpio_pin(TX_PIN, ALTERNATE, PORT_A);
  init_gpio_pin(RX_PIN, ALTERNATE, PORT_A);
  init_alt_pin(TX_PIN, 1, PORT_A);
  init_alt_pin(RX_PIN, 1, PORT_A);
  usart_init();
  //INIT Interrupt
  enable_interrupt_UART1();
  enable_interrupt_EXTI(Button_A0, FALLING, PORT_A, 5, 0x00u);
  //init dht11
  dht11_init();
  //Wait test uart from Rasp if OK: Send OK if not will not send anything and wait loop over
  while(start==0){
    if(rx_data!=0){
      if(rx_data==13){
        data[temp]= '\0';
        if((data[0]=='S')&&(data[1]=='E')&&(data[2]=='N')&&(data[3]=='D'))  {start=1;}
        temp = 0;rx_data=0;
      }else if(rx_data!='J'&&rx_data!='^'&&rx_data!='@'){
        data[temp] = (unsigned char)rx_data;
        temp++;
        rx_data=0;
      }
    }
  }
  usart_send_string("OK\r\n");
  while(1)
  {/*
    if(rx_data!=0){
      if(temp==9){
        if((data[0]=='C')&&(data[1]=='O')&&(data[2]=='M')&&(data[3]=='M')&&(data[4]=='A')&&(data[5]=='N')&&(data[6]=='D')&&(data[7]==' ')&&(data[8]=='1')){
          usart_send_string("OK\r\n");
          set_led_on(GPIO_PIN, PORT_C);
          send=1;
          temp = 0;rx_data=0;
        }
        else if((data[0]=='C')&&(data[1]=='O')&&(data[2]=='M')&&(data[3]=='M')&&(data[4]=='A')&&(data[5]=='N')&&(data[6]=='D')&&(data[7]==' ')&&(data[8]=='0')){
          usart_send_string("OK\r\n");
          set_led_off(GPIO_PIN, PORT_C);
          send=1;
          temp = 0;rx_data=0;
        }
      }
      else if(temp==4){
        if((data[0]=='D')&&(data[1]=='A')&&(data[2]=='T')&&(data[3]=='A')){
          usart_send_string("OK\r\n");
          send=1;
          temp = 0;rx_data=0;
        }
      }
      else{
        data[temp] = (unsigned char)rx_data;
        temp++;
        rx_data=0;
      }
    }*/
    if(rx_data!=0){
      if(rx_data == 13){    //13: \r carri
        data[temp]= '\0';
        if((data[0]==10)&&(data[1]=='C')&&(data[2]=='O')&&(data[3]=='M')&&(data[4]=='M')
                      &&(data[5]=='A')&&(data[6]=='N')&&(data[7]=='D')&&(data[8]==' ')&&(data[9]=='1')&&(data[10]=='\0')){
          set_led_on(GPIO_PIN, PORT_C);
          usart_send_string("OK");usart_send_string("\r\n");
          send=0;
        }
        else if((data[0]==10)&&(data[1]=='C')&&(data[2]=='O')&&(data[3]=='M')&&(data[4]=='M')
                      &&(data[5]=='A')&&(data[6]=='N')&&(data[7]=='D')&&(data[8]==' ')&&(data[9]=='0')&&(data[10]=='\0')){
          set_led_off(GPIO_PIN, PORT_C);
          usart_send_string("OK");usart_send_string("\r\n");
          send=0;
        }
        else if((data[0]==10)&&(data[1]=='D')&&(data[2]=='A')&&(data[3]=='T')&&(data[4]=='A')&&(data[5]=='\0')){
          send=1;
        }
        temp = 0;rx_data=0;
      }else if(rx_data!='J'&&rx_data!='^'&&rx_data!='@'){
        data[temp] = (unsigned char)rx_data;
        temp++;
        rx_data=0;
      }
    }
    if(send==1){
      while(dht11_receive_data()==0);
      //usart_send_string("OK! Receive Data\r\n");
      huminity = div(dht11_data[0]);
      temperature = div(dht11_data[2]);
      delay_ms_systick(500);
      usart_send_1_data(huminity.chiahet);
      usart_send_1_data(huminity.phandu);
      usart_send_string(" ");
      delay_ms_systick(500);
      usart_send_1_data(temperature.chiahet);
      usart_send_1_data(temperature.phandu);
      if(state==1){
        usart_send_string(" 1");
      }
      else{
        usart_send_string(" 0");
      }
      if(dht11_data[2] > 40 && state==1){
        usart_send_string(" 1");
        usart_send_string("\r\n");
        fire=1;
        state=0;
      }
      else{
        usart_send_string(" 0");
        usart_send_string("\r\n");
      }
      send=0;
    }
    if(fire==1){
      set_led_on(GPIO_PIN_2, PORT_C);
    }


    /* This is example for main to read data dht11 and set warring to user
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
        data[temp]= '\0';
        if((data[0]=='o')&&(data[1]=='n')&&(data[2]=='\0'))  set_led_on(LD3_PIN, PORT_C);
        else if((data[0]=='o')&&(data[1]=='f')&&(data[2]=='f')&&(data[3]=='\0'))  set_led_off(LD3_PIN, PORT_C);
        else if((data[0]=='s')&&(data[1]=='e')&&(data[2]=='n')&&(data[3]=='d')&&(data[4]=='\0')) send=1;
        usart_send_string(data);
        usart_send_string("\r\n");
        temp = 0;rx_data=0;
      }else{
        data[temp] = (unsigned char)rx_data;
        temp++;
        rx_data=0;
      }
    }
    if(send){
      while(dht11_receive_data()==0);
      //usart_send_string("OK! Receive Data\r\n");
      huminity = div(dht11_data[0]);
      temperature = div(dht11_data[2]);
      usart_send_string("1 ");
      delay_ms_systick(500);
      usart_send_1_data(huminity.chiahet);
      usart_send_1_data(huminity.phandu);
      usart_send_string(" ");
      delay_ms_systick(500);
      usart_send_1_data(temperature.chiahet);
      usart_send_1_data(temperature.phandu);
      usart_send_string("\r\n");
      if(dht11_data[0] > 40){
        state=1;
      }
      else state=0;
      send=0;
    }
    */

  }
}
