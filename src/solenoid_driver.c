/*
 * solenoid_driver.c
 *
 * Created: 04.11.2015 15:44:19
 *  Author: vegasten
 */ 

#include "solenoid_driver.h"
#include <avr/delay.h>
#include <avr/io.h>

void solenoid_init()
{
	DDRE = (1 << DDE0);
	PORTE |= (1 << PE0);
}
void solenoid_fire()
{
	PORTE &= ~(1 << PE0);
	_delay_ms(500);
	PORTE |= (1 << PE0);
}