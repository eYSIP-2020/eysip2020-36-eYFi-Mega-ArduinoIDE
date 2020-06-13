/*
TITLE  : Interal Interrupt using Timer #2
DATE  : 2019/11/12
AUTHOR  : e-Yantra Team
*/


#define F_CPU 16000000UL    // Define Crystal Frequency of eYFi-Mega Board
#include <avr/io.h>         // Standard AVR IO Library
#include <util/delay.h>     // Standard AVR Delay Library
#include <avr/interrupt.h>  // Standard AVR Interrupt Library

#define PIN_LED_GREEN PH5   // Macro for Pin Number of Green Led

volatile unsigned int count = 0;  // Used in ISR of Timer2 to store ms elasped
unsigned int seconds = 0;         // Stores seconds elasped

void init_timer2(void){
  cli();  // Turn off global interrupts

  //Setup Timer2 to fire every 1ms
  TCCR2B = 0x00;                        // Cut off Clock Source to disbale Timer2 while we set it up
  TCNT2  = 130;                         // Reset Timer Count to 130 out of 255
  TIFR2  &= ~(1 << TOV2);               // Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 |= (1 << TOIE2);               // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;                        // Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B |= (1 << CS22) | (1 << CS20);  // Timer2 Control Reg B: Timer Prescaler set to 128 and Start Timer2

  sei();  // Turn on global interrupts
}


//Timer2 Overflow Interrupt Vector
ISR(TIMER2_OVF_vect) {
  count++;  // increment after 1 ms               
  
  // increment seconds variable after 1000 ms
  if(count > 999){
  seconds++;    
    count = 0;          
  }
  
  TCNT2 = 130;            // Reset Timer to 130 out of 255
  TIFR2  &= ~(1 << TOV2); // Timer2 INT Flag Reg: Clear Timer Overflow Flag
};


void init_led(void){
  DDRH    |= (1 << PIN_LED_GREEN);    
  PORTH   |= (1 << PIN_LED_GREEN);    
}

void led_greenOn(void){
  PORTH &= ~(1 << PIN_LED_GREEN);
}

void led_greenOff(void){
  PORTH |= (1 << PIN_LED_GREEN);
}


int main(void) {
  init_led();
  init_timer2();

  while(1){

    // Turn On green led if seconds elasped are even else turn it off
    if((seconds % 2) == 0){
      led_greenOn();
    } else {
      led_greenOff();
    }

  }

  return 0; 
}
