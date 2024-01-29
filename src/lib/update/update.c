#include "../include/update.h"

update_state_e update_switch_init(update_params_t* pt_update_params){

    update_state_e update_state = UPDATE_NPTR_ERROR;

    if(pt_update_params == NULL) return update_state;

    gpio_init(pt_update_params->switch_pin);
    gpio_set_dir(pt_update_params->switch_pin, GPIO_IN);
    gpio_pull_up(pt_update_params->switch_pin);
    if(UPDATEDEBUG) printf("Input on %d set as pull-up.\n", pt_update_params->switch_pin);

    update_state = UPDATE_ALL_GOOD;

    return update_state;
}