/*
 * MCP2515_driver.c
 *
 * Created: 30.09.2015 12:33:42
 *  Author: vegasten
 */ 

#include "MCP2515_driver.h"

uint8_t MCP2515_init()
{
	uint8_t value;
	
	SPI_init();
	MCP2515_reset();
	
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MCP_MODE_MASK) != MCP_MODE_CONFIG)
	{
		printf("[ERROR] MCP2515 is not in configuration mode after reset!\n");
		return 1;
	}
	return 0;
}


uint8_t MCP2515_read(uint8_t address)
{
	uint8_t result;
	PORTB &= ~(1 << PB4);
	
	SPI_send(MCP_READ);
	SPI_send(address);
	result = SPI_read();
	
	PORTB |= (1 << PB4);
	
	return result;
}

uint8_t MCP2515_read_status()
{
	uint8_t result;
	PORTB &= ~(1 << PB4);
	
	SPI_send(MCP_READ_STATUS);
	result = SPI_read();
	
	PORTB |= (1 << PB4);
	
	return result;
}

void MCP2515_write(uint8_t address, const uint8_t data)
{
	PORTB &= ~(1 << PB4);
	
	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);
	
	PORTB |= (1 << PB4);
}

void MCP2515_request_to_send(uint8_t buffer)
{
	PORTB &= ~(1 << PB4);
	
	SPI_send(buffer);
	
	PORTB |= (1 << PB4);
}

void MCP2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << PB4);
	
	SPI_send(MCP_BIT_MODIFY);
	SPI_send(reg);
	SPI_send(mask);
	SPI_send(data);
	
	PORTB |= (1 << PB4);
}

void MCP2515_reset()
{
	PORTB &= ~(1 << PINB4);
	
	SPI_send(MCP_RESET);
	
	PORTB |= (1 << PINB4);
}