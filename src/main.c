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

typedef enum {
	PLAYING,
	MENU
} GameState_t;


void SRAM_test(void)
{
    unsigned int i;
    //Start address for the SRAM
    volatile char* ext_ram = (char*) 0x1800;
    unsigned int   werrors = 0;
    unsigned int   rerrors = 0;
    unsigned char  testvalue;

    int seed = rand();

    printf("Starting SRAM test...\r\n");
    srand(seed);
    for (i = 0; i < 0x800; i++)
    {
        testvalue  = rand();
        ext_ram[i] = testvalue;
        if (ext_ram[i] != testvalue)
        {
            printf("SRAM error (write phase): ext_ram[%d] = %02X \
                   (should be %02X)\r\n", i, ext_ram[i],
                   testvalue);
            werrors++;
        }
    }

    srand(seed);
    for (i = 0; i < 0x800; i++)
    {
        testvalue = rand();
        if (ext_ram[i] != testvalue)
        {
            printf("SRAM error (read phase): ext_ram[%d] = %02X \
                   (should be %02X)\r\n", i, ext_ram[i],
                   testvalue);
            rerrors++;
        }
    }
    printf("SRAM test completed with %d errors in write phase and %d errors \
           in read phase\r\n", werrors,
           rerrors);
}

int main(void)
{
    // Drivers initialization
    UART_init();
    JOY_init();
    OLED_init();
    solenoid_init();
    CAN_init(MCP_MODE_NORMAL);

    // Menu initialization
    Menu_t* main_menu = menu_create_start_menu();
	Menu_t* active_menu = main_menu;
    OLED_clr();
    menu_draw(active_menu, 2);

    // Store all input states
    Input_t input;

    // Store incoming CAN message
    CanMessage_t resp;
	CanMessage_t game_start;
	game_start.id = SCORE;
	
	GameState_t current_state = MENU;

    while (1)
    {
		int event_flag = 0;
		
        // Update all inputs
        update(&input);
		
		if (current_state == MENU)
		{
			// Process events
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
				if (active_menu->selected)
				{
					active_menu = active_menu->selected;
					
					if (active_menu == main_menu->children[0])
					{
						current_state = PLAYING;
						
						menu_set_title(active_menu->children[0], "Playing...");
						menu_set_title(active_menu->children[1], "Score: 0");
						
						CAN_send(&game_start);
					}
					event_flag  = 1;
				}
			}

			if (is_back_pressed(&input))
			{
				if (active_menu->parent)
				{
					active_menu = active_menu->parent;
					event_flag  = 1;
				}
			}
		}
		else if(current_state == PLAYING)
		{
		
			// Send input states to Node 2
			send_input(&input);
			
			 // Check for incoming message
			 resp = CAN_receive();
			 if (resp.id == SCORE)
			 {
				 current_state = MENU;
				 uint16_t score = resp.data[0] << 8 | resp.data[1];
				 printf("You lose...1");
				 char tmp[50];
				 printf("You lose...2");
				 sprintf(tmp, "Score: %d", score);
				 printf("You lose...3");
				 menu_set_title(main_menu->children[0]->children[1], tmp);
				 printf("You lose...4");
				 menu_set_title(main_menu->children[0]->children[0], "You lose...");
				 printf("You lose...5");
				 menu_update_highscores(main_menu->children[1], score);
				 event_flag = 1;
				 printf("You lose...6");
			 }
			 
			 if (is_enter_pressed(&input))
			 {
				 solenoid_fire();
			 }
		}
       
        // Draw if necessary
        if (event_flag)
        {
            OLED_clr();
            menu_draw(active_menu, 2);
        }
    }
}

