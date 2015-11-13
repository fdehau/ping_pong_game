/**
 * @file ADC_driver.h
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Interface for ADC protocol
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include "../util.h"

enum channel
{
    JOY_X        = 7,
    JOY_Y        = 6,
    LEFT_SLIDER  = 4,
    RIGHT_SLIDER = 5
};

uint8_t ADC_read(enum channel channel);



#endif /* ADC_DRIVER_H_ */