/**
 * @file input.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Input interface
 * Store the input states and provides functions to interpret them and send
 * them to the node 2
 */

#include "input.h"
#include "../com/CAN_driver.h"

/**
 * @brief Update current input states (store 2 last states)
 * @param input
 */
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

/**
 * @brief Check if the enter button (upper left button on IO card) is pressed
 * @param input
 * @return The button state:
 *   - 1: button pressed
 *   - 0: button released
 */
int is_enter_pressed(Input_t* input)
{
    return input->enter_button[0] != input->enter_button[1] &&
           input->enter_button[0] == 0;
}

/**
 * @brief Check if the back button (button just below enter button) is pressed
 * @param input
 * @return The button state:
 *   - 1: button pressed
 *   - 0: button released
 */
int is_back_pressed(Input_t* input)
{
    return input->back_button[0] != input->back_button[1] &&
           input->back_button[0] == 0;
}

/**
 * @brief Detect common movements based on current input
 * @param input
 * @return One of defined movements in the enum SWIPE
 */
enum SWIPE get_gesture(Input_t* input)
{
    if (input->joy_direction[0] == UP && input->joy_direction[1] == NEUTRAL)
        return SWIPE_UP;
    else if (input->joy_direction[0] == LEFT &&
             input->joy_direction[1] == NEUTRAL)
        return SWIPE_LEFT;
    else if (input->joy_direction[0] == DOWN &&
             input->joy_direction[1] == NEUTRAL)
        return SWIPE_DOWN;
    else if (input->joy_direction[0] == RIGHT &&
             input->joy_direction[1] == NEUTRAL)
        return SWIPE_RIGHT;
    else
        return SWIPE_NEUTRAL;
};

/**
 * @brief Send the useful info about current input over CAN
 *
 * The message is structured as follow:
 *   - [0]: the direction of the joystick (UP, LEFT, DOWN, RIGHT, NEUTRAL)
 *   - [1]: the x position of the joystick
 *   - [2]: the y position of the joystick
 *   - [3]: the position of the left slider
 *
 * @param input
 *
 */
void send_input(Input_t* input)
{
    CanMessage_t message;

    // Check if one the input states has changed
    if (input->joy_position[0].X != input->joy_position[1].X ||
        input->joy_position[0].Y != input->joy_position[1].Y ||
        input->left_slider[0] != input->left_slider[1])
    {
        message.id      = INPUT_ID;
        message.length  = 4;
        message.data[0] = input->joy_direction[0];
        message.data[1] = input->joy_position[0].X;
        message.data[2] = input->joy_position[0].Y;
        message.data[3] = input->left_slider[0];
        CAN_print_message(&message);
        CAN_send(&message);
    }
}
