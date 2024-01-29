/*-----------------------------------------------------------------------------
 *  anibubox.c
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *  INCLUDES
 *---------------------------------------------------------------------------*/
#include "../include/anibubox.h"

/*-----------------------------------------------------------------------------
 *  DEFINES
 *---------------------------------------------------------------------------*/

#define BUTTON_PRESSED 0

/*-----------------------------------------------------------------------------
 *  STATIC DECLARATIONS
 *---------------------------------------------------------------------------*/
static anibubox_error_e abb_init(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_start(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_wake_up(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_sleep(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_bat_warn(anibubox_struct_t* pt_abb_struct);

static anibubox_error_e abb_update_init(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_update_loop(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_update_fail(anibubox_struct_t* pt_abb_struct);
static anibubox_error_e abb_update_success(anibubox_struct_t* pt_abb_struct);

static const anibubox_function_table_t anibubox_function_table[] =
{
    {"anibubox_init",       &abb_init           }, // 0x00
    {"abb_start",           &abb_start          }, // 0x01
    {"abb_wake_up",         &abb_wake_up        }, // 0x02
    {"abb_sleep",           &abb_sleep          }, // 0x03
    {"abb_bat_warn",        &abb_bat_warn       }, // 0x04
    // Update functions
    {"abb_update_init",     &abb_update_init    }, // 0x05
    {"abb_update_loop",     &abb_update_loop    }, // 0x06
    {"abb_update_loop",     &abb_update_fail    }, // 0x07
    {"abb_update_loop",     &abb_update_success }, // 0x08

};

static void make_button(anibubox_struct_t* pt_abb_struct);

/*-----------------------------------------------------------------------------
 *  PUBLIC DEFINITIONS
 *---------------------------------------------------------------------------*/
const anibubox_function_table_t* anibubox_get_func_table(anibubox_state_e abb_state){

	return (&anibubox_function_table[abb_state]);
}

anibubox_error_e anibubox_express_state(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    const anibubox_function_table_t* pt_abb_function = anibubox_get_func_table(pt_abb_struct->anibubox_state);

    if(ABBDEBUG) printf("Called function:  %s\n", pt_abb_function->name);

    anibubox_error = pt_abb_function->execute(pt_abb_struct);

    anibubox_error = ABB_ALL_GOOD;

	return anibubox_error;
}

/*-----------------------------------------------------------------------------
 *  STATIC DEFINITIONS
 *---------------------------------------------------------------------------*/
static anibubox_error_e abb_init(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    led_init(&pt_abb_struct->anibubox_params.led_var);
    make_button(pt_abb_struct);
    button_init(&pt_abb_struct->anibubox_params.button_var);
    pio_init();

    (void) update_switch_init(&pt_abb_struct->anibubox_params.update_var);

    adc_state_e adc_state = ADC_ALL_GOOD;

    adc_state = local_adc_init(&pt_abb_struct->anibubox_params.adc_var);

    pio_start_signal();

    while(pt_abb_struct->anibubox_state == ABB_INIT_STATE){


        // read battery
        adc_state = adc_read_battery(&pt_abb_struct->anibubox_params.adc_var);

        // depending on battery read set event
        // pt_abb_struct->anibubox_state == ABB_BATTERY_LOW_EVENT;
        pt_abb_struct->anibubox_event = ABB_BATTERY_GOOD_EVENT;

        if(pt_abb_struct->anibubox_event != ABB_NO_EVENT){
            // get function through event
            anibubox_error = anibubox_set_state(pt_abb_struct);
        }
        sleep_ms(100);
    }

    return anibubox_error;
}

static anibubox_error_e abb_start(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    bool update_switch_on;

    while (pt_abb_struct->anibubox_state == ABB_START_STATE)
    {   
        // check update pin
        update_switch_on = gpio_get(pt_abb_struct->anibubox_params.update_var.switch_pin);
        if(ABBDEBUG) printf("update_switch_on is:  %d\n", update_switch_on);

        if (update_switch_on){
            pt_abb_struct->anibubox_event = ABB_UP_SWITCH_ON_EVENT;
        }else{
            pt_abb_struct->anibubox_event = ABB_UP_SWITCH_OFF_EVENT;
        }

        if(pt_abb_struct->anibubox_event != ABB_NO_EVENT){
            // get function through event
            anibubox_error = anibubox_set_state(pt_abb_struct);
        }
        sleep_ms(100);
    }
    
    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_wake_up(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    sleepy_params_t* pt_sleepy_params = &pt_abb_struct->anibubox_params.sleepy_var;

    // give sleepy module the address of the button press time
    pt_sleepy_params->pt_last_button_press_time = &(pt_abb_struct->anibubox_params.arcade_button.time_of_last_press);

    sleepy_state_e sleepy_state = SLEEPY_ALL_GOOD;

    while (pt_abb_struct->anibubox_state == ABB_WAKE_UP_STATE)
    {   
        // init serial? other core? or here?

        // set sleepy time out 
        // wait for shake
        sleep_ms(100);

        //check for core 1 fifo
        // only here can serial_log be used

        // is time past?
        // set alarm for sleepy time
        if (!pt_sleepy_params->alarm_set)
        {
            anibubox_error = sleepy_time_init(pt_sleepy_params);
        }
    }

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_sleep(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    while (pt_abb_struct->anibubox_state == ABB_SLEEP_STATE)
    {   
        // set serial sleep
        // set interrupt for imu
        // stop all communications

        // wait for shake
        sleep_ms(100);

    }

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_bat_warn(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}


static anibubox_error_e abb_update_init(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_update_loop(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_update_fail(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}

static anibubox_error_e abb_update_success(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    return anibubox_error;
}


static void make_button(anibubox_struct_t* pt_abb_struct){

    pt_abb_struct->anibubox_params.arcade_button.pin = pt_abb_struct->anibubox_params.button_var.button_pin;
    pt_abb_struct->anibubox_params.arcade_button.debounced_value   = false;
    pt_abb_struct->anibubox_params.arcade_button.raw_reading       = false;

    pt_abb_struct->anibubox_params.arcade_button.button_samples_to_do = 5;
    pt_abb_struct->anibubox_params.arcade_button.button_samples_req   = 5;
    pt_abb_struct->anibubox_params.arcade_button.debounce_intervall   = 10;
    pt_abb_struct->anibubox_params.arcade_button.debounce_time        = 200;

    pt_abb_struct->anibubox_params.arcade_button.time_of_last_press    = get_absolute_time();

    pt_abb_struct->anibubox_params.button_var.pt_button = &pt_abb_struct->anibubox_params.arcade_button;
}