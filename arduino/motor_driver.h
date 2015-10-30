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

#define DAC_ADRESS 0b00101111

void motor_init();
void motor_write();
void motor_read();

#endif /* MOTOR_DRIVER_H_ */