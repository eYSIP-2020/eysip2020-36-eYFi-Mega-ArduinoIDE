/*
TITLE  : Analog Input using ADC
DATE  : 2019/11/12
AUTHOR  : e-Yantra Team

AIM: Touch PF1 pin to turn the led red else it should stay blue
*/

#define F_CPU 16000000UL    // Define Crystal Frequency of eYFi-Mega Board

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PIN_ADC     PF1
#define PIN_LED_RED   PH3
#define PIN_LED_BLUE  PH4


unsigned char ADC_Value;
unsigned char adc_reading;
unsigned int value;


//ADC pin configuration
/* 

1) Set all ADC Pins as Input.
2) Make all ADC Pins Floating

NOTE: if ADC pins are pulled-up then 5V will be on the pins. So, ADC wont give proper value.

*/
void adc_pin_config (void){
  DDRF &= ~(1 << PIN_ADC); //set PORTF direction as input
  PORTF &= ~(1 << PIN_ADC); //set PORTF pins floating
}


//Function to Initialize ADC
/*

1) Disable Analog Comparator
2) Turn ON ADC
3) Set Prescalar to 64

*/
void adc_init(){
  
  ACSR = 1 << ACD;    // Analog Comparator Disable; else ADC wont work
  
  ADMUX = (1 << ADLAR);

  // (turn ADC ON) | (set prescalar to 64 110)
  ADCSRA = (1 << ADEN) |  (1 << ADPS2 | 1 << ADPS1) ;
}



//This Function accepts the Channel Number and returns the corresponding Analog Value 
/* This function is for  Single Endded Channels Only */
unsigned char ADC_Conversion(unsigned char Ch)
{
  
  unsigned char a;
  
  // Extract Last 3 bits from Ch for ADMUX
  Ch = Ch & 0b00000111; //0x07    
  ADMUX = 0x20 | Ch; // (Left Adjusted Output) | (ADMUX4:0) 
  //-----------------------------------------------------------------
  // Refer Table 26-4 on page 283 of datasheet
  // If channel number is greater than 7 then SET MUX5
  if(Ch > 7){
    ADCSRB |= 1 << MUX5; // set MUX5 =1
  }
  

     
  // ADMUX |= Ch; // *** does not work if ADLAR is set in adc_init()  
  //-----------------------------------------------------------------
  

  //-----------------------------------------------------------------
  ADCSRA |= 1 << ADSC;    //Set start conversion bit
  
  // Wait for ADC conversion to complete; ADIF = 0, conversion going on; ADIF = 1, conversion complete
  while((ADCSRA & (1 << ADIF) ) == 0);  
  
  // store ADC value in variable are return it.
  a = ADCH;
  //-----------------------------------------------------------------


  //-----------------------------------------------------------------
  // ADIF is set when ADC conversion is complete and Data Registers are updated
  // ADIF needs to be cleared before starting next conversion
  ADCSRA |= (1 << ADIF); // IMP: clear ADIF (ADC Interrupt Flag) by writing 1 to it
  
  ADCSRB &= ~(1 << MUX5); // clear MUX5 so that other ADC channels can use this function
  //-----------------------------------------------------------------

  return a;
}


//Function to Initialize PORTS
void port_init()
{
  adc_pin_config(); 
}


void led_init(void){
  DDRH    |= (1 << PIN_LED_RED) | (1 << PIN_LED_BLUE);    
  PORTH   |= (1 << PIN_LED_RED) | (1 << PIN_LED_BLUE);    
}

void led_redOn(void){
  PORTH &= ~(1 << PIN_LED_RED);
}

void led_redOff(void){
  PORTH |= (1 << PIN_LED_RED);
}

void led_blueOn(void){
  PORTH &= ~(1 << PIN_LED_BLUE);
}

void led_blueOff(void){
  PORTH |= (1 << PIN_LED_BLUE);
}

// Timer 4 initialized in PWM mode for brightness control
// Prescale:256
// PWM 8bit fast, TOP=0x00FF
// Timer Frequency:225.000Hz
void timer4_init()
{
  cli(); //disable all interrupts
  
  TCCR4B = 0x00;  //Stop
  
  TCNT4H = 0xFF;  //Counter higher 8-bit value to which OCR5xH value is compared with
  TCNT4L = 0x00;  //Counter lower 8-bit value to which OCR5xH value is compared with
  
  OCR4AH = 0x00;  //Output compare register high value for Red Led
  OCR4AL = 0xFF;  //Output compare register low value for Red Led
  
  OCR4BH = 0x00;  //Output compare register high value for Blue Led
  OCR4BL = 0xFF;  //Output compare register low value for Blue Led
  
  //  Clear OC4A & OC4B on compare match (set output to low level)
  TCCR4A |= (1 << COM4A1) | (1 << COM4B1);
  TCCR4A &= ~((1 << COM4A0) | (1 << COM4B0));

  // FAST PWM 8-bit Mode
  TCCR4A |= (1 << WGM40);
  TCCR4A &= ~(1 << WGM41);
  TCCR4B |= (1 << WGM42);
  
  // Set Prescalar to 64
  TCCR4B |= (1 << CS41) | (1 << CS40);
  TCCR4B &= ~(1 << CS42);
  
  sei(); //re-enable interrupts
}

// Function for brightness control
void brightness (unsigned char red_led, unsigned char blue_led){
  OCR4AL = 255 - (unsigned char)red_led;  // active low thats why subtracting by 255
  OCR4BL = 255 - (unsigned char)blue_led;
}


void init_devices (void)
{
  port_init();
  adc_init();
  led_init();
  timer4_init();
}


//Main Function
int main(void)
{
  unsigned int value;
  init_devices();
  
  while(1)
  {
    ADC_Value = ADC_Conversion(1);
    brightness(ADC_Value, 255 - ADC_Value);

  }
}
