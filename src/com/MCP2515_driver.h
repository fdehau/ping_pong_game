/*
 * @file MCP2515_driver.h
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Provides basic interface with the MCP2515 chip (read, write, ...)
 *        through SPI
 */

#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

#include <avr/io.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <string.h>

#include "../util.h"
#include "SPI_driver.h"

#define MCP_CANSTAT       0b00001110
#define MCP_CANCTRL       0b00001111
#define MCP_MODE_MASK     0b11100000

#define MCP_MODE_NORMAL   0b00000000
#define MCP_MODE_SLEEP    0b00100000
#define MCP_MODE_LOOPBACK 0b01000000
#define MCP_MODE_LISTEN   0b01100000
#define MCP_MODE_CONFIG   0b10000000

#define MCP_READ          0b00000011
#define MCP_WRITE         0b00000010
#define MCP_RESET         0b11000000
#define MCP_READ_STATUS   0b10100000
#define MCP_BIT_MODIFY    0b00000101
#define MCP_RX_STATUS     0b10110000

#define MCP_RTS_TXB0 0b10000001
#define MCP_RTS_TXB1 0b10000010
#define MCP_RTS_TXB2 0b10000100

#define MCP_CANINTE                         0x2B
#define MCP_CANINTE_RX0_FULL_ENABLE         0xFF
#define MCP_CANINTE_RX0_FULL_ENABLE_MASK    0b00000001
#define MCP_CANINTE_RX0_FULL_DISABLE        0x00
#define MCP_CANINTE_RX0_FULL_DISABLE_MASK   0b00000001


#define MCP_CANINTF                0x2C
#define MCP_CANINTF_RX0_CLEAR      0x00
#define MCP_CANINTF_RX0_CLEAR_MASK 0b00000001
#define MCP_CANINTF_RX0_TEST       0b00000001

void    MCP2515_init();
uint8_t MCP2515_read(uint8_t address);
uint8_t MCP2515_read_status();
void    MCP2515_write(uint8_t address, const uint8_t data);
void    MCP2515_request_to_send(uint8_t buffer);
void    MCP2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data);
void    MCP2515_reset();

#endif /* MCP2515_DRIVER_H_ */