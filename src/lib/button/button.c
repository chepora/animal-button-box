#include "../include/button.h"
#include "../include/pio.h"

#define PULL_UP_INPUT
#define DEBOUNCE_DEL    200

button_t* pt_arcade_button;

int64_t debounce_callback(alarm_id_t id, void *user_data);
void button_callback(uint gpio, uint32_t events);

void button_init(button_param_t* pt_button_param){

    #ifdef DISABLE_HYSTERESIS
        // Schmitt trigger hysteresis is enabled on all GPIOs by default
        // to see why debouncing is truly necessary:
        gpio_set_input_hysteresis_enabled(pt_button_param->button_pin, false);
    #endif 

    gpio_init(pt_button_param->button_pin);
    gpio_set_dir(pt_button_param->button_pin, GPIO_IN);

    #ifdef PULL_UP_INPUT
        // if button sits between IO and GND:
        gpio_pull_up(pt_button_param->button_pin);
        printf("Input on %d set as pull-up.\n", pt_button_param->button_pin);

    #else
        // if button sits between IO and POWER:
        gpio_pull_down(pt_button_param->button_pin);
        printf("Input on %d set as pull-down.\n", pt_button_param->button_pin);
    #endif

    pt_arcade_button = pt_button_param->pt_button;

    gpio_set_irq_enabled_with_callback(pt_button_param->button_pin, GPIO_IRQ_EDGE_FALL, true, &button_callback);
   
}

int64_t debounce_callback(alarm_id_t id, void *user_data) {

    //return is next alarm!
    int64_t alarm_return = 0;

    // inversion for pull-up
    if((!gpio_get(pt_arcade_button->pin))){
        // still pressed
        pt_arcade_button->button_samples_to_do--;
        pt_arcade_button->debounced_value = true;
    }else{
        pt_arcade_button->raw_reading = false;
        pt_arcade_button->debounced_value = false;
        pt_arcade_button->button_samples_to_do = pt_arcade_button->button_samples_req;
    }

    // if delay is passed or enough consecutive samples were the same
    if((absolute_time_diff_us(pt_arcade_button->debounce_delay_end, get_absolute_time()) <= 100*1000) ||
        (pt_arcade_button->button_samples_to_do == 0)){

            gpio_set_irq_enabled_with_callback(pt_arcade_button->pin, GPIO_IRQ_EDGE_FALL, true, &button_callback);

            if(pt_arcade_button->debounced_value){
                // call what button is supposed to trigger
                // should be moved into fn pt inside struct
                // button needs to do 3 things:
                // - change led
                pio_cycle_color();
                // - change e-ink pic
                // - record time
                pt_arcade_button->time_of_last_press = get_absolute_time();
            } 
    }else{
        // alarm will repeat 10 ms after last called(not depending on callback)
        // +10 would mean 10 ms after here
        alarm_return = -10;
    }
    return alarm_return;
}

void button_callback(uint gpio, uint32_t events) {
    
    // press detected
    // disable irq for now, remove callback
    gpio_set_irq_enabled_with_callback(pt_arcade_button->pin, GPIO_IRQ_EDGE_FALL, false, NULL);

    // get time = now + delay
    pt_arcade_button->debounce_delay_end = make_timeout_time_ms(pt_arcade_button->debounce_time);

    pt_arcade_button->raw_reading = true;
    pt_arcade_button->button_samples_to_do--;

    //time to debounce
    add_alarm_in_ms(pt_arcade_button->debounce_intervall, debounce_callback, NULL, true);
    
}
