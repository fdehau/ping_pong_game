/*
 * JOYSTICK_driver.h
 *
 * Created: 09.09.2015 15:16:52
 *  Author: vegasten
 */ 


#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ADC_driver.h"
#include "util.h"

enum JOY_direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL	
};
typedef enum JOY_direction JOY_direction_t;

struct JOY_position
{
	int X;
	int Y;	
};
typedef struct JOY_position JOY_position_t;

enum JOY_button
{
	JOY_BUTTON,
	JOY_LEFT_SLIDER,
	JOY_RIGHT_SLIDER,
	JOY_LEFT_BUTTON,
	JOY_RIGHT_BUTTON,
	JOY_ENTER_BUTTON,
	JOY_BACK_BUTTON,
};

uint8_t JOY_X_INIT;
uint8_t JOY_Y_INIT;
const static int JOY_THRESHOLD = 20;

void JOY_init();
void JOY_calibrate();
uint8_t JOY_getButton(enum JOY_button button);
JOY_position_t JOY_getPosition();
JOY_direction_t JOY_getDirection();
char* direction_to_string(JOY_direction_t direction);

#endif /* JOYSTICK_DRIVER_H_ */