/*
 * motor_driver.h
 *
 * Created: 28.10.2015 17:12:12
 *  Author: vegasten
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>
#include <Wire/Wire.h>

#define DAC_ADRESS 0b0101000

void motor_init();
void motor_set_direction(uint8_t direction);
void motor_write(uint8_t speed);
void motor_read();


void motor_enable_output(uint8_t enable);
void motor_reset();
void motor_select_encoder_byte(uint8_t high);
void motor_enable(uint8_t enable);
void motor_control(int8_t value);

#endif /* MOTOR_DRIVER_H_ */