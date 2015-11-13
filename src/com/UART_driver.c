/**
 * @file UART_driver.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for UART protocol
 */

#include "UART_driver.h"

/**
 * @brief      Initialize the UART driver
 */
void UART_init(void)
{
    UBRR0H  = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L  = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << URSEL0) | (3 << UCSZ00);

    fdevopen(&UART_send, &UART_receive);
}

/**
 * @brief      Send one character over UART
 *
 * @param[in]  data       Char to send
 * @param      dummy      File
 *
 * @return     1
 */
int UART_send(unsigned char data, struct __file* dummy)
{
    while (!(UCSR0A & (1 << UDRE0))){}
    UDR0 = data;
    return 1;
}

/**
 * @brief      Receive one char over UART
 *
 * @param      dummy  File
 *
 * @return     Character read
 */
int UART_receive(struct __file* dummy)
{
    while (!(UCSR0A & (1 << RXC0))){}
    return UDR0;
}