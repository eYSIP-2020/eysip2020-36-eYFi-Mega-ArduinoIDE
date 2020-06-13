/*
TITLE  : Digital Input
DATE  : 2019/11/12
AUTHOR  : e-Yantra Team

AIM : To turn on the green led when onboard user button is pressed otherwise turn it off. 

CONNECTIONS:
* User Button   -> PE7
* Green Led   -> PH5

NOTE:
* Button Pressed  : PE7 - Clear
* Button Released   : PE7 - Set

*/

#define F_CPU 16000000UL    // Define Crystal Frequency of eYFi-Mega Board
#include <avr/io.h>       // Standard AVR IO Library
#include <util/delay.h>     // Standard AVR Delay Library

#define PIN_LED_GREEN PH5 // Macro for Pin Number of Green Led
#define PIN_BUTTON    PE7 // Macro for Pin Number of User Button

void init_button(void){
  DDRE &= ~(1 << PIN_BUTTON);   // Make PIN_BUTTON input
  PORTE |= (1 << PIN_BUTTON);   // Turn on Internal Pull-Up resistor of PIN_BUTTON (Optional)
}

unsigned char button_read(void){
  unsigned char status = PINE >> PIN_BUTTON;  // Read PIN_BUTTON
  return status;
}

void init_led(void){
  DDRH    |= (1 << PIN_LED_GREEN);    // Make PIN_LED_GREEN Output
  PORTH   |= (1 << PIN_LED_GREEN);    // Clear PIN_LED_GREEN
}

void led_greenOn(void){
  PORTH &= ~(1 << PIN_LED_GREEN);   // Clear PIN_LED_GREEN
}

void led_greenOff(void){
  PORTH |= (1 << PIN_LED_GREEN);    // Set PIN_LED_GREEN
}


int main(void){
  
  // initialize led and button
  init_led();
  init_button();

    while(1){

      // If button is pressed turn on the green led else turn it off
    if(button_read() == 1){
      led_greenOff(); 
    } else {
      led_greenOn();
    }
    
    }
    
}
