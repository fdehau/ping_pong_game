/*
 * motor_driver.cpp
 *
 * Created: 28.10.2015 17:11:54
 *  Author: vegasten
 */ 

#include "motor_driver.h"

void motor_init() {
	
	Wire.begin();
	
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A6, OUTPUT);
	
	DDRK = 0;
	
	PORTF |= (1 << A2);
	PORTF &= ~(1 << A3);
	PORTF |= (1 << A4);
	PORTF &= ~(1 << A5);
}

void motor_change_direction() {
	
}

void motor_write() {
	
	Wire.beginTransmission(DAC_ADRESS);
	
	
	Wire.endTransmission();
}


void motor_read() {
	

}