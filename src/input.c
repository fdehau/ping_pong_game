/*
 * input.c
 *
 * Created: 23.09.2015 15:12:07
 *  Author: vegasten
 */ 

#include "input.h"

void update(Input_t* input)
{
	
	// Update joystick direction
	input->joy_direction[1] = input->joy_direction[0];
	input->joy_direction[0] = JOY_getDirection();
	
	// Update enter button state
	input->enter_button[1] = input->enter_button[0];
	input->enter_button[0] = JOY_getButton(JOY_ENTER_BUTTON);
	
	// Update back button state
	input->back_button[1] = input->back_button[0];
	input->back_button[0] = JOY_getButton(JOY_BACK_BUTTON);
}

int is_enter_pressed(Input_t* input)
{
	return input->enter_button[0] != input->enter_button[1] && input->enter_button[0] == 0; 
}

int is_back_pressed(Input_t* input)
{
	return input->back_button[0] != input->back_button[1] && input->back_button[0] == 0;
}

enum SWIPE get_gesture(Input_t* input)
{
	if(input->joy_direction[0] == UP && input->joy_direction[1] == NEUTRAL)
		return SWIPE_UP;
	else if(input->joy_direction[0] == LEFT && input->joy_direction[1] == NEUTRAL)
		return SWIPE_LEFT;
	else if(input->joy_direction[0] == DOWN && input->joy_direction[1] == NEUTRAL)
		return SWIPE_DOWN;
	else if(input->joy_direction[0] == RIGHT && input->joy_direction[1] == NEUTRAL)
		return SWIPE_RIGHT;
	else 
		return SWIPE_NEUTRAL;
};	
