/**
 * @file CAN_driver.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for CAN protocol
 */

#include "CAN_driver.h"

/**
 * @brief Initialize the CAN driver
 * @details Inialize the MCP2515 driver, deactivate the filters and the
 * rollover and configure the first receiving buffer (RX0)
 *
 * @param mode The CAN mode the controller should be configured with
 */
void CAN_init(uint8_t mode)
{
    MCP2515_init();

    MCP2515_bit_modify(CAN_RCV_CTRL_REG, CAN_RCV_MASK,
                       CAN_RCV_NO_FILTERS | CAN_RCV_NO_ROLLOVER);
    MCP2515_bit_modify(MCP_CANINTE, MCP_CANINTE_RX0_FULL_ENABLE_MASK,
                       MCP_CANINTE_RX0_FULL_ENABLE);

    MCP2515_bit_modify(MCP_CANCTRL, MCP_MODE_MASK, mode);
}


/**
 * @brief Send a message over CAN
 * @details The function will wait for an empty buffer, then put the message
 * in the buffer and finnaly signals the controller that there is a message to
 * send.
 * @param message Message to send
 * @return 0
 */
uint8_t CAN_send(CanMessage_t* message)
{
    while (MCP2515_read(CAN_TR_CTRL_REG) & CAN_TR_REQUEST)
    {
    }

    MCP2515_write(CAN_TR_ID_ADDR_1, message->id >> 3);
    MCP2515_write(CAN_TR_ID_ADDR_2, message->id << 5);
    MCP2515_write(CAN_TR_LEN_ADDR, message->length);
    for (int i = 0; i < message->length; i++)
    {
        MCP2515_write(CAN_TR_DATA_ADDR + i, message->data[i]);
    }
    MCP2515_request_to_send(MCP_RTS_TXB0);
    return 0;
}


/**
 * @brief Receive a message over CAN
 * @return A message with the default id (0) if there was no incoming message
 */
CanMessage_t CAN_receive()
{
    CanMessage_t message;

    memset(&message, 0, sizeof(CanMessage_t));

    if (MCP2515_read(MCP_CANINTF) & MCP_CANINTF_RX0_TEST)
    {
        uint8_t id_part1 = MCP2515_read(CAN_RCV_ID_ADDR_1) << 3;
        uint8_t id_part2 = MCP2515_read(CAN_RCV_ID_ADDR_2) >> 5;
        message.id     = id_part1 | id_part2;
        message.length = MCP2515_read(CAN_RCV_LEN_ADDR) & 0x0F;
        for (int i = 0; i < message.length; i++)
        {
            message.data[i] = MCP2515_read(CAN_RCV_DATA_ADDR + i);
        }

        MCP2515_bit_modify(MCP_CANINTF, MCP_CANINTF_RX0_CLEAR_MASK,
                           MCP_CANINTF_RX0_CLEAR);
    }

    return message;
}


/**
 * @brief Util function to print the content of a message
 * @param msg Message to print
 */
void CAN_print_message(CanMessage_t* msg)
{
    printf("+--- Message %d ---+\n", msg->id);
    printf("\t");
    for (int i = 0; i < msg->length; i++)
    {
        printf("%d ", msg->data[i]);
    }
    printf("\n");
}
