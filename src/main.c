#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "anibubox.h"

// add ifndef test and call to test routine

void set_params(anibubox_params_t* pt_anibubox_params);

int main(void) {

    stdio_init_all();
    
    printf("Animal Button Box here.\n");

    anibubox_error_e abb_error = ABB_ALL_GOOD;

    anibubox_struct_t* pt_abb_struct;

    pt_abb_struct = (anibubox_struct_t*) malloc(sizeof(anibubox_struct_t));

    if (pt_abb_struct == NULL)
    {
        printf("No more storage.\n");
        return 0;
    }

    anibubox_params_t* pt_abb_params = &pt_abb_struct->anibubox_params;

    set_params(pt_abb_params);

    pt_abb_struct->anibubox_state = ABB_INIT_STATE;
    pt_abb_struct->anibubox_event = ABB_NO_EVENT;

    while(abb_error == ABB_ALL_GOOD){
        abb_error = anibubox_express_state(pt_abb_struct);
    }

    // error handling to be implemented here

}

void set_params(anibubox_params_t* pt_abb_params){

    pt_abb_params->led_var.led_pin          = LED_PIN;

    pt_abb_params->button_var.button_pin    = BUTTON_PIN;

    pt_abb_params->adc_var.pin              = BATTERY_PIN;
    pt_abb_params->adc_var.adc_inst         = ADC_INST;
    pt_abb_params->adc_var.vol_thres        = VOLT_THRES;

    pt_abb_params->update_var.switch_pin    = SWITCH_PIN;

    pt_abb_params->sleepy_var.sleepy_delay_ms   = SLEEPY_TIME_MS;
    pt_abb_params->sleepy_var.alarm_set         = false;

}



