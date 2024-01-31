#include "../include/led.h"

#define ON  1
#define OFF 0

static uint8_t chosen_led_pin = 0;

void led_init(led_param_t* pt_led_param){

    gpio_init(pt_led_param->led_pin);
    gpio_set_dir(pt_led_param->led_pin, GPIO_OUT);
    chosen_led_pin = pt_led_param->led_pin;

}

void led_on(){

    gpio_put(chosen_led_pin, ON);
}

void led_off(){

    gpio_put(chosen_led_pin, OFF);
}

void led_toggle(){

    if(gpio_get(chosen_led_pin)){

        led_off(chosen_led_pin);
    }else
    {
        led_on(chosen_led_pin);
    }
    
}

void led_blink(uint8_t times, uint32_t blink_time_ms){

    for (size_t i = 0; i < times; i++)
    {
        gpio_put(chosen_led_pin, ON);
        sleep_ms(blink_time_ms);
        gpio_put(chosen_led_pin, OFF);
        sleep_ms(blink_time_ms);
    }
}