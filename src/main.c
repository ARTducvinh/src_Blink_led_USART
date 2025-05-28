#include "stm32f401xx.h"
#include <stdio.h>

int main(void)
{
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |= (1 << (13 * 2));
    GPIOC_OTYPER &= ~(1 << 13);
    GPIOC_OSPEEDR &= ~(3 << (13 * 2));
    GPIOC_OSPEEDR |= (3 << (13 * 2));
    GPIOC_PUPDR &= ~(3 << (13 * 2));

    while (1)
    {
        GPIOC_BSRR = (1 << 13);
        for (volatile uint32_t i = 0; i < 200000; i++);

        GPIOC_BSRR = (1 << (13 + 16));
        for (volatile uint32_t i = 0; i < 100000; i++);
    }
}
