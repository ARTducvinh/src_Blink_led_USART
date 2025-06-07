// === FILE: gpio.c ===
#include "stm32f401xx.h"
#include "gpio.h"
#include "state.h"

extern volatile uint32_t blink_interval_ms;
extern volatile LED_State_t led_state;

void GPIO_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Bật clock cho GPIOC
    GPIOC->MODER &= ~(3U << (13 * 2));   // Clear mode PC13
    GPIOC->MODER |=  (1U << (13 * 2));   // PC13 output
    GPIOC->OTYPER &= ~(1U << 13);        // Push-pull
    GPIOC->OSPEEDR |= (3U << (13 * 2));  // High speed
    GPIOC->PUPDR &= ~(3U << (13 * 2));   // No pull
    LED_Set(1);                          // Tắt LED lúc khởi động
}

void LED_Set(int on) {
    if (on)
        GPIOC->BSRR = (1U << (13 + 16)); // PC13 = 0 (LED sáng)
    else
        GPIOC->BSRR = (1U << 13);        // PC13 = 1 (LED tắt)
}

void LED_Toggle(void) {
    if (GPIOC->ODR & (1U << 13))
        GPIOC->BSRR = (1U << (13 + 16)); // Đang tắt -> bật
    else
        GPIOC->BSRR = (1U << 13);        // Đang bật -> tắt
}

// Nếu cần LED báo lỗi trên PC14 (ví dụ)
void LED_Error(int on) {
    if (on)
        GPIOC->BSRR = (1U << (14 + 16)); // PC14 = 0 (LED đỏ sáng)
    else
        GPIOC->BSRR = (1U << 14);        // PC14 = 1 (LED đỏ tắt)
}

void led_set_blink_interval(uint32_t interval_ms) {
    blink_interval_ms = interval_ms;
}

void led_blink_start(uint32_t interval_ms) {
    blink_interval_ms = interval_ms;
    led_state = LED_STATE_BLINKING;
}

void led_blink_stop(void) {
    led_state = LED_STATE_OFF;
    LED_Set(0); // Tắt LED khi dừng nhấp nháy
}
