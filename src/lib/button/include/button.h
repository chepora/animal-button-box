#ifndef BUTTON_H__
#define BUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

typedef struct {

    uint8_t             pin;
    uint8_t             button_samples_req;
    uint8_t             debounce_intervall;
    uint8_t             debounce_time;
    volatile bool       debounced_value;
    volatile bool       raw_reading;
    volatile uint8_t    button_samples_to_do;
    volatile absolute_time_t debounce_delay_end;

} button_t;

typedef struct {

    uint8_t     button_pin;
    button_t*   pt_button;

} button_param_t;

void button_init(button_param_t* pt_button_param);
void updateButton(button_t* pt_button);

#endif