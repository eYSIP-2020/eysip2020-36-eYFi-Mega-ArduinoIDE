/*
 * TITLE: eYFi-Mega ATmega 2560 I2C Scanner
 * DATE: 2019/12/16
 * AUTHOR: e-Yantra Team
 */ 


#define F_CPU 16000000

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "uart.h"

int main(void) {
  i2c_init();

  uart0_init(UART_BAUD_SELECT(9600, F_CPU));
  uart0_flush();
  uart0_puts("*** ATmega 2560 I2C Scanner ***\n");

  int ret;

  while(1){

    unsigned char error, address;
    int ndevices;
    uart0_puts("Scanning....");
    ndevices = 0;
    char tx_str[100];

    for(address=1;address<127;address++)
    {
      i2c_start(address);

      if((TWSR&0xF8)== 0x18)
      {
        uart0_puts("I2C device found at 0x");
        if(address<16)
        {
        uart0_puts("0");
        }
        sprintf(tx_str, "%02x\n", address/2); // select 7 bits starting from MSB
        uart0_puts(tx_str);
        uart0_puts("!");
        ndevices++;
      }
    }
    
    if(ndevices == 0){
      uart0_puts("No I2C device found\n");
    }else{
      uart0_puts("done\n");
      _delay_ms(5000);
    }
  }
  
  return 0; 
}
