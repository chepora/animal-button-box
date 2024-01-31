#include "../include/piezo.h"

uint slice_num;

static uint32_t clock;


void piezo_init(uint8_t pwm_pin) {

    clock = clock_get_hz(clk_sys);

    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(pwm_pin);
    pwm_set_enabled(slice_num, true);

}

void piezo_play_freq(uint8_t pwm_pin, float freq){
    
    float divider = (float) clock / (freq * 10000.0);
    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, 10000);
    pwm_set_gpio_level(pwm_pin, 5000);

}


