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
#define INPUT_COEFF 10

typedef struct
{
    int16_t position;
    int16_t max;
	int16_t min;
    int16_t reference;
    int16_t KP;
    int16_t KI;
	int16_t KD;
    int16_t error;
    int16_t integral;
} Controller;

void    motor_init();
void    motor_set_direction(uint8_t direction);
void    motor_write(uint8_t speed);
int16_t motor_read();

void motor_enable_output(uint8_t enable);
void motor_reset();
void motor_select_encoder_byte(uint8_t high);
void motor_enable(uint8_t enable);
void motor_control(int8_t value);

void controller_calibrate(Controller* controller);
void controller_set_reference(Controller* controller, int8_t value);
void controller_pi(Controller* controller, int16_t dt);


#endif /* MOTOR_DRIVER_H_ */