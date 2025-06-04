#ifndef __STM32F401XX_H
#define __STM32F401XX_H

#include <stdint.h>

/* Địa chỉ base của các bus */
#define PERIPH_BASE           ((uint32_t)0x40000000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)

/* Địa chỉ base của các ngoại vi */
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00)
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800)
#define NVIC_ISER_BASE        (0xE000E100UL)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)
#define FLASH_BASE            (0x40023C00UL)

/* Cấu trúc thanh ghi RCC */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t RESERVED0[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t RESERVED2[2];
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    // ... các thanh ghi khác nếu cần
} RCC_TypeDef;

#define RCC                 ((RCC_TypeDef *) RCC_BASE)

/* Cấu trúc thanh ghi GPIO */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)

/* Cấu trúc thanh ghi USART */
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

#define USART2              ((USART_TypeDef *) USART2_BASE)

/* Cấu trúc thanh ghi TIM */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    // ... các thanh ghi khác nếu cần
} TIM_TypeDef;

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)

/* Cấu trúc thanh ghi EXTI */
typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)

/* Cấu trúc thanh ghi SYSCFG */
typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    // ... các thanh ghi khác nếu cần
} SYSCFG_TypeDef;

#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)

/* NVIC: chỉ cần define macro thao tác ISER/ICER nếu cần */
#define NVIC_ISER           ((volatile uint32_t *) NVIC_ISER_BASE)

/* Cấu trúc thanh ghi PWR */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_TypeDef;

#define PWR                 ((PWR_TypeDef *) PWR_BASE)

/* Cấu trúc thanh ghi FLASH */
typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t OPTCR;
} FLASH_TypeDef;

#define FLASH               ((FLASH_TypeDef *) FLASH_BASE)

/* Các macro bit cho RCC, GPIO, USART */
#define RCC_AHB1ENR_GPIOAEN     (1U << 0)
#define RCC_AHB1ENR_GPIOBEN     (1U << 1)
#define RCC_AHB1ENR_GPIOCEN     (1U << 2)
#define RCC_APB1ENR_USART2EN    (1U << 17)
#define RCC_APB1ENR_PWREN       (1U << 28)

#endif