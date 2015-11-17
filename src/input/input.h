/**
 * @file input.h
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Input interface
 * Store the input states and provides functions to interpret them and send
 * them to the node 2
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "JOYSTICK_driver.h"

enum SWIPE
{
    SWIPE_UP,
    SWIPE_LEFT,
    SWIPE_DOWN,
    SWIPE_RIGHT,
    SWIPE_NEUTRAL,
};

struct Input
{
    uint8_t enter_button[2];
    uint8_t back_button[2];
    JOY_direction_t joy_direction[2];
    JOY_position_t joy_position[2];
    uint8_t left_slider[2];
    uint8_t right_slider[2];
};
typedef struct Input Input_t;

void       update(Input_t* input);
int        is_enter_pressed(Input_t* input);
int        is_back_pressed(Input_t* input);
enum SWIPE get_gesture(Input_t* input);
void       send_input(Input_t* input);

#endif /* INPUT_H_ */
