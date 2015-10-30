/*
 * ir_driver.h
 *
 * Created: 30.10.2015 11:39:04
 *  Author: vegasten
 */ 


#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_

#include <Arduino.h>

#define THRESHOLD 100

static int last_check = 0;

void ir_init();
int ir_check();

#endif /* IR_DRIVER_H_ */