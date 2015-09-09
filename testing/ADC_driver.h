/*
 * ADC_driver.h
 *
 * Created: 09.09.2015 12:33:16
 *  Author: vegasten
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#define F_CPU 4915200
#include <util/delay.h>

#include "util.h"

enum channel {
	JOY_X = 7,
	JOY_Y = 6,
	LEFT_SLIDER = 4,
	RIGHT_SLIDER = 5	
};

uint8_t ADC_read(enum channel channel); 



#endif /* ADC_DRIVER_H_ */