#include "stm32f401xx.h"

void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms * 21000; i++) {
        __asm__("nop");
    }
}

// Khởi tạo USART2 ở baudrate 115200, 8N1, bật ngắt RX
void usart2_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~((3 << (2*2)) | (3 << (3*2)));
    GPIOA->MODER |=  (2 << (2*2)) | (2 << (3*2));
    GPIOA->AFR[0] &= ~((0xF << (2*4)) | (0xF << (3*4)));
    GPIOA->AFR[0] |=  (7 << (2*4)) | (7 << (3*4)); 

    USART2->BRR = 364; // 42MHz/115200
    USART2->CR1 |= (1 << 13) | (1 << 3) | (1 << 2); 

    USART2->CR1 |= (1 << 5); 

    NVIC_ISER[1] = (1 << 6);
}

// Gửi 1 ký tự qua USART2
void usart2_send_char(char c)
{
    while (!(USART2->SR & (1 << 7)));
    USART2->DR = c;
}

// Gửi chuỗi ký tự qua USART2
void usart2_send_str(const char* s)
{
    while (*s) {
        usart2_send_char(*s++);
    }
}

// Khởi tạo GPIOC13 làm output điều khiển LED
void gpio_led_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER &= ~(3 << (13 * 2));
    GPIOC->MODER |= (1 << (13 * 2));
    GPIOC->OTYPER &= ~(1 << 13);
    GPIOC->OSPEEDR |= (3 << (13 * 2));
    GPIOC->PUPDR &= ~(3 << (13 * 2));
    GPIOC->BSRR = (1 << (13 + 16)); // bật LED (PC13 = 0)
}

// Ngắt USART2: nhận ký tự '1' bật LED, '0' tắt LED
void USART2_IRQHandler(void)
{
    if (USART2->SR & (1 << 5)) { 
        char c = USART2->DR; // tự động xoá cờ ngắt
        if (c == '1') {
            GPIOC->BSRR = (1 << (13 + 16)); 
        } else if (c == '0') {
            GPIOC->BSRR = (1 << 13); 
        }
    }
}

// Hàm main: gửi "vinh" mỗi 5 giây, nhận ký tự điều khiển LED qua USART2
int main(void)
{
    gpio_led_init();
    usart2_init();

    while (1) {
        usart2_send_str("vinh\r\n");
        delay_ms(5000);
    }
}