
/*
 * driver_ATMega_uart.c
 *
 * Created: 28.08.2015 14:38:25
 *  Author: vegasten
 */ 

//char tx_buffer[255], rx_buffer[255];
//void USART_send();
//void USART_init(void);
//unsigned char USART_recieve(void);

#include "driver_ATMega_uart.h"

void USART_init(void){
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0) | (3<<UCSZ00);
}

void USART_send(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char USART_recieve(void){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}