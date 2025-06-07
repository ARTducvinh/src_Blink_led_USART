// === FILE: usart.c ===
#include "stm32f401xx.h"
#include "usart.h"
#include "state.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>

extern volatile uint32_t last_command_tick;
extern volatile uint32_t blink_interval_ms;
extern volatile LED_State_t led_state;

void USART2_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // PA2, PA3: alternate function 7 (USART2)
    GPIOA->MODER &= ~((3U << (2*2)) | (3U << (3*2)));
    GPIOA->MODER |=  (2U << (2*2)) | (2U << (3*2));
    GPIOA->AFR[0] &= ~((0xFU << (2*4)) | (0xFU << (3*4)));
    GPIOA->AFR[0] |=  (7U << (2*4)) | (7U << (3*4));

    USART2->BRR = 42000000 / 115200; // Giả sử APB1 clock 42MHz
    USART2->CR1 |= (1U << 13) | (1U << 3) | (1U << 2); // UE, TE, RE
    USART2->CR1 |= (1U << 5); // RXNEIE
    NVIC_ISER[1] = (1U << 6); // USART2_IRQn = 38 (bit 6 của ISER[1])
}

void USART2_SendChar(char c) {
    while (!(USART2->SR & (1U << 7))); // TXE
    USART2->DR = c;
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

// Hàm chuyển uint32_t sang chuỗi (base 10)
static void utoa_simple(uint32_t val, char *buf) {
    char tmp[12];
    int i = 0, j = 0;
    if (val == 0) {
        buf[0] = '0'; buf[1] = 0; return;
    }
    while (val > 0) {
        tmp[i++] = (val % 10) + '0';
        val /= 10;
    }
    while (i--) buf[j++] = tmp[i];
    buf[j] = 0;
}

// USART2 IRQ Handler: nhận từng ký tự và xử lý lệnh đơn giản
void USART2_IRQHandler(void) {
    static char tbuf[8];
    static uint8_t t_index = 0;

    if (USART2->SR & (1U << 5)) { // RXNE
        char ch = USART2->DR;
        if (ch == '\r' || ch == '\n') {
            if (t_index > 1 && tbuf[0] == 't') {
                tbuf[t_index] = 0;
                uint32_t val = atoi(&tbuf[1]);
                if (val > 0 && val <= 10000) {
                    led_set_blink_interval(val);
                    USART2_SendString("Blink interval set to ");
                    char numbuf[12];
                    utoa_simple(val, numbuf);
                    USART2_SendString(numbuf);
                    USART2_SendString("ms\r\n");
                } else {
                    USART2_SendString("Invalid interval\r\n");
                }
            }
            t_index = 0;
            return;
        }

        // Lệnh đơn ký tự
        if (ch == '1') {
            led_blink_start(500);
            last_command_tick = 0;
            USART2_SendString("LED started blinking (interval: 500ms)\r\n");
        } else if (ch == '0') {
            led_blink_stop();
            last_command_tick = 0;
            USART2_SendString("LED turned off\r\n");
        } else if (ch == 'i') {
            if (led_state == LED_STATE_BLINKING)
                USART2_SendString("LED status: BLINKING\r\n");
            else if (led_state == LED_STATE_OFF)
                USART2_SendString("LED status: OFF\r\n");
            else if (led_state == LED_STATE_ERROR)
                USART2_SendString("LED status: ERROR\r\n");
            else
                USART2_SendString("LED status: ON\r\n");
        } else if (ch == 't') {
            tbuf[0] = 't';
            t_index = 1;
        } else if (t_index > 0 && t_index < sizeof(tbuf) - 1) {
            tbuf[t_index++] = ch;
        }
    }
}
