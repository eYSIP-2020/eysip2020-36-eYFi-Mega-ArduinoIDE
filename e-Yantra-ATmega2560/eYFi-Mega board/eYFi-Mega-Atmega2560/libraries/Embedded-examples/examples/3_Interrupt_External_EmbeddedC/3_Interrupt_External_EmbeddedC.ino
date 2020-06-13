/*
TITLE  : External Interrupt
DATE  : 2019/11/12
AUTHOR  : e-Yantra Team
*/

#define F_CPU 16000000UL    // Define Crystal Frequency of eYFi-Mega Board

#include <avr/io.h>       // Standard AVR IO Library
#include <util/delay.h>     // Standard AVR Delay Library
#include <avr/interrupt.h>    // Standard AVR Interrupt Library

#define PIN_LED_RED   PH3   // Macro for Pin Number of Red Led
#define PIN_LED_BLUE  PH4   // Macro for Pin Number of Blue Led
#define PIN_LED_GREEN PH5   // Macro for Pin Number of Green Led
#define PIN_USER_SW   PE7   // Macro for Pin Number of User Switch

volatile unsigned int counter_switch = 0; // variable, immune to compiler optimization, to store press count

void init_button(void){
  DDRE &= ~(1 << PIN_USER_SW);    // Make PIN_USER_SW input
  PORTE |= (1 << PIN_USER_SW);    // Turn on Internal Pull-Up resistor of PIN_USER_SW (Optional)
}


void init_switch_interrupt(void){
  
  // all interrupts have to be disabled before configuring interrupts
  cli();  // Disable Interrupts Globally

  EIMSK |= (1 << INT7); // Turn ON INT7 (alternative function of PE7 i.e Button Pin)
  
  EICRB |= (1 << ISC71);  // Falling Edge detection on INT7
  EICRB &= ~(1 << ISC70);

  sei();  // Enable Interrupts Gloabally
}


// Interrupt Servie Routine of INT7
ISR(INT7_vect){
  counter_switch++; // increment this when the User Switch is pressed and then released
}


void init_led(){
  DDRH    |= (1 << PIN_LED_RED) | (1 << PIN_LED_BLUE) | (1 << PIN_LED_GREEN);     // initialize the pins PIN_LED_RED,PIN_LED_BLUE,PIN_LED_GREEN of port H as output pins.
  PORTH   |= (1 << PIN_LED_RED) | (1 << PIN_LED_BLUE) | (1 << PIN_LED_GREEN);     // set the values that all the LEDs remains off initially
}

void led_redOn(void){
  PORTH &= ~(1 << PIN_LED_RED);   // Make PHPIN_LED_RED Low
}

void led_redOff(void){
  PORTH |= (1 << PIN_LED_RED);    // Make PHPIN_LED_RED High
}


void led_blueOn(void){
  PORTH &= ~(1 << PIN_LED_BLUE);    // Make PHPIN_LED_BLUE Low
}

void led_blueOff(void){
  PORTH |= (1 << PIN_LED_BLUE);   // Make PHPIN_LED_BLUE High
}



void led_greenOn(void){
  PORTH &= ~(1 << PIN_LED_GREEN);   // Make PHPIN_LED_GREEN Low
}

void led_greenOff(void){
  PORTH |= (1 << PIN_LED_GREEN);    // Make PHPIN_LED_GREEN High
}


// Function to turn off all leds
void leds_off(void){
  PORTH   |= (1 << PIN_LED_RED) | (1 << PIN_LED_BLUE) | (1 << PIN_LED_GREEN);  // Clear all Led Pins
}

// Function to turn on each led individually for 100 ms
void led_all(void){

  led_redOn();
  _delay_ms(250);

  led_redOff();
  _delay_ms(250);

  led_greenOn();
  _delay_ms(250);

  led_greenOff();
  _delay_ms(250);

  led_blueOn();
  _delay_ms(250);

  led_blueOff();
  _delay_ms(250);
}

// Function to turn on Red and Blue Led
void led_rb(void){
  leds_off();
  led_redOn();
  led_blueOn();
}

// Function to turn on Green and Red Led
void led_rg(void){
  leds_off();
  led_redOn();
  led_greenOn();
}

// Function to turn on Blue and Green Led
void led_bg(void){
  leds_off();
  led_blueOn();
  led_greenOn();
}

// Function to turn on RBG leds
void led_rbg(void){
  leds_off();
  led_redOn();
  led_blueOn();
  led_greenOn();
}


int main(void){
  init_led();
  init_button();
  init_switch_interrupt();

    while(1){

    switch(counter_switch){

      case 0:
      led_all();
      break;

      case 1:
      led_rg();
      break;

      case 2:
      led_rb();
      break;

      case 3:
      led_bg();
      break;

      case 4:
      leds_off();
      led_redOn();
      break;

      case 5:
      leds_off();
      led_greenOn();
      break;

      case 6:
      leds_off();
      led_blueOn();
      break;

      default:
      leds_off();
      counter_switch = 0;
      break;
    };
    }
    
}
