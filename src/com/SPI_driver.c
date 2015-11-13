/**
 * @file SPI_driver.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for SPI protocol
 */

#include "SPI_driver.h"

/**
 * @brief      Initialize the SPI driver
 */
void SPI_init()
{
    // Master
    DDRB   = (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
    DDRB  &= ~(1 << PB6);
    PORTB |= (1 << PB6);
    SPCR  |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

/**
 * @brief      Send character over SPI
 *
 * @param[in]  data    Data to be sent
 */
void SPI_send(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)))
    {
    }
}

/**
 * @brief      Read one character over SPI
 *
 * @return     Character read
 */
uint8_t SPI_read()
{
    SPI_send('$');
    while (!(SPSR & (1 << SPIF)))
    {
    }
    return SPDR;
}