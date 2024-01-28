#ifndef ANIBUBOX_H__
#define ANIBUBOX_H_

#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#include "led.h"
#include "button.h"
#include "pio.h"

typedef struct{

    led_param_t     led_var;
    button_param_t  button_var;
    button_t        arcade_button;

} anibubox_params_t;

typedef enum {
    ABB_ALL_GOOD    = 0x00,
    ABB_WRITE_ERROR = 0x0F,
    ABB_READ_ERROR  = 0xF0,
    ABB_NPTR_ERROR  = 0xFF,
} anibubox_error_e;

anibubox_error_e anibubox_init(anibubox_params_t* pt_anibubox_params);

anibubox_error_e anibubox_loop(anibubox_params_t* pt_anibubox_params);

#endif