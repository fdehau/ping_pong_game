/*
 * intro.c
 *
 * Created: 15.11.2015 22:03:43
 *  Author: vegasten
 */ 
#include "intro.h"
#include "../util.h"
#include "../input/input.h"

volatile char* oled_data = (char*) 0x1200;

void intro_run_intro(int button){
	
	intro_lightning();
	_delay_ms(1000);
	intro_lightning();
	_delay_ms(200);
	intro_lightning();
	_delay_ms(2000);
	intro_lightning();
	_delay_ms(200);
	intro_lightning();
	_delay_ms(100);
	intro_lightning();
	intro_print_text();
	_delay_ms(1500);
	
	intro_print_text();
	
	_delay_ms(1000);
		
	intro_print_ball_and_start_game(114); 
	//OLED_clr();
}


void intro_lightning(){
	
	int i;
	for(i = 0; i<5; i++)
	{
		intro_invert_screen(0);
		intro_print_all_inverted_lightnings();
		_delay_ms(20);
		
		intro_invert_screen(1);
		intro_print_all_lightnings();
		_delay_ms(20);
	}
	
	OLED_clr();
}


void intro_print_all_lightnings(){
	intro_print_lightning(10);
	intro_print_lightning(41);
	intro_print_lightning(76);
	intro_print_lightning(107);
}

void intro_print_all_inverted_lightnings(){
	intro_print_inverted_lightning(10);
	intro_print_inverted_lightning(41);
	intro_print_inverted_lightning(76);
	intro_print_inverted_lightning(107);
}
	

void intro_print_lightning(int position){

	OLED_pos(0,position,10);
	*oled_data = 0b00000000;
	*oled_data = 0b11000000;
	*oled_data = 0b11110000;
	*oled_data = 0b11111100;
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b11011111;
	*oled_data = 0b11000111;
	*oled_data = 0b01000001;
	
	OLED_pos(1,position,9);
	*oled_data = 0b00000000;
	*oled_data = 0b00000011;
	*oled_data = 0b11100011;
	*oled_data = 0b11111011;
	*oled_data = 0b11111111;
	*oled_data = 0b01111111;
	*oled_data = 0b00111111;
	*oled_data = 0b00011111;
	*oled_data = 0b00001111;
	*oled_data = 0b00000011;
	
	OLED_pos(2,position,4);
	*oled_data = 0b00000000;
	*oled_data = 0b00001111;
	*oled_data = 0b00000111;
	*oled_data = 0b00000011;
	*oled_data = 0b00000001;	


}

void intro_invert_screen(int inverted){
	
	if(inverted){
		for (int i = 0; i < 8; i++)
		{
			OLED_pos(i, 0, 127);
			for (int j = 0; j < 128; j++)
			{
				*oled_data = 0x00;
			}
		}
	}	
	else{
		
		for (int i = 0; i < 8; i++)
		{
			OLED_pos(i, 0, 127);
			for (int j = 0; j < 128; j++)
			{
				*oled_data = 0xFF;
			}
		}		
	}
}

void intro_print_inverted_lightning(int position){
	OLED_pos(0,position,10);
	*oled_data = 0b11111111;
	*oled_data = 0b00111111;
	*oled_data = 0b00001111;
	*oled_data = 0b00000011;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00100000;
	*oled_data = 0b00111000;
	*oled_data = 0b10111110;
	
	OLED_pos(1,position,9);
	*oled_data = 0b11111111;
	*oled_data = 0b11111100;
	*oled_data = 0b00011100;
	*oled_data = 0b00000100;
	*oled_data = 0b00000000;
	*oled_data = 0b10000000;
	*oled_data = 0b11000000;
	*oled_data = 0b11100000;
	*oled_data = 0b11110000;
	*oled_data = 0b11111100;
	
	OLED_pos(2,position,4);
	*oled_data = 0b11111111;
	*oled_data = 0b11110000;
	*oled_data = 0b11111000;
	*oled_data = 0b11111100;
	*oled_data = 0b11111110;	
}

