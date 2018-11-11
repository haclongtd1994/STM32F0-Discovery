#include "dht11.h"

int dht11_data[5]={0,0,0,0,0};

void dht11_init(){
  unsigned int temp_reg;
  init_gpio_pin(DHT11_PIN, OUTPUT, PORT_B);
  temp_reg = read_reg(GPIO_OSPEEDR(PORT_B), ~(0x3<<DHT11_PIN*2));
  temp_reg |= (0x3<<DHT11_PIN*2);
  write_reg(GPIO_OSPEEDR(PORT_B), temp_reg);
  set_led_on(DHT11_PIN, PORT_B);
}
unsigned int read_data_dht11(void){
  unsigned int temp_reg;
  temp_reg = read_reg(GPIO_IDR(PORT_B), (1<<DHT11_PIN));
  temp_reg = temp_reg>>DHT11_PIN;
  return temp_reg;
}
unsigned int dht11_receive_data(){
  unsigned int laststate = 0x01;
  unsigned int counter = 0;
  unsigned int j=0,i;

  dht11_data[0] = dht11_data[1] = dht11_data[2] = dht11_data[3] = dht11_data[4] = 0;
  init_gpio_pin(DHT11_PIN, OUTPUT, PORT_B);
  set_led_off(DHT11_PIN, PORT_B);
  delay_ms_systick(18);

  set_led_on(DHT11_PIN, PORT_B);
  delay_us_systick(40);

  init_gpio_pin(DHT11_PIN, INPUT, PORT_B);
  for(i=0;i<85;i++){
    counter = 0;
    while(read_data_dht11() == laststate){
      counter++;
      delay_us_systick(1);
      if(counter == 255) break;
    }
    laststate = read_data_dht11();
    if(counter == 255) break;
    if((i>=4)&&(i%2==0)){
      dht11_data[j/8] = dht11_data[j/8]<<1;
      if(counter > 12)  dht11_data[j/8] |= 1;
      j++;
    }
  }
  if((j>=40)&&(dht11_data[4] = (dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3]) & 0xff)){
    return 1;
  }
  else{
    return 0;
  }
}
