/*
 * ir_driver.cpp
 *
 * Created: 30.10.2015 11:40:52
 *  Author: vegasten
 */ 

#include "ir_driver.h"

void ir_init()
{
	pinMode(A0, INPUT);
}

int ir_check()
{
	int value = analogRead(A0);
	int result = 0;
	if (value < THRESHOLD) {
		if (last_check)
			result = 2;
		else {
			last_check = 1;
			result = 1;
		}
	}
	else
		last_check = 0;
	return result;
}