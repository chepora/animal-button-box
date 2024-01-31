#include "../include/piezo.h"

uint slice_num;

static uint32_t clock;

static uint8_t pin;


void piezo_init(uint8_t pwm_pin) {

    clock = clock_get_hz(clk_sys);
    pin = pwm_pin;

    gpio_set_function(pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(pin);

}

void piezo_play_freq(float freq){
    
    float divider = (float) clock / (freq * 10000.0);
    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, 10000);
    pwm_set_gpio_level(pin, 5000);

}


uint8_t piezo_play_hello(){

    uint8_t value = 0;

    pwm_set_enabled(slice_num, true);
    piezo_play_freq(82.407);
    sleep_ms(250);
    piezo_play_freq(92.499);
    sleep_ms(250);
    piezo_play_freq(110.000);
    sleep_ms(500);
    pwm_set_enabled(slice_num, false);

    return value;

}

uint8_t piezo_play_goodnight(){

    uint8_t value = 0;

    pwm_set_enabled(slice_num, true);
    sleep_ms(250);
    piezo_play_freq(82.407);
    sleep_ms(250);
    piezo_play_freq(92.499);
    sleep_ms(500);
    piezo_play_freq(0.0);
    pwm_set_enabled(slice_num, false);

    return value;

}

