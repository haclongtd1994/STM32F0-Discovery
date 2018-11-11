
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

/* LED D2 - PA4 */
#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

//RCC
#define BASE_ADD_RCC         0x40021000u
#define RCC_AHBENR          (BASE_ADD_RCC + 0x14u)

//GPIO
#define BASE_ADD_GPIO        0x48000800u
#define GPIOC_MODER        (BASE_ADD_GPIO + 0x00u)
#define GPIOC_MODER_INPUT    0x00u
#define GPIOC_MODER_OUTPUT   0x01u
#define GPIOC_MODER_ANF      0x02u
#define GPIOC_MODER_ANL      0x03u

#define GPIOC_BSRR        (BASE_ADD_GPIO + 0x18u)

#define PC9_PIN           9


/* end file */
#endif /* __HW_STM32F051R8_H__ */
