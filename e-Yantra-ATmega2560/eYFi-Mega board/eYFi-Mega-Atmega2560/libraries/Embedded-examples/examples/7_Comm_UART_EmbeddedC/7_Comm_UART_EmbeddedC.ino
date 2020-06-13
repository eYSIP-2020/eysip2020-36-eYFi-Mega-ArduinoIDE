/*
TITLE  : UART
DATE  : 2019/11/12
AUTHOR  : e-Yantra Team
*/

#define F_CPU 16000000
#define USART0_ENABLED

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"


char uart0_readByte(void){

  uint16_t rx;
  uint8_t rx_status, rx_data;

  rx = uart0_getc();
  rx_status = (uint8_t)(rx >> 8);
  rx = rx << 8;
  rx_data = (uint8_t)(rx >> 8);

  if(rx_status == 0 && rx_data != 0){
    return rx_data;
  } else {
    return -1;
  }

}

int main(void) {

  char rx_byte;

  uart0_init(UART_BAUD_SELECT(9600, F_CPU));
  uart0_flush();
  uart0_puts("*** ATMega 2560 UART0 ECHO ***\n");

  while(1){

    rx_byte = uart0_readByte();

    if(rx_byte != -1){
      uart0_putc(rx_byte);
    }
    
  }

  return 0; 
}
