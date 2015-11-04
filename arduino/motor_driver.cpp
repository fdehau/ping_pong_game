/*
 * motor_driver.cpp
 *
 * Created: 28.10.2015 17:11:54
 *  Author: vegasten
 */ 

#include "motor_driver.h"

void motor_init() {
	
	Wire.begin();
	Wire.setClock(50000L);
	
	pinMode(A7, OUTPUT); //Output enable
	pinMode(A6, OUTPUT); //Reset
	pinMode(A5, OUTPUT); //Byte select
	pinMode(A4, OUTPUT); //Enable motor
	pinMode(A3, OUTPUT); //Set direction
	
	pinMode(20, OUTPUT); // SDA
	pinMode(21, OUTPUT); // SCL
	
	DDRK = 0;
	
	motor_enable_output(1);
	motor_reset();
	motor_select_encoder_byte(1);
	motor_enable(1);
	
	motor_set_direction(1);
}



void motor_write(uint8_t speed) {
	
	Wire.beginTransmission(DAC_ADRESS);
	
	Wire.write(0x00);
	Wire.write(speed); //0-255?
	
	Wire.endTransmission();
}


void motor_read() {
	

}


void motor_enable_output(uint8_t enable) {
	enable ? digitalWrite(A7, LOW) : digitalWrite(A7, HIGH);
}

void motor_reset() {
	digitalWrite(A6, HIGH);
	delayMicroseconds(20);
	digitalWrite(A6, LOW);
}

void motor_select_encoder_byte(uint8_t high) {
	high ? digitalWrite(A5, HIGH) : digitalWrite(A5, LOW);
}

void motor_enable(uint8_t enable) {
	enable ? digitalWrite(A4, HIGH) : digitalWrite(A4, LOW);
}

void motor_set_direction(uint8_t direction) {
	direction ? digitalWrite(A3, HIGH) : digitalWrite(A3, LOW);
}

void motor_control(int8_t value) {
	motor_set_direction(value > 0);
	motor_write(abs(value));
}




