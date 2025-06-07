// === FILE: gpio.h ===
#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

void GPIO_Init(void);
void LED_Set(int on);
void LED_Toggle(void);
void LED_Error(int on);
void led_blink_start(uint32_t interval_ms);
void led_blink_stop(void);
void led_set_blink_interval(uint32_t interval_ms);

#endif // GPIO_H