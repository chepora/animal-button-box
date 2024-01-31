#include "../include/sleepy_time.h"

int64_t sleepy_time_callback(alarm_id_t id, void *user_data);

sleepy_state_e sleepy_time_init(sleepy_params_t* pt_sleepy_params){


    sleepy_state_e sleepy_state = SLEEPY_NPTR_ERROR;

    if(pt_sleepy_params == NULL) return sleepy_state;

    // get last time button was pressed in absolute time
    volatile absolute_time_t    time_of_last_press = *(pt_sleepy_params->pt_last_button_press_time);

    // add delay
    pt_sleepy_params->time_of_alarm = delayed_by_ms(time_of_last_press, pt_sleepy_params->sleepy_delay_ms);

    // set alarm with callback
    // alarm needs to be passsed pointerto last button press time

    pt_sleepy_params->alarm_id = add_alarm_at(pt_sleepy_params->time_of_alarm , &sleepy_time_callback, pt_sleepy_params, true);
    if(SLEEPYDEBUG)printf("sleepy_time_alarm was set.\n");

    pt_sleepy_params->alarm_set = true;

    sleepy_state = SLEEPY_ALL_GOOD;

    return sleepy_state;
}

int64_t sleepy_time_callback(alarm_id_t id, void *user_data){

    uint8_t reschedule = 0; // to not reschedule
    if(SLEEPYDEBUG)printf("sleepy_time_callback was called.\n");

    // set state

    return reschedule;

}
