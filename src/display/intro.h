/*
 * intro.h
 *
 * Created: 15.11.2015 22:03:57
 *  Author: vegasten
 */ 


#ifndef INTRO_H_
#define INTRO_H_


#include "OLED_driver.h"


void intro_run_intro();

//Lightning
void intro_lightning();
void intro_print_all_lightnings();
void intro_print_all_inverted_lightnings();
void intro_print_lightning(int position);
void intro_invert_screen(int inverted);
void intro_print_inverted_lightning(int position);

//Text
void intro_print_text();
void intro_print_blinking_text(uint8_t time, uint8_t period, uint8_t line, uint8_t pos, char* text);
void intro_print_P(int position);
void intro_print_I(int position);
void intro_print_N(int position);
void intro_print_G(int position);
void intro_print_O(int position);

//Ball and start game
void intro_draw_ball(uint8_t i);
void intro_print_ball_and_start_game(int end_position);
void intro_print_start_game();
void intro_ball_enter_screen();
void intro_ball_exit_screen();









#endif /* INTRO_H_ */