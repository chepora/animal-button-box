#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct {

    uint8_t     led_pin;

} led_param_t;

void led_init(led_param_t* pt_led_param);
void led_on();
void led_off();
void led_toggle();
void led_blink(uint8_t times, uint32_t blink_time_ms);

#endif