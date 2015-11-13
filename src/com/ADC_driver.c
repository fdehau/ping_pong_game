/**
 * @file ADC_driver.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for ADC protocol
 */

#include "ADC_driver.h"


/**
 * @brief Read char on a given channel
 *
 * @param channel The channel to read from
 * @return Value read on channel
 */
uint8_t ADC_read(enum channel channel)
{
    volatile char* start_mem = (char*) 0x1400;
    *start_mem = channel;
    _delay_us(40);
    return *start_mem;
}