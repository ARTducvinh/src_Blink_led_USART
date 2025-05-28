#ifndef STM32F401XX_H
#define STM32F401XX_H

#include <stdint.h>

#define GPIOC_BASE         0x40020800U
#define GPIOC_MODER        (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_OTYPER       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_OSPEEDR      (*(volatile uint32_t *)(GPIOC_BASE + 0x08))
#define GPIOC_PUPDR        (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_BSRR         (*(volatile uint32_t *)(GPIOC_BASE + 0x18))

#define RCC_BASE           0x40023800U
#define RCC_AHB1ENR        (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_AHB1ENR_GPIOCEN (1U << 2)

#endif
