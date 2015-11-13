/**
 * @file JOYSTICK_driver.c
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Joystick interface
 */

#include "JOYSTICK_driver.h"

/**
 * @brief Intialize the driver and calibrate the joystick
 */
void JOY_init()
{
    MCUCR |= (1 << SRE);

    // Init the pin for button input
    DDRB  &= ~(1 << PB0);
    PORTB |= (1 << PB0);
    DDRB  &= ~(1 << PB1);
    PORTB |= (1 << PB1);

    JOY_calibrate();
}


/**
 * @brief Calibrate the joystick by reading position at boot
 */
void JOY_calibrate()
{
    JOY_X_INIT = ADC_read(JOY_X);
    JOY_Y_INIT = ADC_read(JOY_Y);
}

/**
 * @brief Get the current state of a button on the IO card
 */
uint8_t JOY_getButton(enum JOY_button button)
{
    switch (button)
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
    case JOY_ENTER_BUTTON:
        return bit_get(PINB, BIT(0));
    case JOY_BACK_BUTTON:
        return bit_get(PINB, BIT(1));
    default:
        return -1;
    }
}


/**
 * @brief Get the current of the joystic (X-axis and Y-axis)
 * @return The position of the joystick store in a JOY_position_t struct
 */
JOY_position_t JOY_getPosition()
{
    JOY_position_t position;
    uint8_t        JOY_X_value = ADC_read(JOY_X);
    uint8_t        JOY_Y_value = ADC_read(JOY_Y);

    position.X = (JOY_X_value - JOY_X_INIT) * 100 / (255 - JOY_X_INIT);
    position.Y = (JOY_Y_value - JOY_Y_INIT) * 100 / (255 - JOY_Y_INIT);

    return position;
}


/**
 * @brief Get the current direction of the joystick
 * @return One of the direction in JOY_direction_t struct
 */
JOY_direction_t JOY_getDirection()
{

    JOY_position_t position  = JOY_getPosition();
    int            max_value = abs(position.X) > abs(position.Y)
                             ? abs(position.X)
                             : abs(position.Y);

    if (max_value < JOY_THRESHOLD)
        return NEUTRAL;
    if (abs(position.X) > abs(position.Y))
        return position.X < 0 ? LEFT : RIGHT;
    else
        return position.Y > 0 ? UP : DOWN;
}

char * direction_to_string(JOY_direction_t direction)
{
    char* string = malloc(sizeof(char) * 10);

    switch (direction)
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
