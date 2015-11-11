/*
 * input.c
 *
 * Created: 23.09.2015 15:12:07
 *  Author: vegasten
 */ 

#include "input.h"
#include "CAN_driver.h"

void update(Input_t* input)
{
	
	// Update joystick direction
	input->joy_direction[1] = input->joy_direction[0];
	input->joy_direction[0] = JOY_getDirection();
	
	// Update joystick position
	input->joy_position[1] = input->joy_position[0];
	input->joy_position[0] = JOY_getPosition();
	
	// Update enter button state
	input->enter_button[1] = input->enter_button[0];
	input->enter_button[0] = JOY_getButton(JOY_ENTER_BUTTON);
	
	// Update back button state
	input->back_button[1] = input->back_button[0];
	input->back_button[0] = JOY_getButton(JOY_BACK_BUTTON);
	
	// Update left slider
	input->left_slider[1] = input->left_slider[0];
	input->left_slider[0] = JOY_getButton(JOY_LEFT_SLIDER);

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

void send_input(Input_t* input)
{
	CanMessage_t message;

	if (input->joy_position[0].X != input->joy_position[1].X ||
		input->joy_position[0].Y != input->joy_position[1].Y ||
		input->left_slider[0] != input->left_slider[1])
	{
		message.id = INPUT_ID;
		message.length = 4;
		message.data[0] = input->joy_direction[0];
		message.data[1] = input->joy_position[0].X;
		message.data[2] = input->joy_position[0].Y;
		message.data[3] = input->left_slider[0];
		CAN_print_message(&message);
		CAN_send(&message);
	}
}