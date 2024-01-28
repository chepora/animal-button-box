#include "../include/anibubox.h"

#define BUTTON_PRESSED 0

static void make_button(anibubox_params_t* pt_anibubox_params);

anibubox_error_e anibubox_init(anibubox_params_t* pt_anibubox_params){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_anibubox_params == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    led_init(&pt_anibubox_params->led_var);
    make_button(pt_anibubox_params);
    button_init(&pt_anibubox_params->button_var);
    pio_init();

    /*
    still to add:
    - pwm with piezo (pio or gpio?)
    - imu
    - serial log
    - e-ink
    - adc
    - multicore?
    - flash access?
    */

    return anibubox_error;

}

anibubox_error_e anibubox_loop(anibubox_params_t* pt_anibubox_params){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_anibubox_params == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    pio_start_signal();

    uint8_t input = 0;

    while(true){

        // timer for sleep needs to start
        // callback is set to sleep with all power down
        /*
        - needs to cancel button interrupt ?
        - needs to set itr on pin to imu
        - needs to set imu to sleep (dormant?)
        
        */
    }
    
    return anibubox_error;
}

static void make_button(anibubox_params_t* pt_anibubox_params){

    pt_anibubox_params->arcade_button.pin = pt_anibubox_params->button_var.button_pin;
    pt_anibubox_params->arcade_button.debounced_value   = false;
    pt_anibubox_params->arcade_button.raw_reading       = false;

    pt_anibubox_params->arcade_button.button_samples_to_do = 5;
    pt_anibubox_params->arcade_button.button_samples_req   = 5;
    pt_anibubox_params->arcade_button.debounce_intervall   = 10;
    pt_anibubox_params->arcade_button.debounce_time        = 200;

    pt_anibubox_params->button_var.pt_button = &pt_anibubox_params->arcade_button;
}