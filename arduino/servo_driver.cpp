/*
 * servo_driver.cpp
 *
 * Created: 21.10.2015 15:16:44
 *  Author: vegasten
 */

#include "servo_driver.h"

void servo_init()
{

    pinMode(10, OUTPUT); // 0C2A
    pinMode(9, OUTPUT); // 0C2B

    TCCR2A = (1 << (COM2A0))
             | (1 << (COM2B1))
             | (1 << (WGM20));
    TCCR2B = (1 << (WGM22))
             | (1 << (CS22)) // for 1024
             | (1 << (CS21))
             | (1 << (CS20));

    OCR2A = TOP_VALUE;

    float i;
    float n = WIDTH_DUTY_CYCLE / 30;
    for (i = LOWER_DUTY_CYCLE; i < HIGHER_DUTY_CYCLE; i += n)
    {
        servo_set_duty_cycle(i);
        delay(20);
    }
    servo_set_duty_cycle(MID_DUTY_CYCLE);
}


void servo_set_duty_cycle(float value)
{
    if (value < LOWER_DUTY_CYCLE || value > HIGHER_DUTY_CYCLE)
        return;
    OCR2B = value * TOP_VALUE;
}

void servo_joystick_control(float value)
{
    value *= -1;
    value  = value > 100 ? 100 : value;
    value  = ((value + 100) / 200 + 1) / PERIOD;
    servo_set_duty_cycle(value);
}