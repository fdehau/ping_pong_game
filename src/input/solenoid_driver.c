/**
 * @file solenoid_driver.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for solenoid
 */

#include "solenoid_driver.h"


#include <avr/io.h>

#include "../util.h"

/**
 * @brief      Initialize the solenoid driver
 */
void solenoid_init()
{
    // Set the first pin of port E as output
    DDRE   = (1 << DDE0);
    // Set the pin high
    PORTE |= (1 << PE0);
}

/**
 * @brief      Trigger the solenoid (quick inversion on output pin)
 */
void solenoid_fire()
{
    PORTE &= ~(1 << PE0);
    _delay_ms(500);
    PORTE |= (1 << PE0);
}