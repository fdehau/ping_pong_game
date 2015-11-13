/**
 * @file CAN_test.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Test suite for the CAN protocol
 */

#include "CAN_test.h"

/**
 * @brief    Put the CAN controller in loopback mode and test local features
 */
void CAN_test_loopback()
{
    CAN_init(MCP_MODE_LOOPBACK);

    CanMessage_t message;
    CanMessage_t resp;
    message.id      = 15;
    message.length  = 4;
    message.data[0] = 'T';
    message.data[1] = 'E';
    message.data[2] = 'S';
    message.data[3] = 'T';
    while (1)
    {
        CAN_send(&message);
        _delay_ms(200);
        resp = CAN_receive();
        CAN_print_message(&resp);
    }
}


/**
 * @brief    Put the controller in normal mode and make it send the same message
 *           over and over again
 */
void CAN_test_normal_send()
{

    CAN_init(MCP_MODE_NORMAL);

    CanMessage_t message;
    message.id      = 15;
    message.length  = 4;
    message.data[0] = 'T';
    message.data[1] = 'E';
    message.data[2] = 'S';
    message.data[3] = 'T';
    while (1)
    {
        CAN_send(&message);
        printf("Message sent!\n");
        //_delay_ms(200);
    }
}

/**
 * @brief      Put the controller in normal mode and make it receive incoming
 *             messages
 */
void CAN_test_normal_receive()
{
    CAN_init(MCP_MODE_NORMAL);

    CanMessage_t resp;

    while (1)
    {
        _delay_ms(200);
        resp = CAN_receive();
        CAN_print_message(&resp);
    }
}
