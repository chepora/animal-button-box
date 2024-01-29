#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "anibubox.h"

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

    pt_abb_params->led_var.led_pin          = LED_PIN;
    pt_abb_params->button_var.button_pin    = BUTTON_PIN;

    pt_abb_struct->anibubox_state = ABB_INIT_STATE;

    while(1){
        abb_error = anibubox_express_state(pt_abb_struct);
    }

}



