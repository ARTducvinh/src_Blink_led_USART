#include "stm32f401xx.h"
#include "timer.h"
#include "state.h"
#include "gpio.h"

// TIM1: Điều khiển nhấp nháy LED (APB2)
void TIM1_Init(uint32_t interval_ms) {
    RCC->APB2ENR |= (1U << 0); // TIM1EN (bit 0)
    TIM1->PSC = 84 - 1;        // 84MHz/84 = 1MHz (1us/tick)
    TIM1->ARR = interval_ms * 1000 - 1; // interval_ms ms
    TIM1->DIER |= (1U << 0);   // UIE: Update interrupt enable
    NVIC_ISER[0] = (1U << 25); // TIM1_UP_TIM10_IRQn = 25
}

// TIM3: Watchdog timeout 1s (APB1)
void TIM3_Init(void) {
    RCC->APB1ENR |= (1U << 1); // TIM3EN (bit 1)
    TIM_TypeDef *TIM3 = (TIM_TypeDef *)(APB1PERIPH_BASE + 0x0400);
    TIM3->PSC = 84 - 1;        // 1MHz
    TIM3->ARR = 1000000 - 1;   // 1s (1MHz * 1s)
    TIM3->DIER |= (1U << 0);   // UIE
    NVIC_ISER[0] = (1U << 29); // TIM3_IRQn = 29
    TIM3->CR1 |= (1U << 0);    // CEN
}

// TIM1 IRQ Handler: nhấp nháy LED
void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & (1U << 0)) {
        TIM1->SR &= ~(1U << 0);
        if (led_state == LED_STATE_BLINKING) {
            LED_Toggle();
        }
    }
}

// TIM3 IRQ Handler: Watchdog
void TIM3_IRQHandler(void) {
    TIM_TypeDef *TIM3 = (TIM_TypeDef *)(APB1PERIPH_BASE + 0x0400);
    if (TIM3->SR & (1U << 0)) {
        TIM3->SR &= ~(1U << 0);
        last_command_tick++;
        if (last_command_tick >= 10 && led_state != LED_STATE_ERROR) {
            led_state = LED_STATE_ERROR;
            LED_Error(1);
        }
    }
}