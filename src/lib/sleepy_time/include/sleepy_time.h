#ifndef SLEEPY_TIME_H__
#define SLEEPY_TIME_H_

#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define SLEEPYDEBUG 0

typedef enum {
    SLEEPY_ALL_GOOD        = 0x00,
    SLEEPY_WRITE_ERROR     = 0x0F,
    SLEEPY_READ_ERROR      = 0xF0,
    SLEEPY_NPTR_ERROR      = 0xFF,
} sleepy_state_e;

typedef struct {

    uint64_t                    sleepy_delay_ms;
    volatile absolute_time_t    time_of_alarm;
    absolute_time_t*            pt_last_button_press_time;
    alarm_id_t                  alarm_id;
    bool                        alarm_set;
    bool                        is_sleepy_time;

} sleepy_params_t;

sleepy_state_e sleepy_time_init(sleepy_params_t* pt_sleepy_params);

#endif