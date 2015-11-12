/**
 * @file UART_driver.h
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for UART protocol
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>

#include "util.h"

#define BAUDRATE 9600
#define BAUD_PRESCALLER ((F_CPU / BAUDRATE / 16UL) - 1)


void UART_init(void);
int  UART_send(unsigned char data, struct __file* dummy);
int  UART_receive(struct __file* dummy);

#endif /* UART_DRIVER_H_ */