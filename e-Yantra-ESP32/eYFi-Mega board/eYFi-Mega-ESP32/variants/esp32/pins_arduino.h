#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

//13 5 21 23 12 26 35 39 16 17 19 22 14 25 34 36
// static const uint8_t TX = 1;
// static const uint8_t RX = 3;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t SS    = 5;
static const uint8_t MOSI  = 23;
static const uint8_t MISO  = 19;
// static const uint8_t SCK   = 18;

static const uint8_t A0 = 36;
static const uint8_t A3 = 39;
// static const uint8_t A4 = 32;
// static const uint8_t A5 = 33;
static const uint8_t A6 = 34;
static const uint8_t A7 = 35;
// static const uint8_t A10 = 4;
// static const uint8_t A11 = 0;
// static const uint8_t A12 = 2;
// static const uint8_t A13 = 15;
static const uint8_t A14 = 13;
static const uint8_t A15 = 12;
static const uint8_t A16 = 14;
// static const uint8_t A17 = 27;
static const uint8_t A18 = 25;
static const uint8_t A19 = 26;

/*******************/
static const uint8_t GPIO13 = 13;
static const uint8_t GPIO5 = 5;
static const uint8_t GPIO21 = 21;
static const uint8_t GPIO23 = 23;
static const uint8_t GPIO12 = 12;
static const uint8_t GPIO26 = 26;
static const uint8_t GPIO35 = 35;
static const uint8_t GPIO39 = 39;
static const uint8_t GPIO16 = 16;
static const uint8_t GPIO17 = 17;
static const uint8_t GPIO19 = 19;
static const uint8_t GPIO22 = 22;
static const uint8_t GPIO14 = 14;
static const uint8_t GPIO25 = 25;
static const uint8_t GPIO34 = 34;
static const uint8_t GPIO36 = 36;

//13 5 21 23 12 26 35 39 16 17 19 22 14 25 34 36
// static const uint8_t T0 = 4;
// static const uint8_t T1 = 0;
// static const uint8_t T2 = 2;
// static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
// static const uint8_t T7 = 27;
// static const uint8_t T8 = 33;
// static const uint8_t T9 = 32;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

#endif /* Pins_Arduino_h */
