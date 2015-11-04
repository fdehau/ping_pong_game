/*
 * SPI_driver.c
 *
 * Created: 30.09.2015 11:06:21
 *  Author: vegasten
 */ 

#include "SPI_driver.h"
#include <Arduino.h>
void SPI_init()
{
	DDRB   = (1 << DDB1) | (1 << DDB2) | (1 << DDB0);
	DDRB  &= ~(1 << PB3);
	PORTB |= (1 << PB3);
	SPCR  |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

void SPI_send(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF))){}
}

uint8_t SPI_read()
{
	SPI_send('$');
	while(!(SPSR & (1 << SPIF))){}
	return SPDR;
} 