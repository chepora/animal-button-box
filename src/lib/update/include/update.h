#ifndef UPDATE_H__
#define UPDATE_H_

#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define UPDATEDEBUG 1

typedef enum {
    UPDATE_ALL_GOOD     = 0x00,
    UPDATE_WRITE_ERROR  = 0x0F,
    UPDATE_READ_ERROR   = 0xF0,
    UPDATE_NPTR_ERROR   = 0xFF,
} update_state_e;

typedef struct {

    uint8_t switch_pin;

} update_params_t;

update_state_e update_switch_init(update_params_t* pt_update_params);

#endif