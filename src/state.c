#include "state.h"

volatile LED_State_t led_state = LED_STATE_OFF;
volatile uint32_t blink_interval_ms = 500;
volatile uint32_t last_command_tick = 0;