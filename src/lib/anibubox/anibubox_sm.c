#include "../include/anibubox.h"

const anibubox_state_table_t anibubox_state_trans_table[MAX_STATE_TABLE] = {

    // CURR STATE           // EVENT                    // NEXT STATE
    {ABB_INIT_STATE,        ABB_BATTERY_GOOD_EVENT,     ABB_START_STATE         },
    {ABB_INIT_STATE,        ABB_BATTERY_LOW_EVENT,      ABB_BAT_WARN_STATE      },
    //
    {ABB_START_STATE,       ABB_UP_SWITCH_OFF_EVENT,    ABB_WAKE_UP_STATE       },
    {ABB_START_STATE,       ABB_UP_SWITCH_ON_EVENT,     ABB_UPDATE_INIT_STATE   },
    //
    {ABB_WAKE_UP_STATE,     ABB_BUTTON_PRESS_EVENT,     ABB_WAKE_UP_STATE       },
    {ABB_WAKE_UP_STATE,     ABB_SLEEPY_TIME_EVENT,      ABB_SLEEP_STATE         },
    {ABB_WAKE_UP_STATE,     ABB_BATTERY_LOW_EVENT,      ABB_BAT_WARN_STATE      },
    //
    {ABB_SLEEP_STATE,       ABB_WAKE_UP_EVENT,          ABB_WAKE_UP_STATE       },
    //
    {ABB_SERIAL_REQ_STATE,  ABB_SERIAL_DONE_EVENT,      ABB_WAKE_UP_STATE       },
    //
    // UPDATE TRANSITIONS
    // CURR STATE           // EVENT                    // NEXT STATE
    {ABB_UPDATE_INIT_STATE, ABB_UP_SD_OK_EVENT,         ABB_UPDATE_LOOP_STATE   },
    {ABB_UPDATE_INIT_STATE, ABB_UP_SD_NOT_OK_EVENT,     ABB_UPDATE_FAIL_STATE   },
    //
    {ABB_UPDATE_LOOP_STATE, ABB_UP_SUCCESS_EVENT,       ABB_UPDATE_SUCC_STATE   },
    {ABB_UPDATE_LOOP_STATE, ABB_UP_TIMEOUT_EVENT,       ABB_UPDATE_FAIL_STATE   },
    //
    {ABB_UPDATE_FAIL_STATE, ABB_UP_TIMEOUT_EVENT,       ABB_INIT_STATE          },
    //
    {ABB_UPDATE_SUCC_STATE, ABB_UP_TIMEOUT_EVENT,       ABB_INIT_STATE          },

};

anibubox_error_e anibubox_set_state(anibubox_struct_t* pt_abb_struct){

    anibubox_error_e anibubox_error = ABB_NPTR_ERROR;

    if(pt_abb_struct == NULL) return anibubox_error;

    anibubox_error = ABB_ALL_GOOD;

    for (size_t i = 0; i < MAX_STATE_TABLE; i++)
    {
        if (anibubox_state_trans_table[i].current_state == pt_abb_struct->anibubox_state)
        {
            if (anibubox_state_trans_table[i].event == pt_abb_struct->anibubox_event)
            {
                pt_abb_struct->anibubox_state = anibubox_state_trans_table[i].next_state;
                if(ABBDEBUG)printf("Set to state: 0x%02x\n", pt_abb_struct->anibubox_state);
            }
            
        }
        
    }
    return anibubox_error;
}