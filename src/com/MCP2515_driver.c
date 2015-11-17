/*
 * @file MCP2515_driver.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Provides basic interface with the MCP2515 chip (read, write, ...)
 *        through SPI
 */

#include "MCP2515_driver.h"

/**
 * @brief      Initialize the driver for the CAN controller
 */
void MCP2515_init()
{
    uint8_t value = 0;

    SPI_init();
    MCP2515_reset();

    _delay_ms(50);

    //Wait for MCP to change modes
    while ((value & MCP_MODE_MASK) != MCP_MODE_CONFIG)
    {
        value = MCP2515_read(MCP_CANSTAT);
        MCP2515_reset();
        printf("[ERROR] MCP2515 is not in configuration mode after reset!\n");
    }
    printf("MCP2515 configuration mode... OK\n");

}

/**
 * @brief      Read value in memory of the CAN controller
 *
 * @param[in]  address  Where to read in the memory of the CAN controller
 *
 * @return     The value read
 */
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

/**
 * @brief      Read the current status of the CAN controller
 *
 * @return     The status of the controller
 */
uint8_t MCP2515_read_status()
{
    uint8_t result;

    PORTB &= ~(1 << PB4);

    SPI_send(MCP_READ_STATUS);
    result = SPI_read();

    PORTB |= (1 << PB4);

    return result;
}


/**
 * @brief      Write in the memory of the CAN controller
 *
 * @param[in]  address  Where to write in memory
 * @param[in]  data     What to write in memory
 */
void MCP2515_write(uint8_t address, const uint8_t data)
{
    PORTB &= ~(1 << PB4);

    SPI_send(MCP_WRITE);
    SPI_send(address);
    SPI_send(data);

    PORTB |= (1 << PB4);
}


/**
 * @brief      Tell the controller that one of the buffer is ready to be sent
 *over CAN
 *
 * @param[in]  buffer  Code associated with the buffer
 */
void MCP2515_request_to_send(uint8_t buffer)
{
    PORTB &= ~(1 << PB4);

    SPI_send(buffer);

    PORTB |= (1 << PB4);
}


/**
 * @brief      Change the value of a config register in the CAN controller
 *
 * @param[in]  reg   The configuration register that needs to be changed
 * @param[in]  mask  The mask used when writing
 * @param[in]  data  The new value for the register
 */
void MCP2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data)
{
    PORTB &= ~(1 << PB4);

    SPI_send(MCP_BIT_MODIFY);
    SPI_send(reg);
    SPI_send(mask);
    SPI_send(data);

    PORTB |= (1 << PB4);
}

/**
 * @brief      Reset the CAN controller
 */
void MCP2515_reset()
{
    PORTB &= ~(1 << PB4);

    SPI_send(MCP_RESET);

    PORTB |= (1 << PB4);
}