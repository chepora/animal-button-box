#ifndef PIEZO_H__
#define PIEZO_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

void piezo_init(uint8_t pwm_pin);
void piezo_play_freq(float freq);
uint8_t piezo_play_hello(void);
uint8_t piezo_play_goodnight(void);

#endif