void intro_print_text(){
	
	intro_print_P(20);
	intro_print_I(30);
	intro_print_N(33);
	intro_print_G(44);
	
	intro_print_P(66);
	intro_print_O(76);
	intro_print_N(86);
	intro_print_G(97);
}

void intro_print_P(int position){
	OLED_pos(5,position,8);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b10000011;
	*oled_data = 0b10000011;
	*oled_data = 0b10000011;
	*oled_data = 0b10000111;
	*oled_data = 0b10001110;
	*oled_data = 0b11111100;
	*oled_data = 0b01111000;
	OLED_pos(6,position,8);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b00000001;
	*oled_data = 0b00000001;
	*oled_data = 0b00000001;
	*oled_data = 0b00000001;
	*oled_data = 0b00000001;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
}

void intro_print_I(int position){
	//I
	OLED_pos(5,position,1);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	OLED_pos(6,position,1);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
}

void intro_print_N(int position){
	//N
	OLED_pos(5,position,9);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b00001100;
	*oled_data = 0b00111000;
	*oled_data = 0b11100000;
	*oled_data = 0b10000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;

	OLED_pos(6,position,9);
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000011;
	*oled_data = 0b00001110;
	*oled_data = 0b00111000;
	*oled_data = 0b11111111;
	*oled_data = 0b11111111;
}

void intro_print_G(int position){
	//G
	OLED_pos(5,position,8);
	*oled_data = 0b11111000;
	*oled_data = 0b11111100;
	*oled_data = 0b00001110;
	*oled_data = 0b00000111;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;

	OLED_pos(6,position,8);
	*oled_data = 0b00111111;
	*oled_data = 0b01111111;
	*oled_data = 0b01100000;
	*oled_data = 0b11000000;
	*oled_data = 0b11000011;
	*oled_data = 0b11000011;
	*oled_data = 0b11100011;
	*oled_data = 0b01111111;
	*oled_data = 0b00111111;
}

void intro_print_O(int position){
	//O
	OLED_pos(5,position,8);
	*oled_data = 0b11111000;
	*oled_data = 0b11111100;
	*oled_data = 0b00000110;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;
	*oled_data = 0b00000011;
	*oled_data = 0b00000110;
	*oled_data = 0b11111100;
	*oled_data = 0b11111000;

	OLED_pos(6,position,8);
	*oled_data = 0b00011111;
	*oled_data = 0b00111111;
	*oled_data = 0b01100000;
	*oled_data = 0b11000000;
	*oled_data = 0b11000000;
	*oled_data = 0b11000000;
	*oled_data = 0b01100000;
	*oled_data = 0b00111111;
	*oled_data = 0b00011111;
}

void intro_draw_ball(uint8_t i)
{
	if(i!=0){
		OLED_pos(2, i-1, 5);
		*oled_data = 0x00;

		OLED_pos(3, i-1, 5);
		*oled_data = 0x00;
	}
	OLED_pos(2, i, 12);
	*oled_data = 0b11110000;
	*oled_data = 0b11111000;
	*oled_data = 0b11111100;
	*oled_data = 0b11111100;
	*oled_data = 0b11111110;
	*oled_data = 0b11111110;
	*oled_data = 0b11111110;
	*oled_data = 0b11001110;
	*oled_data = 0b10001100;
	*oled_data = 0b10001100;
	*oled_data = 0b11111000;
	*oled_data = 0b11110000;
	*oled_data = 0b00000000;

	OLED_pos(3, i, 12);
	*oled_data = 0b00000111;
	*oled_data = 0b00001111;
	*oled_data = 0b00011111;
	*oled_data = 0b00011111;
	*oled_data = 0b00111111;
	*oled_data = 0b00111111;
	*oled_data = 0b00111111;
	*oled_data = 0b00111111;
	*oled_data = 0b00011111;
	*oled_data = 0b00011111;
	*oled_data = 0b00001111;
	*oled_data = 0b00000111;
	*oled_data = 0b00000000;
	_delay_ms(30);
}

//Ball and Start Game
void intro_print_ball_and_start_game(int end_position){
	intro_ball_enter_screen();
	int i;
	for (i = 0; i<end_position; i++)
	{
		intro_draw_ball(i);
		intro_print_blinking_text(i, 40, 7, 25, "Starting game...");
	}
	intro_ball_exit_screen();
}

