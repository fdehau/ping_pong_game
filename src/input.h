/*
 * input.h
 *
 * Created: 23.09.2015 15:11:53
 *  Author: vegasten
 */ 


#ifndef INPUT_H_
#define INPUT_H_

#include "JOYSTICK_driver.h"

enum SWIPE {
	SWIPE_UP,
	SWIPE_LEFT,
	SWIPE_DOWN,
	SWIPE_RIGHT,
	SWIPE_NEUTRAL,
};

struct Input {
	enum JOY_button enter_button[2];
	enum JOY_button back_button[2];
	JOY_direction_t joy_direction[2];
	JOY_position_t joy_position[2];
};
typedef struct Input Input_t;

void update(Input_t* input);
int is_enter_pressed(Input_t* input);
int is_back_pressed(Input_t* input);
enum SWIPE get_gesture(Input_t* input);
void send_joystick_position(Input_t* input);

#endif /* INPUT_H_ */