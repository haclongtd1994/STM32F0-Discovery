#ifndef __HW_STM32F051R9_H__
#define __HW_STM32F051R9_H__
//khai bao dau chuong trinh
typedef unsigned int      u32_t;
typedef unsigned short    u16_t;
typedef unsigned char     u8_t;

#define write_reg(addr, value)      *((unsigned long int *)(addr)) = (value)
#define read_reg(addr, mask)        *((unsigned long int *)(addr)) & (mask)
#define __io              volatile
//RCC_REG
#define BASE_ADDR_RCC     0x40021000u
#define RCC_CR            (BASE_ADDR_RCC + 0x00u)
#define RCC_CFGR          (BASE_ADDR_RCC + 0x04u)
#define RCC_CIR           (BASE_ADDR_RCC + 0x08u)
#define RCC_APB2RSTR      (BASE_ADDR_RCC + 0x0cu)
#define RCC_APB1RSTR      (BASE_ADDR_RCC + 0x10u)
#define RCC_AHBENR        (BASE_ADDR_RCC + 0x14u)
#define RCC_APB2ENR       (BASE_ADDR_RCC + 0x18u)
#define RCC_APB1ENR       (BASE_ADDR_RCC + 0x1cu)
#define RCC_BDCR          (BASE_ADDR_RCC + 0x20u)
#define RCC_CSR           (BASE_ADDR_RCC + 0x24u)
#define RCC_AHBRSTR       (BASE_ADDR_RCC + 0x28u)
#define RCC_CFGR2         (BASE_ADDR_RCC + 0x2cu)
#define RCC_CFGR3         (BASE_ADDR_RCC + 0x30u)
#define RCC_CR2           (BASE_ADDR_RCC + 0x34u)

typedef enum{
  PREDIV_1  = 0x00u,
  PREDIV_2  = 0x01u,
  PREDIV_3  = 0x02u,
  PREDIV_4  = 0x03u,
  PREDIV_5  = 0x04u,
  PREDIV_6  = 0x05u,
  PREDIV_7  = 0x06u,
  PREDIV_8  = 0x07u,
  PREDIV_9  = 0x08u,
  PREDIV_10 = 0x09u,
  PREDIV_11 = 0x0au,
  PREDIV_12 = 0x0bu,
  PREDIV_13 = 0x0cu,
  PREDIV_14 = 0x0du,
  PREDIV_15 = 0x0eu,
  PREDIV_16 = 0x0fu
}PREDIV_ATTR;
typedef enum{
  PLL_MUX_2    =    0x00u,
  PLL_MUX_3    =    0x01u,
  PLL_MUX_4    =    0x02u,
  PLL_MUX_5    =    0x03u,
  PLL_MUX_6    =    0x04u,
  PLL_MUX_7    =    0x05u,
  PLL_MUX_8    =    0x06u,
  PLL_MUX_9    =    0x07u,
  PLL_MUX_10   =    0x08u,
  PLL_MUX_11   =    0x09u,
  PLL_MUX_12   =    0x0au,
  PLL_MUX_13   =    0x0bu,
  PLL_MUX_14   =    0x0cu,
  PLL_MUX_15   =    0x0du,
  PLL_MUX_16   =    0x0eu
}PLLMUX_ATTR;
typedef enum{
  HSI_DIV_2          =     0,
  HSI_DIV_PREDIV     =     1
}PLLSRC_ATTR;
typedef enum{
  DIV_1     =       0x00u,
  DIV_2     =       0x08u,
  DIV_4     =       0x09u,
  DIV_8     =       0x0au,
  DIV_16    =       0x0bu,
  DIV_64    =       0x0cu,
  DIV_128   =       0x0du,
  DIV_256   =       0x0eu,
  DIV_512   =       0x0fu
}AHBDIV_ATTR;
typedef enum{
  SOURCE_HSI    =     0x00u,
  SOURCE_HSE    =     0x01u,
  SOURCE_PLL    =     0x02u
}SYSTEMSOURCE_ATTR;
typedef enum{
  APB1_HCLK_1   =     0x00u,
  APB1_HCLK_2   =     0x04u,
  APB1_HCLK_4   =     0x05u,
  APB1_HCLK_8   =     0x06u,
  APB1_HCLK_16  =     0x07u
}APB1HCLK_ATTR;
//GPIO_REG
#define BASE_ADDR_GPIO          0x48000000u
#define GPIO_MODER(port)        (BASE_ADDR_GPIO + (0x400u * (port)) + 0x00u)
#define GPIO_OTYPER(port)       (BASE_ADDR_GPIO + (0x400u * (port)) + 0x04u)
#define GPIO_OSPEEDR(port)      (BASE_ADDR_GPIO + (0x400u * (port)) + 0x08u)
#define GPIO_PUPDR(port)        (BASE_ADDR_GPIO + (0x400u * (port)) + 0x0cu)
#define GPIO_IDR(port)          (BASE_ADDR_GPIO + (0x400u * (port)) + 0x10u)
#define GPIO_ODR(port)          (BASE_ADDR_GPIO + (0x400u * (port)) + 0x14u)
#define GPIO_BSRR(port)         (BASE_ADDR_GPIO + (0x400u * (port)) + 0x18u)
#define GPIO_LCKR(port)         (BASE_ADDR_GPIO + (0x400u * (port)) + 0x1cu)
#define GPIO_AFRL(port)         (BASE_ADDR_GPIO + (0x400u * (port)) + 0x20u)
#define GPIO_AFRH(port)         (BASE_ADDR_GPIO + (0x400u * (port)) + 0x24u)
#define GPIO_BRR(port)          (BASE_ADDR_GPIO + (0x400u * (port)) + 0x28u)

