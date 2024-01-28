#include "board.h"
#include "anibubox.h"

int main(void) {

    stdio_init_all();
    
    printf("Animal Button Box here.\n");

    anibubox_error_e anibubox_error = ABB_ALL_GOOD;

    anibubox_params_t anibubox_params = {
        .led_var       = {.led_pin = LED_PIN},
        .button_var    = {.button_pin = BUTTON_PIN},
    };

    anibubox_error = anibubox_init(&anibubox_params);

    anibubox_error = anibubox_loop(&anibubox_params);
}



