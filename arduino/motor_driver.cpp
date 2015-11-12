/*
 * motor_driver.cpp
 *
 * Created: 28.10.2015 17:11:54
 *  Author: vegasten
 */

#include "motor_driver.h"

void motor_init()
{

    Wire.begin();
    Wire.setClock(50000L);

    pinMode(A7, OUTPUT); //Output enable
    pinMode(A6, OUTPUT); //Reset
    pinMode(A5, OUTPUT); //Byte select
    pinMode(A4, OUTPUT); //Enable motor
    pinMode(A3, OUTPUT); //Set direction

    pinMode(20, OUTPUT); // SDA
    pinMode(21, OUTPUT); // SCL

    DDRK  &= 0;
    PORTK |= 1;

    motor_enable_output(1);
    motor_reset();
    motor_select_encoder_byte(1);
    motor_enable(1);

    motor_set_direction(1);

}

void controller_calibrate(Controller* controller)
{
    controller->KP = 1;
    controller->KI = 1;

    motor_control(-80);
    _delay_ms(1000);
    motor_reset();
    //int16_t after_reset = -motor_read();
    motor_control(80);
    _delay_ms(800);
    controller->max_encoder_value = -motor_read(); //- after_reset;
    controller_set_reference(controller, 255);
    motor_control(0);
}

void controller_set_reference(Controller* controller, uint8_t value)
{
    controller->reference = (int16_t) value;
}

void controller_pi(Controller* controller, int16_t dt)
{
    int16_t current = -(int32_t) motor_read() * 255 /
                      controller->max_encoder_value;
    int16_t error = controller->reference - current;
    controller->integral += error * dt / 1000;
    controller->error     = error;
    int16_t output = controller->KP * error + controller->KI *
                     controller->integral;
    int16_t command = output / 2;
    //printf("Dt: %d | Current: %d | Reference: %d | Error:%d | Max: %d |
    // Integral: %d |Output: %d | Command: %d\n", dt, current,
    // controller->reference, error, controller->max_encoder_value,
    // controller->integral, output, (int8_t) command);
    motor_control((int8_t) command);
    controller->last_output = output;
}


void motor_write(uint8_t speed)
{

    Wire.beginTransmission(DAC_ADRESS);

    Wire.write(0x00);
    Wire.write(speed); //0-255?

    Wire.endTransmission();
}


static inline uint8_t reverse_bits(uint8_t x)
{
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    x = (((x & 0xf0) >> 4) | ((x & 0x0f) << 4));
    return x;

}

int16_t motor_read()
{

    motor_enable_output(1);
    motor_select_encoder_byte(0);
    _delay_us(20);
    uint16_t high_byte = reverse_bits(PINK);

    motor_select_encoder_byte(1);
    _delay_us(20);
    uint16_t low_byte = reverse_bits(PINK);

    motor_enable_output(0);

    return (high_byte << 8) + low_byte;
}


void motor_enable_output(uint8_t enable)
{
    enable ? digitalWrite(A7, LOW) : digitalWrite(A7, HIGH);
}

void motor_reset()
{
    digitalWrite(A6, LOW);
    delayMicroseconds(50);
    digitalWrite(A6, HIGH);
}

void motor_select_encoder_byte(uint8_t high)
{
    high ? digitalWrite(A5, HIGH) : digitalWrite(A5, LOW);
}

void motor_enable(uint8_t enable)
{
    enable ? digitalWrite(A4, HIGH) : digitalWrite(A4, LOW);
}

void motor_set_direction(uint8_t direction)
{
    direction ? digitalWrite(A3, HIGH) : digitalWrite(A3, LOW);
}

void motor_control(int8_t value)
{
    motor_set_direction(value > 0);
    motor_write(abs(value));
}




