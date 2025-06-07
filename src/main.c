// === FILE: main.c ===
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "state.h"
#include "stm32f401xx.h"

extern volatile uint32_t blink_interval_ms;
extern volatile LED_State_t led_state;

int main(void) {
    GPIO_Init();
    USART2_Init();
    TIM1_Init(blink_interval_ms); // Đổi sang dùng TIM1
    TIM3_Init();

    LED_State_t prev_state = LED_STATE_OFF;
    uint32_t prev_interval = blink_interval_ms;

    while (1) {
        // Nếu có hàm xử lý lệnh UART, gọi ở đây
        // USART2_Task();

        // Chỉ cập nhật timer khi trạng thái hoặc interval thay đổi
        if (led_state != prev_state || blink_interval_ms != prev_interval) {
            if (led_state == LED_STATE_BLINKING) {
                TIM1->ARR = blink_interval_ms * 1000 - 1;
                TIM1->CNT = 0;
                TIM1->CR1 |= (1U << 0);
            } else {
                TIM1->CR1 &= ~(1U << 0);
            }
            prev_state = led_state;
            prev_interval = blink_interval_ms;
        }

        // Chỉ cập nhật LED khi KHÔNG ở trạng thái BLINKING
        switch (led_state) {
            case LED_STATE_OFF:
                LED_Set(0);
                LED_Error(0);
                break;
            case LED_STATE_ON:
                LED_Set(1);
                LED_Error(0);
                break;
            case LED_STATE_BLINKING:
                LED_Error(0);
                break;
            case LED_STATE_ERROR:
                LED_Set(0);
                LED_Error(1);
                break;
        }
    }
}
