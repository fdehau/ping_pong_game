
/*
 * UART_driver.c
 *
 * Created: 28.08.2015 14:38:25
 *  Author: vegasten
 */ 

//char tx_buffer[255], rx_buffer[255];
//void USART_send();
//void USART_init(void);
//unsigned char USART_recieve(void);

#include "UART_driver.h"

void USART_init(void){
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<URSEL0) | (3<<UCSZ00);
	
	fdevopen(&USART_send,&USART_receive);
}

int USART_send(unsigned char data, struct __file* dummy){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	return 1;
}


int USART_receive(struct __file* dummy){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}