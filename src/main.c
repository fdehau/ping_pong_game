/**
 * @file main.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Entry point for the program uploaded on Atmega 128 (Node 1)
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "input/JOYSTICK_driver.h"
#include "com/UART_driver.h"
#include "display/OLED_driver.h"
#include "com/CAN_driver.h"
#include "com/CAN_test.h"
#include "input/solenoid_driver.h"
#include "input/input.h"
#include "display/menu.h"
#include "display/intro.h"

typedef enum
{
    INTRO,
    PLAYING,
    MENU
} GameState_t;


int main(void)
{
    // Drivers initialization
    UART_init();
    JOY_init();
    OLED_init();
    solenoid_init();
    CAN_init(MCP_MODE_NORMAL);

    // Run the intro
    intro_run_intro();
    intro_ball_enter_screen();

    // Variables to keep track of the ball position on the starter screen
    uint8_t ball_position = 0;
    uint8_t ball_speed    = 1;
    uint8_t count         = 0;


    // Menu initialization
    Menu_t* main_menu   = menu_create_start_menu();
    Menu_t* active_menu = main_menu;

    // Store all input states
    Input_t input;
    update(&input);

    // Store incoming CAN message
    CanMessage_t resp;

    // Curren game state
    GameState_t current_state = INTRO;

    // Keep track of events that trigger a redraw on the OLED display
    int event_flag = 0;

    while (1)
    {
        // Update all inputs
        update(&input);

        if (current_state == INTRO)
        {
            // Make sure that the ball will stay on the screen
            if (ball_position < 0 || ball_position > 114)
                ball_speed *= -1;

            // Update the ball position
            ball_position += ball_speed;

            if (is_enter_pressed(&input))
            {
                current_state = MENU;
            }

            event_flag = 1
        }
        else if (current_state == MENU)
        {
            // Process input events
            switch (get_gesture(&input))
            {
                case SWIPE_UP:
                    menu_move(active_menu, MENU_UP);
                    event_flag = 1;
                    break;
                case SWIPE_DOWN:
                    menu_move(active_menu, MENU_DOWN);
                    event_flag = 1;
                    break;
                default:
                    break;
            }
            if (is_enter_pressed(&input))
            {
                // If its the settings menu check for cycle around available
                // speeds and send a CAN message to Node 2 to update this
                // value
                if (active_menu == main_menu->children[2])
                {
                    CanMessage_t settings;
                    settings.id     = SETTINGS;
                    settings.length = 1;
                    if (!strcmp(active_menu->children[0]->title, "Speed: Slow"))
                    {
                        menu_set_title(active_menu->children[0],
                                       "Speed: Medium");
                        settings.data[0] = 1;
                    }
                    else if (!strcmp(active_menu->children[0]->title,
                                     "Speed: Medium"))
                    {
                        menu_set_title(active_menu->children[0], "Speed: Fast");
                        settings.data[0] = 2;
                    }
                    else if (!strcmp(active_menu->children[0]->title,
                                     "Speed: Fast"))
                    {
                        menu_set_title(active_menu->children[0], "Speed: Slow");
                        settings.data[0] = 0;
                    }
                    CAN_send(&settings);
                }
                // If the user select a submenu move to this submenu
                else if (active_menu->children[active_menu->selected]->length > 0)
                {
                    active_menu = active_menu->children[active_menu->selected];

                    // Process the special case of the "Play" menu
                    if (active_menu == main_menu->children[0])
                    {
                        // Change the game state
                        current_state = PLAYING;

                        // Update the screen accordingly
                        menu_set_title(active_menu->children[0], "Playing...");
                        menu_set_title(active_menu->children[1], "Score: 0");

                        // Signal it to Node 2
                        CanMessage_t game_start;
                        game_start.id     = SCORE;
                        game_start.length = 0;
                        CAN_send(&game_start);
                    }
                }
                event_flag = 1;
            }

            // Go back it the menus
            if (is_back_pressed(&input))
            {
                if (active_menu->parent)
                {
                    active_menu = active_menu->parent;
                    event_flag  = 1;
                }
            }
        }
        else if (current_state == PLAYING)
        {

            // Check for incoming messages
            resp = CAN_receive();

            // If it is a score message that means that the game is finished
            if (resp.id == SCORE)
            {
                // Change the current game state
                current_state = MENU;

                // Retrieve the score in the message (2 fields)
                uint16_t score = resp.data[0] << 8 | resp.data[1];

                // Update the score
                char     tmp[10];
                sprintf(tmp, "Score: %d", score);
                menu_set_title(main_menu->children[0]->children[1], tmp);

                // Inform the player
                menu_set_title(main_menu->children[0]->children[0],
                               "You lose...");

                // Update the high scores table
                menu_update_highscores(main_menu->children[1], score);
                event_flag = 1;
            }
            else
            {
                // The rest of the time just check if the player fire the
                // solenoid and send the current input to the Node 2
                if (is_enter_pressed(&input))
                {
                    solenoid_fire();
                }

                // Send input states to Node 2
                send_input(&input);
            }
        }

        // Draw if necessary
        if (event_flag)
        {
            if (current_state == INTRO)
            {
                intro_draw_ball(ball_position);
                intro_print_blinking_text(count, 30, 7, 25, "Press a button !");
            }
            else
            {
                OLED_clr();
                menu_draw(active_menu, 2);
            }
        }
        count++;
    }
}

