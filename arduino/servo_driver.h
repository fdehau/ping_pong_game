/*
 * servo_driver.h
 *
 * Created: 21.10.2015 15:16:30
 *  Author: vegasten
 */


#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

#include "Arduino.h"

const float TOP_VALUE         = 156;
const float PERIOD            = 20.0;
const float LOWER_BOUND       = 1.0;
const float HIGHER_BOUND      = 2.0;
const float LOWER_DUTY_CYCLE  = LOWER_BOUND / PERIOD;
const float HIGHER_DUTY_CYCLE = HIGHER_BOUND / PERIOD;
const float MID_DUTY_CYCLE    = (HIGHER_DUTY_CYCLE + LOWER_DUTY_CYCLE) / 2;
const float WIDTH_DUTY_CYCLE  = (HIGHER_DUTY_CYCLE - LOWER_DUTY_CYCLE) / 2;

void servo_init();
void servo_set_duty_cycle(float value);
void servo_joystick_control(float value);

#endif /* SERVO_DRIVER_H_ */