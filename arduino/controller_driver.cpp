/*
 * controller_driver.cpp
 *
 * Created: 11.11.2015 12:08:58
 *  Author: vegasten
 */


#include "controller_driver.h"
#include "motor_driver.h"

uint16_t encoder_read()
{
    motor_enable_output(1);

    motor_select_encoder_byte(0);
    _delay_us(20);
    uint16_t high_byte = reverse_bits(PINK);
    Serial.println(PINK, BIN);
    Serial.println(high_byte, BIN);

    motor_select_encoder_byte(1);
    _delay_us(20);
    uint16_t low_byte = reverse_bits(PINK);
    Serial.println(PINK, BIN);
    Serial.println(low_byte, BIN);

    motor_reset();

    motor_enable_output(0);

    uint16_t result = ((high_byte << 8) | (low_byte));
    Serial.println(result, BIN);
    return result;
}

uint8_t reverse_bits(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}



