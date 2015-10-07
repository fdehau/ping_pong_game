/*
 * SPI_driver.h
 *
 * Created: 30.09.2015 11:06:48
 *  Author: vegasten
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>
#include <stdint-gcc.h>

void SPI_init();
void SPI_send(uint8_t data);
uint8_t SPI_read();

#endif /* SPI_DRIVER_H_ */