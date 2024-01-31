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
#define VOLT_THRES  1.0 // too low -> only for testing

// UPDATE
#define SWITCH_PIN  27

// SLEEPY TIME
#define SLEEPY_TIME_MS 10 * 1000

// BUZZER PIN
#define BUZZER_PIN 24

// EPAPER
#define EP_SCK_PIN 10
#define EP_TX_PIN 10
#define EP_CS_PIN 9
#define EP_RX_PIN 8
#define EP_RS_PIN 12
#define EP_BUSY_PIN 13

#define EP_IMAGE_SIZE 10000

#endif