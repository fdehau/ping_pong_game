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
	OCR2B = LOWER_DUTY_CYCLE * TOP_VALUE;
	delay(2000);
	Serial.println(OCR2B, BIN);
	Serial.println(MID_DUTY_CYCLE);
	Serial.println(LOWER_BOUND);
}


void servo_set_duty_cycle(float value)
{
	if(value < LOWER_DUTY_CYCLE || value > HIGHER_DUTY_CYCLE)
		return;
	OCR2B = value * TOP_VALUE;	
}