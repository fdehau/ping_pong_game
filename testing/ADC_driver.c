/*
 * ADC_driver.c
 *
 * Created: 09.09.2015 12:33:00
 *  Author: vegasten
 */ 

#include "ADC_driver.h"

uint8_t ADC_read(enum channel channel)
{
	volatile char* start_mem = (char *) 0x1400;
	*start_mem = channel;
	_delay_us(40);
	return *start_mem;
}