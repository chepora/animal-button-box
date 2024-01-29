#include "../include/anibubox_sm.h"

const anibubox_state_table_t anibubox_state_trans_table[14] = {

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