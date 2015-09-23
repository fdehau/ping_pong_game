/*
 * UART_driver.h
 *
 * Created: 02.09.2015 09:06:41
 *  Author: vegasten
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER ((F_CPU / BAUDRATE / 16UL)-1)


void USART_init(void);
int USART_send(unsigned char data, struct __file* dummy);
int USART_receive(struct __file* dummy);



#endif /* UART_DRIVER_H_ */