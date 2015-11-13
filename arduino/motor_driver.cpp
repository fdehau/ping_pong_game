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
    controller->KP = 3;
    controller->KI = 5;
	controller->KD = 1;

    motor_control(-100);
    _delay_ms(1000);
    motor_reset();
    controller->min = -motor_read();
    motor_control(100);
    _delay_ms(1000);
    controller->max = -motor_read();
    controller_set_reference(controller, (controller->max - controller->min) / 2);
	motor_control(0);
}

void controller_set_reference(Controller* controller, int8_t value)
{
    controller->reference += INPUT_COEFF * value;
	if (controller->reference > controller->max)
	{
		controller->reference = controller->max;
	}
	else if (controller->reference < controller->min)
	{
		controller->reference = controller->min;
	}
}

void controller_pi(Controller* controller, int16_t dt)
{
    int16_t current = -motor_read();
	int16_t error = (controller->reference - current) / 10;
    controller->integral += error * dt / 1000;
	int16_t derivative = error - controller->error;
    int16_t output = error / controller->KP + controller->integral / controller->KI + derivative * controller->KD;
	printf("output: %d\n", output);
	if (output > 127)
		output = 127;
	else if (output < -127)
		output = -127;
    printf("| %d - %d = %d  |  %d + %d + %d = %d\n", current, controller->reference, error, error / controller->KP, controller->integral / controller->KI, derivative * controller->KD, (int8_t) output);
    motor_control((int8_t) output);
    controller->error = error;
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




