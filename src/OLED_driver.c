/*
 * OLED_driver.c
 *
 * Created: 16.09.2015 11:36:29
 *  Author: vegasten
 */ 

#include "OLED_driver.h"

void OLED_write_command(unsigned char cmd)
{
	volatile char *oled_command = (char *) 0x1000;
	oled_command[0] = cmd;
}

void OLED_clr()
{
	volatile char *oled_data = (char *) 0x1200;
	for(int i = 0; i < 8; i++)
	{
		OLED_pos(i,0,127);
		for(int j = 0; j < 128; j++)
		{
			*oled_data = 0x00;
		}
	}
}

void OLED_pos(int page, int column, int width)
{
	//OLED_write_command(0x22);
	//OLED_write_command(page);
	//OLED_write_command(page);
	OLED_goto_line(page);
	OLED_write_command(0x21);
	OLED_write_command(column);
	OLED_write_command(column+width);
}

void OLED_goto_line(int line)
{
	OLED_write_command(0x22);
	OLED_write_command(line);
	OLED_write_command(line);
	OLED_write_command(0x21);
	OLED_write_command(0);
	OLED_write_command(127);
}


void OLED_clear_line(int line)
{
	volatile char *oled_data = (char *) 0x1200;
	OLED_goto_line(line);
	OLED_pos(line, 0,127);
	for(int j = 0; j < 128; j++)
	{
		*oled_data = 0x00;
	}
}

void OLED_init()
{
	MCUCR |= (1 << SRE);
	OLED_write_command(0xae);    // display off
	OLED_write_command(0xa1);    //segment remap
	OLED_write_command(0xda);    //common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xc8);    //common output scan direction:com63~com0
	OLED_write_command(0xa8);    //multiplex ration mode:63
	OLED_write_command(0x3f);
	OLED_write_command(0xd5);    //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81);    //contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xd9);    //set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20);    //Set Memory Addressing Mode
	OLED_write_command(0x02);
	OLED_write_command(0xdb);    //VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xad);    //master configuration
	OLED_write_command(0x00);
	OLED_write_command(0xa4);    //out follows RAM content
	OLED_write_command(0xa6);    //set normal display
	OLED_write_command(0xaf);    // display on
	
	OLED_clr();
}

void OLED_print(char* string)
{
	int length = strlen(string);

	volatile char* oled_data = (char *) 0x1200;	
	for(int i = 0; i < length; i++)
	{
		const unsigned char* char_bytes = get_char(string[i]);
		for(int j = 0; j < FONT_WIDTH; j++)
		{
			*oled_data = pgm_read_byte(&char_bytes[j]);
		}
	}
}

void OLED_print_arrow(int page, int col)
{
	volatile char *oled_data = (char *) 0x1200;
	OLED_pos(page, col, 5);
	*oled_data = 0b00011000;
	*oled_data = 0b00011000;
	*oled_data = 0b01111110;
	*oled_data = 0b00111100;
	*oled_data = 0b00011000;
}
