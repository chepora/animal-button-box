#ifndef BOARD_H__
#define BOARD_H_

// LED
#define LED_PIN     13  // on-board LED on Adafruit Feather RP2040

// BUTTON
#define BUTTON_PIN   6  // D4

#define PULL_UP_INPUT
#define DISABLE_HYSTERESIS

#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

// ADC
#define BATTERY_PIN 13
#define ADC_INST    0
#define VOLT_THRES  3.3

// UPDATE
#define SWITCH_PIN  27

// SLEEPY TIME
#define SLEEPY_TIME_MS 10 * 1000

#endif