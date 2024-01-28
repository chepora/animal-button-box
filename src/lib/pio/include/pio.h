#ifndef PIO_H__
#define PIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

struct pio_color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void pio_init();
void pio_cycle_color();
void pio_start_signal();

#endif
