// === FILE: state.h ===
#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_BLINKING,
    LED_STATE_ON,
    LED_STATE_ERROR
} LED_State_t;

extern volatile LED_State_t led_state;
extern volatile uint32_t blink_interval_ms;
extern volatile uint32_t last_command_tick;
#endif // STATE_H