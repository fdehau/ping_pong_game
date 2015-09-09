/*
 * JOYSTICK_driver.c
 *
 * Created: 09.09.2015 15:16:40
 *  Author: vegasten
 */ 


#include "JOYSTICK_driver.h"

void JOY_init(){
	MCUCR |= (1 << SRE);
	JOY_calibrate();
}
	
	
void JOY_calibrate(){
	JOY_X_INIT = ADC_read(JOY_X);
	JOY_Y_INIT = ADC_read(JOY_Y);	
}
	

uint8_t JOY_getButton(enum JOY_button button){
	switch(button)
	{
		case JOY_BUTTON:
			return 0;
		case JOY_LEFT_SLIDER:
			return ADC_read(LEFT_SLIDER);
		case JOY_RIGHT_SLIDER:
			return ADC_read(RIGHT_SLIDER);
		case JOY_LEFT_BUTTON:
			return 0;
		case JOY_RIGHT_BUTTON:
			return 0;
	}
}

	
	
JOY_position_t JOY_getPosition(){
	JOY_position_t position;
	uint8_t JOY_X_value = ADC_read(JOY_X);
	uint8_t JOY_Y_value = ADC_read(JOY_Y);
	position.X = (JOY_X_value - JOY_X_INIT) * 100 / (255 - JOY_X_INIT) ;
	position.Y = (JOY_Y_value - JOY_Y_INIT) * 100 / (255 - JOY_Y_INIT) ;
	return position;
}
	
	
JOY_direction_t JOY_getDirection(){
	
	JOY_position_t position = JOY_getPosition();
	int max_value = abs(position.X) > abs(position.Y) ? abs(position.X) : abs(position.Y);
	if (max_value < JOY_THRESHOLD)
		return NEUTRAL;
	if (abs(position.X) > abs(position.Y))
		return position.X < 0 ? LEFT : RIGHT;
	else
		return position.Y > 0 ? UP : DOWN;
}

char* direction_to_string(JOY_direction_t direction){
	char* string = malloc(sizeof(char)*10);
	switch(direction)
	{
		case UP:
			memcpy(string, "Up", 10);
			break;
		case DOWN:
			memcpy(string, "Down", 10);
			break;
		case RIGHT:
			memcpy(string, "Right", 10);
			break;
		case LEFT:
			memcpy(string, "Left", 10);
			break;
		case NEUTRAL:
			memcpy(string, "Neutral", 10);
			break;
	}
	return string;
}