// config clock
#include "stm32f401xx.h"

void SystemInit(void)
{
    RCC->CR |= (1U << 16);
    while (!(RCC->CR & (1U << 17)));

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= (1U << 14);

    FLASH->ACR |= (1U << 9) | (1U << 10) | (1U << 8) | (2U << 0);

    uint32_t PLLM = 25;
    uint32_t PLLN = 336;
    uint32_t PLLP = 2;
    uint32_t PLLSRC = 1;
    uint32_t PLLQ = 7;

    RCC->PLLCFGR = (PLLM << 0) | (PLLN << 6) | (1U << 16) | (PLLSRC << 22) | (PLLQ << 24);

    RCC->CR |= (1U << 24);
    while (!(RCC->CR & (1U << 25)));

    RCC->CFGR &= ~(3U << 0);
    RCC->CFGR |= (2U << 0);

    RCC->CFGR &= ~((0xF << 4) | (0x7 << 10) | (0x7 << 13));
    RCC->CFGR |= (0U << 4);   
    RCC->CFGR |= (4U << 10);  // PPRE1_DIV2 (APB1 = 42MHz)
    RCC->CFGR |= (0U << 13);  

    while (((RCC->CFGR >> 2) & 0x3) != 0x2);
}