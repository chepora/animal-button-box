#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct {

    uint8_t     led_pin;

} led_param_t;

void led_init(led_param_t* pt_led_param);
void led_on(uint8_t led_pin);
void led_off(uint8_t led_pin);
void led_toggle();
void led_blink(uint8_t led_pin, uint32_t blink_time_ms);

#endif