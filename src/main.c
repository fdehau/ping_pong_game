/*
 * testing.c
 *
 * Created: 02.09.2015 08:52:12
 *  Author: vegasten
 */ 

 
#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//#include "util.h"
// #include "ADC_driver.h"
#include "JOYSTICK_driver.h"
#include "UART_driver.h"
#include "OLED_driver.h"
#include "CAN_driver.h"
#include "input.h"
#include "menu.h"


void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800;//Start address for the SRAM
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;
	
	int seed = rand();
	
	printf("Starting SRAM test...\r\n");
	srand(seed);
	for (i = 0; i < 0x800; i++) {
		testvalue = rand();
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			//printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
	}
	
	srand(seed);
	for (i = 0; i < 0x800; i++) {
		testvalue = rand();
		if (ext_ram[i] != testvalue) {
			//printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}



int main(void)
{
	
	USART_init();
	JOY_init();
	OLED_init();
	CAN_init(MCP_MODE_NORMAL);

	Menu_t* active_menu = menu_create_start_menu();
	Input_t input;
	OLED_clr();
	menu_draw(active_menu, 2);

	while(1)
	{
		
		// Update
		update(&input);
		
		// Process events
		int event_flag = 0;
		switch(get_gesture(&input)){
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
		
		if(is_enter_pressed(&input)){
			if(active_menu->selected)
			{
				active_menu = active_menu->selected;
				event_flag = 1;
			}
		}
		if(is_back_pressed(&input)){
			if(active_menu->parent)
			{
				active_menu = active_menu->parent;
				event_flag = 1;
			}
		}
		
		// Draw
		if(event_flag)
		{
			OLED_clr();
			menu_draw(active_menu, 2);
		}
		
		CanMessage_t message;
		
		memset(&message, 0, sizeof(CanMessage_t));
	
		message.id = 15;
		message.length = 5;
		message.data[0] = 'T';
		message.data[1] = 'E';
		message.data[2] = 'S';
		message.data[3] = 'T';
		uint8_t error_code = CAN_send(&message);
		switch(error_code)
		{
			case 1:
				printf("Send has failed !\n");
				break;
			case 2:
				printf("Send lost arbitration !\n");
				break;
			case 3:
				printf("Send aborted !\n");
				break;
			case 4:
				printf("Strange!\n");
				break;
			case 0:
				printf("Send succeeded !\n");
				break;
		}
		
		
		//CanMessage_t resp;
    		//resp = CAN_receive();
    		//
    		//printf("id: %d\n", resp.id);
    		//printf("length: %d\n", resp.length);
    		//for(int i =0; i < resp.length; i++)
    		//{
   	 		//printf("data[%d]: %d\n", i, (char) resp.data[i]);
    		//}
 		//
		_delay_ms(1000/20);
		
	}
	
	//OLED_pos(1, i++, 13 * FONT_WIDTH);//10 * FONT_WIDTH);
	//OLED_print("Hello world !");// World !");
	//OLED_pos(2, i++, 7 * FONT_WIDTH);//10 * FONT_WIDTH);
	//i = (i>128) ? 0 : i;
	// 		OLED_goto_line(0);
	// 		OLED_print("Testing 1");
	//
	// 		OLED_goto_line(1);
	// 		OLED_print("Testing 2");
	//
	// 		OLED_goto_line(2);
	// 		OLED_print("Testing 3");
	//
	// 		OLED_goto_line(3);
	// 		OLED_print("Testing 4");
	//
	// 		OLED_goto_line(4);
	// 		OLED_print("Testing 5");
	//
	// 		OLED_goto_line(5);
	// 		OLED_print("Testing 6");
	//
	// 		OLED_goto_line(6);
	// 		OLED_print("Testing 7");
	//
	// 		OLED_goto_line(7);
	// 		uint8_t sw_button = JOY_getButton(JOY_SW_BUTTON);
	// 		char str[20];
	// 		printf("Button: %u\n", sw_button);
	// 		sprintf(str, "Button: %u", sw_button);
	// 		OLED_print(str);
	
	//_delay_ms(1000);
	//OLED_clear_line(2);
	
	//OLED_goto_line(4);
	//LED_print("test");
	//_delay_ms(1000);
	//OLED_pos(2,100,0);
	//OLED_print("t");
	//_delay_ms(1000);
	
	
	
	// 		JOY_position_t position = JOY_getPosition();
	// 		JOY_direction_t direction = JOY_getDirection();
	// 		uint8_t left_slider = JOY_getButton(JOY_LEFT_SLIDER);
	// 		uint8_t right_slider = JOY_getButton(JOY_RIGHT_SLIDER);
	// 		char* string = direction_to_string(direction);
	// 		printf("Position %d:%d / Direction: %s / Sliders: %d:%d\n" , position.X, position.Y, string, left_slider, right_slider);
	// 		free(string);
	// 		_delay_ms(500);
	
	
	/*
	while(1)
	{
		JOY_X_value = ADC_read(JOY_X);
		JOY_Y_value = ADC_read(JOY_Y);
		LEFT_SLIDER_value = ADC_read(LEFT_SLIDER);
		RIGHT_SLIDER_value = ADC_read(RIGHT_SLIDER);
		printf("JX: %4d \t    JY: %4d  \t  LS: %4d \t   RS: %4d \n", JOY_X_value, JOY_Y_value, LEFT_SLIDER_value, RIGHT_SLIDER_value);
		_delay_ms(100);
	}
	*/
	
	
	/*DDRC=0xFF;
	
	
	unsigned char testvalue;
	volatile char *ext_ram = (char *) 0x1400;//Start address for the SRAM
	bit_clear(PORTC,BIT(3));
	bit_clear(PORTC,BIT(2));
	int i;
	int seed = rand();
	while(1){
		//SRAM_test();
		//bit_set(PORTC,BIT(2));
		//bit_set(PORTC,BIT(3));
		
		srand(seed);
		for (i = 0; i < 0x400; i++) {
			testvalue = rand();
			ext_ram[i] = testvalue;
			}
	}
	*/
	
	/*
	while(1)
	{
		
		
		int i;
		scanf("%d", &i);
		printf("Hello World! %d\n", i);
		
		
		_delay_ms(1000);		
	}
	*/

	
	/*
	DDRA=0xFF;
    while(1)
    {
        //TODO:: Please write your application code 
	
		PORTA=0xFF;
		_delay_ms(500);
		PORTA=0x0;
		_delay_ms(500);
		
    }
	*/
	
}


