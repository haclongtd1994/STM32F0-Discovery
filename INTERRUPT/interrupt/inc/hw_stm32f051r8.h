#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

/* LED D2 - PA4 */
#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

//RCC
#define BASE_ADD_RCC         0x40021000u
#define RCC_AHBENR          (BASE_ADD_RCC + 0x14u)

//GPIO C
#define BASE_ADD_GPIOC        0x48000800u
#define GPIOC_MODER        (BASE_ADD_GPIOC + 0x00u)
#define GPIOC_MODER_INPUT    0x00u
#define GPIOC_MODER_OUTPUT   0x01u
#define GPIOC_MODER_ANF      0x02u
#define GPIOC_MODER_ANL      0x03u
//GPIO A
#define BASE_ADD_GPIOA        0x48000000u
#define GPIOA_MODER        (BASE_ADD_GPIOA + 0x00u)
#define GPIOA_IDR          (BASE_ADD_GPIOA + 0x10u)
#define GPIOA_MODER_INPUT    0x00u


#define GPIOC_BSRR        (BASE_ADD_GPIOC + 0x18u)
//PC9
#define LED_PIN           9
#define LED_PIN_2         8
//PA0
#define BUTTON_PIN        0
//EXTI
#define BASE_ADD_EXTI      0x40010400u
#define EXTI_IMK           (BASE_ADD_EXTI + 0x00u)    //Mask
#define EXTI_RTSR          (BASE_ADD_EXTI + 0x08u)   //Ngat canh len
#define EXTI_PR            (BASE_ADD_EXTI + 0x14u)  //Co
//SYSCFG
#define BASE_ADD_SYSCFG    0x40010000u
#define SYSCFG_EXTICR1     (BASE_ADD_SYSCFG + 0x08u)

//NVIC
#define NVIC_ISER          0xE000E100u
#define NVIC_ICER          0xE000E180u
#define NVIC_ISPR          0xE000E200u
#define NVIC_ICPR          0xE000E280u
#define NVIC_PRI1          0xE000E404u



/* end file */
#endif /* __HW_STM32F051R8_H__ */