void intro_print_blinking_text(uint8_t time, uint8_t period, uint8_t line, uint8_t pos, char* text)
{
	OLED_pos(line, pos, 127 - pos);
	if(time % period == 0)
		OLED_print(text);
	else if(time % (period / 2) == 0)
		OLED_clear_line(line);
}

void intro_ball_enter_screen(){
	
	int i;
	for (i = 0; i < 13; i++){
		OLED_pos(2, 0, 12);
		if (i>12)
			*oled_data = 0b11110000;
		if (i>11)
			*oled_data = 0b11111000;
		if (i>10)
			*oled_data = 0b11111100;
		if (i>9)
			*oled_data = 0b11111100;
		if (i>8)
			*oled_data = 0b11111110;
		if (i>7)
			*oled_data = 0b11111110;
		if (i>6)
			*oled_data = 0b11111110;
		if (i>5)
			*oled_data = 0b11001110;
		if (i>4)
			*oled_data = 0b10001100;
		if (i>3)
			*oled_data = 0b10001100;
		if (i>2)
			*oled_data = 0b11111000;
		if (i>1)
			*oled_data = 0b11110000;
		if (i>=0)
			*oled_data = 0b00000000;

		OLED_pos(3, 0, 12);
		if (i>12)
			*oled_data = 0b00000111;
		if (i>11)
			*oled_data = 0b00001111;
		if (i>10)
			*oled_data = 0b00011111;
		if (i>9)
			*oled_data = 0b00011111;
		if (i>8)
			*oled_data = 0b00111111;
		if (i>7)
			*oled_data = 0b00111111;
		if (i>6)
			*oled_data = 0b00111111;
		if (i>5)
			*oled_data = 0b00111111;
		if (i>4)
			*oled_data = 0b00011111;
		if (i>3)
			*oled_data = 0b00011111;
		if (i>2)
			*oled_data = 0b00001111;
		if (i>1)
			*oled_data = 0b00000111;
		if (i>=0)
			*oled_data = 0b00000000;
		_delay_ms(30);
	}
	
}
	
void intro_ball_exit_screen(){
	int i;
	for (i = 0; i < 14; i++){
		OLED_pos(2, 113 + i, 13 - i);
		*oled_data = 0x00;
		if (i < 13)
			*oled_data = 0b11110000;
		if (i < 12)
			*oled_data = 0b11111000;
		if (i < 11)
			*oled_data = 0b11111100;
		if (i < 10)
			*oled_data = 0b11111100;
		if (i < 9)
			*oled_data = 0b11111110;
		if (i < 8)
			*oled_data = 0b11111110;
		if (i < 7)
			*oled_data = 0b11111110;
		if (i < 6)
			*oled_data = 0b11001110;
		if (i < 5)
			*oled_data = 0b10001100;
		if (i < 4)
			*oled_data = 0b10001100;
		if (i < 3)
			*oled_data = 0b11111000;
		if (i < 2)
			*oled_data = 0b11110000;
		if (i < 1)
			*oled_data = 0b00000000;

		OLED_pos(3, 113 + i, 13 - i);
		*oled_data = 0x00;
		if (i < 13)
			*oled_data = 0b00000111;
		if (i < 12)
			*oled_data = 0b00001111;
		if (i < 11)
			*oled_data = 0b00011111;
		if (i < 10)
			*oled_data = 0b00011111;
		if (i < 9)
			*oled_data = 0b00111111;
		if (i < 8)
			*oled_data = 0b00111111;
		if (i < 7)
			*oled_data = 0b00111111;
		if (i < 6)
			*oled_data = 0b00111111;
		if (i < 5)
			*oled_data = 0b00011111;
		if (i < 4)
			*oled_data = 0b00011111;
		if (i < 3)
			*oled_data = 0b00001111;
		if (i < 2)
			*oled_data = 0b00000111;
		if (i < 1)
			*oled_data = 0b00000000;

		_delay_ms(30);
	}
}
	

	
	
	
	
	
	
	
	
	
	

	
