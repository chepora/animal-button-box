#ifndef ANIBUBOX_H__
#define ANIBUBOX_H_

#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#include "anibubox_sm.h"

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

typedef struct{

    anibubox_params_t anibubox_params;
    anibubox_state_e  anibubox_state; 

} anibubox_struct_t;

typedef anibubox_error_e(*anibubox_function_t)(anibubox_struct_t* pt_abb_struct);

typedef struct {

    const char* name;
    anibubox_function_t execute;

} anibubox_function_table_t;

extern const anibubox_state_table_t anibubox_state_trans_table[14];

const anibubox_function_table_t* anibubox_get_func_table(anibubox_state_e abb_state);

anibubox_error_e anibubox_express_state(anibubox_struct_t* pt_abb_struct);

#endif