/*
 * testing.c
 *
 * Created: 02.09.2015 08:52:12
 *  Author: vegasten
 */ 

 
#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>


#include"driver_ATMega_uart.h"

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800;//Start address for the SRAM
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;
	
	int seed = rand();
	
	printf("Starting SRAM test...\r\n");
	srand(seed);
	for (i = 0; i < 0x800; i++) {
		testvalue = rand();
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			//printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
	}
	
	srand(seed);
	for (i = 0; i < 0x800; i++) {
		testvalue = rand();
		if (ext_ram[i] != testvalue) {
			//printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}



int main(void)
{
	
	USART_init();
	//DDRA=0xFF;
	
	MCUCR |= (1 << SRE);
	
	while(1){
		SRAM_test();
	}
	
	
	/*
	while(1)
	{
		
		
		int i;
		scanf("%d", &i);
		printf("Hello World! %d\n", i);
		
		
		_delay_ms(1000);		
	}
	*/

	
	/*
	DDRA=0xFF;
    while(1)
    {
        //TODO:: Please write your application code 
	
		PORTA=0xFF;
		_delay_ms(500);
		PORTA=0x0;
		_delay_ms(500);
		
    }
	*/
	
}


