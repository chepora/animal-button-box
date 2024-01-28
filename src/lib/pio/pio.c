#include "../include/pio.h"

// Our assembled program:
#include "pio_poc.pio.h"

#define BRIGTNESS 0.01

#define LAST_COLOR 5

uint8_t current_color;

static const struct pio_color led_colors[6] = {

    {.red = 255, .green =   8, .blue = 255}, // 0 - lila
    {.red =  79, .green =   9, .blue = 255}, // 1 - blue
    {.red =  20, .green = 255, .blue =   9}, // 2 - green
    {.red = 150, .green = 150, .blue =  26}, // 3 - yellow
    {.red = 243, .green = 100, .blue =  78}, // 4 - orange
    {.red = 243, .green =  56, .blue =  19}, // 5 - red
};


static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r * BRIGTNESS) << 8) |
            ((uint32_t) (g * BRIGTNESS) << 16) |
            (uint32_t) (b * BRIGTNESS);
}

void pio_init() {

    printf("pio up for WS2812 using pin %d\n", PICO_DEFAULT_WS2812_PIN);

    PIO pio = pio0;
    int8_t sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, PICO_DEFAULT_WS2812_PIN, 800000, true);

    current_color = 0;

}

static void pio_show_color(const struct pio_color* pr_pio_color){

    put_pixel(urgb_u32(pr_pio_color->red, pr_pio_color->green, pr_pio_color->blue));

}

void pio_cycle_color() {
    
    pio_show_color(&led_colors[current_color]);
    printf("set color %d\n", current_color);
    if(current_color == LAST_COLOR){
        current_color = 0;
    }else current_color++;
}

void pio_start_signal() {

    for (size_t i = 0; i <= LAST_COLOR; i++)
    {
        pio_show_color(&led_colors[i]);
        sleep_ms(500);
    }
    
}