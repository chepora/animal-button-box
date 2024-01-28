#ifndef BOARD_H__
#define BOARD_H_

#define LED_PIN     13  // on-board LED on Adafruit Feather RP2040
#define BUTTON_PIN   6  // D4

// FOR BUTTON
#define PULL_UP_INPUT
#define DISABLE_HYSTERESIS

#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

#endif