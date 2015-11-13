/**
 * @file SPI_driver.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for SPI protocol
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>
#include <stdint-gcc.h>

void    SPI_init();
void    SPI_send(uint8_t data);
uint8_t SPI_read();

#endif /* SPI_DRIVER_H_ */