typedef enum{
  INPUT = 0x00u,
  OUTPUT = 0x01u,
  ALTERNATE = 0x02u,
  ANALOG = 0x03u
}MODER;
typedef enum{
   PORT_A        =          0x00u,
   PORT_B        =          0x01u,
   PORT_C        =          0x02u,
   PORT_D        =          0x03u,
   PORT_E        =          0x04u,
   PORT_F        =          0x05u
}PORT;

//////////////////Ngoai vi////////////////////////////
//Interrupt///////////////////EXTI_reg
#define BASE_ADDR_EXTI      0x40010400u
#define EXTI_IMR            (BASE_ADDR_EXTI + 0x00u)     //set mask for interrupt
#define EXTI_EMR            (BASE_ADDR_EXTI + 0x04u)     //set mask for event
#define EXTI_RTSR           (BASE_ADDR_EXTI + 0x08u)     //Select trigger rising
#define EXTI_FTSR           (BASE_ADDR_EXTI + 0x0cu)     //Select trigger falling
#define EXTI_SWIER          (BASE_ADDR_EXTI + 0x10u)     //Interrupt or event by software
#define EXTI_PR             (BASE_ADDR_EXTI + 0x14u)     //read by 1: selected triger request occurred
typedef enum{
  RISING = 0,
  FALLING = 1
}EXTI_Triger;
//Interrupt///////////////////SYSCFG
#define BASE_ADDR_SYSCFG    0x40010000u
#define SYSCFG_EXTICR1      (BASE_ADDR_SYSCFG + 0x08u)  //Select PA or PB or PC or ... PF
#define SYSCFG_EXTICR2      (BASE_ADDR_SYSCFG + 0x0Cu)  //Select PA or PB or PC or ... PF
#define SYSCFG_EXTICR3      (BASE_ADDR_SYSCFG + 0x10u)  //Select PA or PB or PC or ... PF
#define SYSCFG_EXTICR4      (BASE_ADDR_SYSCFG + 0x14u)  //Select PA or PB or PC or ... PF
//Interrupt///////////////////NVIC
#define NVIC_ISER           0xE000E100u
#define NVIC_ICER           0xE000E180u
#define NVIC_ISPR           0xE000E200u
#define NVIC_ICPR           0xE000E280u
#define NVIC_IPR0           0xE000E400u
#define NVIC_IPR1           0xE000E404u
#define NVIC_IPR2           0xE000E408u
#define NVIC_IPR3           0xE000E40cu
#define NVIC_IPR4           0xE000E410u
#define NVIC_IPR5           0xE000E414u
#define NVIC_IPR6           0xE000E418u
#define NVIC_IPR7           0xE000E41cu
///////////////////////////////////////////////////////
/////////////////////USART////////////////////////////
#define BASE_ADDR_USART1    0x40013800u
#define USART_CR1           (BASE_ADDR_USART1 + 0x00u)
#define USART_CR2           (BASE_ADDR_USART1 + 0x04u)
#define USART_CR3           (BASE_ADDR_USART1 + 0x08u)
#define USART_BRR           (BASE_ADDR_USART1 + 0x0cu)
#define USART_GTPR          (BASE_ADDR_USART1 + 0x10u)
#define USART_RTOR          (BASE_ADDR_USART1 + 0x14u)
#define USART_RQR           (BASE_ADDR_USART1 + 0x18u)
#define USART_ISR           (BASE_ADDR_USART1 + 0x1cu)
#define USART_ICR           (BASE_ADDR_USART1 + 0x20u)
#define USART_RDR           (BASE_ADDR_USART1 + 0x24u)
#define USART_TDR           (BASE_ADDR_USART1 + 0x28u)
///////////////////////////////////////////////////////
////////////////////SYSTICK////////////////////////////
#define SYSTICK_CSR         0xE000E010u
#define SYSTICK_RVR         0xE000E014u
#define SYSTICK_CVR         0xE000E018u
///////////////////////////////////////////////////////
//dht11 PORT_B
#define DHT11_PIN  3

//led pin PORT_C
#define GPIO_PIN    9
#define GPIO_PIN_2    8
//button_pin PORT_A
#define Button_A0  0
//transmit pin usart 1 PORT_A
#define TX_PIN          9
#define RX_PIN          10
#endif
