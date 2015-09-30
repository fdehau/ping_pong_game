/*
 * SPI_driver.c
 *
 * Created: 30.09.2015 11:06:21
 *  Author: vegasten
 */ 

#include "SPI_driver.h"

void SPI_init()
{
	// Master
	DDRB = (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
	DDRB &= ~(1 << PB6);
	PORTB |= (1 << PB6);
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
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