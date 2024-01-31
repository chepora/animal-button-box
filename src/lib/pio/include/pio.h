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

typedef enum{
    LILA    = 0x00,
    BLUE    = 0x01,    
    GREEN   = 0x02,   
    YELLOW  = 0x03,   
    WHITE   = 0x04, 
    ORANGE  = 0x05,      
    RED     = 0x06,
}pio_color_names_e;

void pio_init();
void pio_cycle_color();
void pio_put_white();
void pio_put_red();
void pio_put_green();
void pio_put_yellow();
void pio_put_off();

#endif
