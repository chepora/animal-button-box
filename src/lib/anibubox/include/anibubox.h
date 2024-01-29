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

typedef enum {

    ABB_INIT_STATE          = 0x00,
    ABB_START_STATE         = 0x01,
    ABB_WAKE_UP_STATE       = 0x02,
    ABB_SLEEP_STATE         = 0x03,
    ABB_BAT_WARN_STATE      = 0x04,
    // update states
    ABB_UPDATE_INIT_STATE   = 0x05,
    ABB_UPDATE_LOOP_STATE   = 0x06,
    ABB_UPDATE_FAIL_STATE   = 0x07,
    ABB_UPDATE_SUCC_STATE   = 0x08,
    // for sanity check
    ABB_MAX_STATE           = ABB_UPDATE_SUCC_STATE,

} anibubox_state_e;

typedef enum {

    ABB_WAKE_UP_EVENT       = 0x00,
    ABB_SLEEPY_TIME_EVENT   = 0x01,
    ABB_BUTTON_PRESS_EVENT  = 0x02,
    ABB_BATTERY_GOOD_EVENT  = 0x03,
    ABB_BATTERY_LOW_EVENT   = 0x04,
    // update events
    ABB_UP_SWITCH_OFF_EVENT = 0x05,
    ABB_UP_SWITCH_ON_EVENT  = 0x06,
    ABB_UP_SD_OK_EVENT      = 0x07,
    ABB_UP_SD_NOT_OK_EVENT  = 0x08,
    ABB_UP_TIMEOUT_EVENT    = 0x09,
    ABB_UP_SUCCESS_EVENT    = 0x0A,
    // idle
    ABB_NO_EVENT            = 0x0B,
    // for sanity check
    ABB_MAX_EVENT           = ABB_NO_EVENT,

} anibubox_event_e;

typedef struct {
    anibubox_state_e current_state;
    anibubox_event_e event;
    anibubox_state_e netx_state;
} anibubox_state_table_t;

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