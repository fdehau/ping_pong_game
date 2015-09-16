/*
 * OLED_driver.h
 *
 * Created: 16.09.2015 11:36:42
 *  Author: vegasten
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h> 
#include "font.h"

void OLED_init();
void OLED_clr();
void OLED_write_command(unsigned char cmd);
void OLED_pos(int page, int column, int width);
void OLED_print(char* string);



#endif /* OLED_DRIVER_H_ */